#include <iostream>
#include <string>
#include <stack>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include "dayufs.hpp"

#if defined(_WIN32)
#define DEFAULT_CONFIG_FILE "util.xml"
#else
#define DEFAULT_CONFIG_FILE "/etc/dayu/util.xml"
#endif

namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

typedef boost::shared_ptr<std::vector<fs::path> > FileListPtr;

bool getListDone = false;
bool nonstop = false;
static DayuFs* dayufs = NULL;
const unsigned int iterPerThread = 10000;
uint64_t numfiles = 0;

struct ToBeDel {
    FileListPtr filelist;
    uint64_t start;
    uint64_t count;
};

boost::mutex mutex;

void set_threadlist(FileListPtr filelist, std::list<ToBeDel>& threadlist)
{
    ToBeDel delTask;
    uint64_t sz = filelist->size();

    int num = (sz % iterPerThread) ? (sz / iterPerThread + 1) : (sz / iterPerThread);
    for (int i = 1; i <= num; i++) {
        delTask.filelist = filelist;
        delTask.start = (i - 1)* iterPerThread;
        delTask.count = (i == num) ? (sz - iterPerThread * (num - 1)) : iterPerThread;
        {
            boost::mutex::scoped_lock lock(mutex);
            threadlist.push_back(delTask);
        }
    }
    return;
}

int get_list(DayuFs* dayufs, std::vector<std::string>& path,
            std::list<ToBeDel>& threadlist, std::vector<fs::path>& dirlist) 
{
    fs::path top;
    std::list<DirEntry> entries;
    std::stack<fs::path> st;
    FileListPtr filelist(new std::vector<fs::path>);
    std::vector<std::string>::iterator it = path.begin();
    
    for (; it != path.end(); ++it) {
        fs::path p(*it);
        st.push(p);
        dirlist.push_back(p);
    }

    while(!st.empty()) {
        // Set  threadlist and when the size of filelist is beyond iterPerThread
        if (filelist->size() > iterPerThread) {
            set_threadlist(filelist, threadlist);
            numfiles += filelist->size();
            filelist.reset(new std::vector<fs::path>);
        }
        // Replace the value of top at each iteration, 
        // then read it to param 'entries'
        top = st.top();
        entries.clear();
        int ret = dayufs->readdir(top.string(), entries);
        if(ret) {
            std::cerr << DayuFs::errmsg(-ret) << ", " << top << std::endl;
            if(!nonstop) return -ret;
        }
        st.pop();

        // Iteraoter the list, push files and dirs
        for(std::list<DirEntry>::iterator eit = entries.begin();
                eit != entries.end(); ++eit) {
            DirEntry& stat = *eit;
            fs::path subpath(top/stat.name);
            if(stat.type == DAYU_DIR) {
                st.push(subpath);
                dirlist.push_back(subpath);
            } else {
                filelist->push_back(subpath);
            }
        }
    }

    // The last time to set threadlist and set getListDone flag
    set_threadlist(filelist, threadlist);
    numfiles += filelist->size();
    {
        boost::mutex::scoped_lock lock(mutex);
        getListDone = true;
    }
    return 0;
}

void rm_files(std::list<ToBeDel>& threadlist)
{
    while (1) {
        ToBeDel delTask;
        {
            boost::mutex::scoped_lock lock(mutex);
            if (getListDone && threadlist.empty()) {
                    break;
            }
            if(threadlist.empty() == false) {
                delTask = threadlist.front();
                threadlist.pop_front();
            }
        }
        FileListPtr filelist(delTask.filelist);
        if(filelist == NULL) {
            boost::this_thread::sleep(boost::posix_time::seconds(2));
            continue;
        }
        
        for (uint64_t i = delTask.start; i < delTask.start + delTask.count; i++) {
            int ret = dayufs->remove((*filelist)[i].string());
            if(ret) {
                std::cerr << DayuFs::errmsg(-ret) << ", " << ret << ","
                        << (*filelist)[i].string() << std::endl;
                if (!nonstop) return;
            }
        }
    }

    return;
}

int rm_dirs(std::vector<fs::path>& dirlist) 
{
    std::vector<fs::path>::reverse_iterator it = dirlist.rbegin();
    for (; it != dirlist.rend(); ++it) {
        int ret = dayufs->rmdir(it->string());
        if(ret) {
            std::cerr << DayuFs::errmsg(-ret) << ", " << ret << "," 
                    << it->string() << std::endl;
            if (!nonstop) return -ret;
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int numThreads = 1;
    bool recursive = false;
    bool verbose = false;
    std::vector<std::string> path;
    std::string cfgfile;
    std::vector<fs::path> dirlist;
    std::list<ToBeDel> threadlist;

    po::options_description desc("Allowed options");
    desc.add_options()
        (   "help,h",
            "Show the help message"
        )
        (
            "cfgfile,c",
            po::value<std::string>(&cfgfile)->default_value(DEFAULT_CONFIG_FILE),
            "Config file"
        )
        (
            "path,p",
            po::value<std::vector<std::string> >(&path)->composing(),
            "Directories or file of dayufs to remove, example: /dayupath"
        )
        (
            "recursive,r",
            "Remove directories and their contents recursively"
        )
        (
            "verbose,v",
            "Show the result of remove"
        )
        (
            "nonstop,n",
            "Continue when delete some file or directory wrong"
        )
        (
            "threads,t",
            po::value<int>(&numThreads)->default_value(1),
            "Thread numbers"
        );

    try {
        po::positional_options_description p;
        p.add("path", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(),
                  vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            exit(0);
        }
        if (vm.count("recursive")) {
            recursive = true;
        }
        if (vm.count("verbose")) {
            verbose = true;
        }
        if (vm.count("nonstop")) {
            nonstop = true;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    if (path.empty()) {
        std::cout << desc << std::endl;
        exit(1);
    }
    // Initialize DayuFs library
    dayufs = DayuFs::initialize(cfgfile);
    if(dayufs == NULL) {
        std::cerr << "Failed to initialize DayuFs library!\n";
        dayufs = NULL;
        return 1;
    }

    // Remove single file
    if(recursive == false) {
        std::vector<std::string>::iterator it = path.begin();
        int r = 0;
        for (; it != path.end(); ++it) {
            r = dayufs->remove(*it);
            if(r) {
                std::cerr << DayuFs::errmsg(-r) << ", " << *it << std::endl;
            }
        }
        DayuFs::terminate();
        return -r;
    }
    
    // Start thread to remove files, sleep 2 second if no files exist
    pt::ptime start = boost::get_system_time();
    std::vector<boost::thread*> ths;

    for (int i = 1; i <= numThreads; i++) {
        ths.push_back(new boost::thread(boost::bind(rm_files, boost::ref(threadlist))));
    }

    // Get files and directories
    int r = get_list(dayufs, path, threadlist, dirlist);
    if(r) {
        std::cerr << DayuFs::errmsg(-r) << std::endl;
        DayuFs::terminate();
        return -r;
    }
    // Wait thread to stop
    for (int i = 0; i < numThreads; i++) {
        ths[i]->join();
        delete ths[i];
    }

    // Remove directories
    r = rm_dirs(dirlist);
    if(r) {
        std::cerr << "Remove dirs failed" << std::endl;
        DayuFs::terminate();
        return r;
    }

    // Print iops if param 'verbose' has been set
    pt::ptime end = boost::get_system_time(); 
    double totaltime = ((end - start).total_milliseconds() * (double)1.0);
    uint64_t totalobject = numfiles + dirlist.size();
    double iops = (totalobject * (double)1.0) / (totaltime / 1000);
    if(verbose) {
        // std::cout << "Start time: " << start << std::endl;
        // std::cout << "End time: " << end << std::endl;
        std::cout << "Time Used     : " << totaltime << " ms" << std::endl;
        std::cout << "Total Objects : " << totalobject << std::endl;
        std::cout << "IOPS          : " << iops << std::endl;
    }

    DayuFs::terminate();
    return 0;
}

