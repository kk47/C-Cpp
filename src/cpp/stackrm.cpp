#include <iostream>
#include <string>
#include <boost/program_options.hpp>

#include <list>
#include <stack>

#include "dayufs.hpp"

namespace po = boost::program_options;

#if defined(_WIN32)
#define DEFAULT_CONFIG_FILE "util.xml"
#else
#define DEFAULT_CONFIG_FILE "/etc/dayu/util.xml"
#endif
static DayuFs* dayufs = NULL;

int main(int argc, char* argv[])
{
    std::string path;
    std::string cfgfile;
    bool recursive = false;
    
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
            po::value<std::string>(&path),
            "Directory or file to rm"
        )
        (
            "recursive,r",
            "Remove directories and their contents recursively"
        );

    try {
        po::positional_options_description p;
        p.add("path", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            exit(0);
        }
        if (vm.count("recursive")) {
            recursive = true;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    // Initialize DayuFs library

    dayufs = DayuFs::initialize(cfgfile);
    if(dayufs == NULL) {
        std::cerr << "Failed to initialize DayuFs library!\n";
        dayufs = NULL;
        return 1;
    }
    if(recursive == false) {
        int r = dayufs->remove(path);
        if(r) {
            std::cerr << DayuFs::errmsg(-r) << ", " << path << std::endl;
        }
        DayuFs::terminate();
        return -r;
    }
    
    int ret;
    std::string top;
    std::string subpath;
    std::list<FileInfo> entries;
    std::list<FileInfo>::iterator eit;
    std::stack<std::string> st;

    st.push(path);
    while(!st.empty()) {
        top = st.top();
        entries.clear();
        ret = dayufs->readdir(top, entries);
        if(ret) {
            std::cerr << DayuFs::errmsg(-ret) << ", " << top << std::endl;
            DayuFs::terminate();
            return -ret;
        }
        if(entries.begin() == entries.end()) {
            ret = dayufs->rmdir(top);
            if(ret) {
                std::cerr << DayuFs::errmsg(-ret) << ", " << top << std::endl;
                DayuFs::terminate();
                return -ret;
            }
            st.pop();
            std::cout << "rmdir:" << top << std::endl;
        } else {
            for(eit = entries.begin(); eit != entries.end(); eit++) {
                FileInfo& stat = *eit;
                subpath = top + '/' + stat.name;
                if(stat.type != DAYU_DIR) {
                    ret = dayufs->remove(subpath);
                    if(ret) {
                        std::cout << ret << std::endl;
                        std::cerr << DayuFs::errmsg(-ret) << ", " << subpath << std::endl;
                        DayuFs::terminate();
                        return -ret;
                    }
                    std::cout << "rmfile:" << subpath << std::endl;
                } else {
                    st.push(subpath);
                }
                
            }
        }
    }

    DayuFs::terminate();
    return 0;
}

