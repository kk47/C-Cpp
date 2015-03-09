#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include <list>
#include <vector>

#include "dayufs.hpp"
#include "dayulog.hpp"

namespace po = boost::program_options;

#if defined(_WIN32)
#define DEFAULT_CONFIG_FILE "util.xml"
#else
#define DEFAULT_CONFIG_FILE "/etc/dayu/util.xml"
#endif
static DayuFs* dayufs = NULL;
int recrmdir(std::string& path);

int main(int argc, char* argv[])
{
    std::string path = "/";
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
    
    int ret = recrmdir(path);
    if(ret != 0) {
        std::cerr << DayuFs::errmsg(-ret) << ", " << path << std::endl;
        return -ret;
    }

    DayuFs::terminate();
    return 0;

}

int recrmdir(std::string& subpath)
{
    std::list<FileInfo> entries;
    bool empty = false;
    int r;
    int ret = dayufs->readdir(subpath, entries);
    if(ret != 0) {
        std::cerr << DayuFs::errmsg(-ret) << ", " << subpath << std::endl;
        DayuFs::terminate();
        return -ret;
    }

    std::list<FileInfo>::iterator eit = entries.begin();
    if (empty == false)
        for(; eit != entries.end(); ++eit)
        {
            FileInfo& stat = *eit;

            std::string mode;
            switch(stat.type)
            {
                case DAYU_FILE:
                    mode = "F";
                    break;
                case DAYU_DIR:
                    mode = "D";
                case DAYU_SYMLINK:
                    mode = "S";
                    break;
                default:
                    DASSERT(false, "unknown object type");
            }
     
            std::string tmppath = subpath + "/" + stat.name;
            if(stat.type != DAYU_DIR) {
                std::cout << "rmfile:" << tmppath << std::endl;
                r = dayufs->remove(tmppath); 
                if(r) {
                    std::cerr << DayuFs::errmsg(-r) << ", " << tmppath << std::endl;
                    exit(1);
                }
            } else {
                recrmdir(tmppath);
              }
      }

        ret = dayufs->readdir(subpath, entries);
        if(ret != 0) {
            std::cerr << DayuFs::errmsg(-ret) << ", " << subpath << std::endl;
            DayuFs::terminate();
            return -ret;
        }
        if(entries.empty()) {
            empty=true;
        }
    std::cout << "rmdir:" << subpath << std::endl;
    r = dayufs->rmdir(subpath);
    if(r) {
        std::cerr << DayuFs::errmsg(-r) << ", " << subpath << std::endl;
        exit(1);
    }
    return 0;
}
