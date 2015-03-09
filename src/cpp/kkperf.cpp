#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#include "dayufs.hpp"
#include "dayuerror.hpp"
#include "util/convertor.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

#define DEFAULT_MIN_FILE_SIZE   0
#define DEFAULT_MAX_FILE_SIZE   (512*1024)

namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

typedef boost::mt19937 randeng;
typedef boost::uniform_int<uint64_t> intdis;
typedef boost::variate_generator<randeng, intdis  > intrand;

std::string testdir;
bool testRead = false;
bool testWrite = false;
bool testRemove = false;
bool singledir = false;
bool verbose = false;
bool readMeta = false;
bool dirTest = false;
unsigned int iterPerThread = 10000;
unsigned int numThreads = 1;
uint64_t minFileSize = DEFAULT_MIN_FILE_SIZE;
uint64_t maxFileSize = DEFAULT_MAX_FILE_SIZE;
unsigned int recordSize = 512 * 1024;
std::string prefix("test");
std::string postfix("");
// By default, read file by name in order.
// Instead, read file by name randomly, which may read single file 
// several times and some file may not be read at all.
bool readInSeq = true; 

bool api = false;
DayuFs* dayufs = NULL;
std::string cfgfile;

class result
{
public:
    result() :
        startTime(),
        endTime(),
        numFiles(0),
        numSuccess(0),
        totalSize(0),
        minLat(99999999),
        maxLat(0),
        avgLat(0)
    {}

    pt::ptime           startTime;
    pt::ptime           endTime;
    unsigned int        numFiles;
    unsigned int        numSuccess;
    uint64_t            totalSize;
    uint64_t            minLat;
    uint64_t            maxLat;
    uint64_t            avgLat;
};

// uniform distribution random number generator
static intrand uniformRandGenerator(uint64_t min, uint64_t max)
{
    randeng eng;
    eng.seed(static_cast<uint64_t>(time(NULL)));
    intdis dis(min, max);
    return intrand(eng, dis);
}

// File name generator
static std::string fname(unsigned int  threadid,
                  unsigned int seq)
{
    std::ostringstream oss;
    if(singledir) {
        oss << testdir << "/" << prefix << "-" << threadid << "-" << seq;
    } else {
        oss << testdir << "/" << threadid << "/" << prefix << "-" << seq;
    }
    if (!postfix.empty()) 
        oss << "." << postfix;

    return oss.str();
}

static int close_fn(int fd)
{
    int r = 0;
    if(api) {
        r = dayufs->close(fd);
        if(r < 0) {
            std::cerr << "Failed to close " << fd << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }
    } else {
        r = ::close(fd);
        if(r < 0) {
            std::cerr << "Failed to close " << fd << ", "
                      << strerror(errno) << std::endl;
        }
    }
    return r;
}    

static int open_fn(const std::string& fn, int flag)
{
    int fd = 0;
    if(api) {
        fd = dayufs->open(fn, flag);
        if(fd < 0) {
            std::cerr << "Failed to open " << fn << ", "
                      << DayuFs::errmsg(fd) << std::endl;
        }
    } else {
        fd = ::open(fn.c_str(), flag);
        if(fd < 0) {
            std::cerr << "Failed to open " << fn << ", " 
                      << strerror(errno) << std::endl;
        }
    }
    return fd;
}    

static int create_fn(const std::string& fn)
{
    int fd = 0;
    if(api) {
        fd = dayufs->create(fn, 0644, true);
        if(fd < 0) {
            std::cerr << "Failed to open " << fn << ", "
                      << DayuFs::errmsg(fd) << std::endl;
        }
    } else {
        fd = ::open(fn.c_str(), O_CREAT | O_WRONLY, 0644);
        if(fd < 0) {
            std::cerr << "Failed to open " << fn << ", " 
                      << strerror(errno) << std::endl;
        }
    }
    return fd;
}    

static int remove_fn(const std::string& fn)
{
    int r = 0;
    if(api) {
        r = dayufs->remove(fn);
        if(r) {
            std::cerr << "Failed to remove " << fn << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }
    } else {
        r = ::unlink(fn.c_str());
        if(r < 0) {
            std::cerr << "Failed to open " << fn << ", " 
                      << strerror(errno) << std::endl;
        }
    }
    return r;
}

static int getattr_fn(const std::string& fn)
{
    int r = 0;
    if(api) {
        struct FileInfo st;
        r = dayufs->getattr(fn.c_str(), st);
        if(r < 0) {
            std::cerr << "Failed to getattr " << fn << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }
    } else {
#ifdef _WIN32
        WIN32_FILE_ATTRIBUTE_DATA data;
        GET_FILEEX_INFO_LEVELS fInfoLevelId = GetFileExInfoStandard;
        r = GetFileAttributesEx(fn.c_str(), fInfoLevelId, &data);
        if(r != 0) {
            std::cerr << "Failed to lstat " << fn << ", "
                      << GetLastError() << std::endl;
        }
#else
        struct stat st;
        r = ::lstat(fn.c_str(), &st);
        if(r < 0) {
            std::cerr << "Failed to lstat " << fn << ", "
                      << strerror(errno) << std::endl;
        }
#endif
    }
    return r;
}

static int read_fn(int fd, char* buf, uint len)
{
    int r = 0;
    if(api) {
        r = dayufs->read(fd, buf, len);
        if(r < 0) {
            std::cerr << "Failed to read " << fd << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }
    } else {
        r = ::read(fd, buf, len);
        if(r < 0) {
            std::cerr << "Failed to read " << fd << ", " 
                      << strerror(errno) << std::endl;
        }
    }
    return r;
}

static int write_fn(int fd, const char* buf, uint len)
{
    int r = 0;
    if(api) {
        r = dayufs->write(fd, buf, len);
        if(r < 0) {
            std::cerr << "Failed to write " << fd << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }
    } else {
        r = ::write(fd, buf, len);
        if(r < 0) {
            std::cerr << "Failed to write " << fd << ", " 
                      << strerror(errno) << std::endl;
        }
    }
    return r;
}

static int create_dir(const std::string& fn)
{
#ifdef _WIN32
    return _mkdir(fn.c_str());
#else
    return ::mkdir(fn.c_str(), 0755);
#endif
}

static bool createDir(const std::string& dest)
{
    // Check if the testdir exists, if not, create it. 
    // if fails return false;
    
    if(api) {
        int r = dayufs->mkdir(dest, 0755);
        if(r < 0) {
            if(r == -DAYU_EEXIST) {
                if(testWrite) {
                    std::cerr << "Directory " << dest << " exists" << std::endl;
                    return false;
                } else {
                    return true;
                }    
            } else {
                std::cerr << "Failed to create dir " << dest << ", "
                          << DayuFs::errmsg(r) << std::endl;
                return false;
            }
        } else {
            return true;
        } 
    }

    int r = create_dir(dest);
    if(r < 0) {
        std::cerr << "Failed to create dir " << dest << ", "
                  << strerror(errno) << std::endl;
        return false;
    }
    return true;
}   

static void removeDir(const std::string& dest)
{
    if(api) {
        int r = dayufs->rmdir(dest);
        if(r) {
            std::cerr << "Failed to rmdir " << dest << ", "
                      << DayuFs::errmsg(r) << std::endl;
        }    
        return;
    }
    
    fs::path dir(dest);
    if (fs::is_empty(dir)) {
        fs::remove(dir);
    }
}

static bool prepareEnv()
{
    if(createDir(testdir) == false) {
        return false;
    }
    
    // create sub dir 
    if(singledir == false) {
        for(uint i = 0; i < numThreads; ++i) {
            std::string sub = testdir + "/" + Convertor::val2Str(i);
            if(createDir(sub) == false) {
                return false;
            }
        }
    }
    return true;
}

static void cleanEnv()
{
    // remove sub dir 
    if(singledir == false) {
        for(uint i = 0; i < numThreads; ++i) {
            std::string sub = testdir + "/" + Convertor::val2Str(i);
            removeDir(sub);
        }
    }
    removeDir(testdir);
}


static int readTest(const std::string& fn, char* buf)
{
    int fd = open_fn(fn, O_RDONLY);
    if (fd < 0) {
        return -1;
    }
    
    size_t nbytes = 0;
    while(true) {
        ssize_t got = read_fn(fd, buf, recordSize);
        if(got == 0) {
            break; // eof
        }
        if(got < 0) {
            close_fn(fd);
            return -1;
        }
        nbytes += got;
    }
    close_fn(fd);
    return nbytes;
}

static bool writeTest(const std::string& fn, uint64_t size, char* buf)
{
    // create/open
    int fd = create_fn(fn);
    if (fd < 0) {
        return false;
    }

    uint64_t tmpSize = size;
    while (tmpSize != 0) {
        int sz = tmpSize > recordSize ? recordSize : tmpSize;
        if (write_fn(fd, buf, sz) < sz) {
            close_fn(fd);
            return false;
        }
        tmpSize -= sz;
    }
    close_fn(fd);
    return true;
}

static int removeTest(const std::string& fn)
{
    if (dirTest) {
        removeDir(fn);
        return 0;
    } else {
        return remove_fn(fn);
    }
}

static int getattrTest(const std::string& fn)
{
    return getattr_fn(fn);
}

static void testReadThread(unsigned int id, result* res)
{
    // each thread use a buffer to avoid allocate many times
    char* buf = new char[recordSize];
    
    res->startTime = boost::get_system_time();
    res->numFiles = iterPerThread;

    intrand die = uniformRandGenerator(0, iterPerThread - 1);

    uint64_t avgLat = 0;
    for (unsigned int i = 0; i < iterPerThread; i++) {
        std::string fn;
        if (readInSeq) {
            fn = fname(id, i);
        } else {
            fn = fname(id, die());
        }

        pt::ptime stime  = boost::get_system_time();
        // Read metadata if param readMeta has been set
        if (readMeta) {
            int r = getattrTest(fn);
            if (r < 0) {
                std::cout << "Failed to get metadata of file: " << fn << std::endl;
                continue;
            } else {
                res->numSuccess ++;
            }
        } else {
            int sz = readTest(fn, buf);
            if (sz >= 0) {
                res->numSuccess ++;
                res->totalSize += sz;
            } else {
                std::cout << "Failed to read file: " << fn << std::endl;
                continue;
            }
        }

        uint64_t lat =  (boost::get_system_time() - stime).total_microseconds();
        if(verbose) {
            std::cout << "\t\tRead Latency: " << lat << std::endl;
        }
        if (lat < res->minLat) res->minLat = lat;
        if (lat > res->maxLat) res->maxLat = lat;
        avgLat += lat;
    }
    
    delete [] buf;
    res->endTime = boost::get_system_time();
    res->avgLat = avgLat / res->numFiles;
    return;
}

static void testRemoveThread(unsigned int id, result* res)
{
    res->startTime = boost::get_system_time();
    res->numFiles = iterPerThread;

    uint64_t avgLat = 0;
    for (unsigned int i = 0; i < iterPerThread; i++) {
        std::string fn;
        fn = fname(id, i);

        pt::ptime stime  = boost::get_system_time();
        int sz = removeTest(fn);
        if (sz == 0) {
            res->numSuccess ++;
        } else {
            std::cout << "Failed to remove file: " << fn << std::endl;
        }

        uint64_t lat =  (boost::get_system_time() - stime).total_microseconds();
        if(verbose) {
            std::cout << "\t\tRemove Latency: " << lat << std::endl;
        }
        if (lat < res->minLat) res->minLat = lat;
        if (lat > res->maxLat) res->maxLat = lat;
        avgLat += lat;
    }

    res->endTime = boost::get_system_time();
    res->avgLat = avgLat / res->numFiles;
    return;
}

static void testWriteThread(unsigned int id, result* res)
{
    // each thread use a buffer to avoid allocate many times
    char* buf = new char[recordSize]; 
    
    res->startTime = boost::get_system_time();
    res->numFiles = iterPerThread;

    intrand die = uniformRandGenerator(minFileSize, maxFileSize);
    
    uint64_t avgLat = 0;
    for (unsigned int i = 0; i < iterPerThread; i++) {
        std::string fn = fname(id, i);

        pt::ptime stime  = boost::get_system_time();
        // Mkdirs if param dirTest has been set
        if (dirTest) {
            if (createDir(fn)) {
                res->numSuccess ++;
            } else {
                std::cout << "Failed to write file: " << fn << std::endl;
                continue;
            }
        } else {
            uint64_t sz = die();
            if (writeTest(fn, sz, buf)) {
                res->numSuccess ++;
                res->totalSize += sz;
            } else {
                std::cout << "Failed to write file: " << fn << std::endl;
                continue;
            }
        }

        uint64_t lat =  (boost::get_system_time() - stime).total_microseconds();
        if(verbose) {
            std::cout << "\t\tWrite Latency: " << lat << std::endl;
        }

        if (lat < res->minLat) res->minLat = lat;
        if (lat > res->maxLat) res->maxLat = lat;
        avgLat += lat;
    }
    
    delete [] buf;
    res->endTime = boost::get_system_time();
    res->avgLat = avgLat / res->numFiles;
    return;
}

static void printConfig()
{
    std::cout << "\tDayu File Performance Test\n";
    std::cout << "\t\tAPI type:             \t" 
              << (api ? "DayuFs API" : "POSIX API") << std::endl;
    std::cout << "\t\tTest Directory:       \t" << testdir << std::endl;
    std::cout << "\t\tTest File Prefix:     \t" << prefix << std::endl;
    std::cout << "\t\tTest File Postfix:    \t" << postfix << std::endl;
    std::cout << "\t\tNumber of Threads:    \t" << numThreads << std::endl;
    std::cout << "\t\tNumber of iterations: \t" << iterPerThread << std::endl;
    std::cout << "\t\tMinimal File Size:    \t" << minFileSize << std::endl;
    std::cout << "\t\tMaxmum File Size:     \t" << maxFileSize << std::endl;
    std::cout << "\t\tTest Read Perf:       \t" << (testRead ? "Yes" : "No") << std::endl;
    std::cout << "\t\tRead Metadata:        \t" << (readMeta ? "Yes" : "No") << std::endl;
    std::cout << "\t\tTest Write Perf:      \t" << (testWrite ? "Yes" : "No")  << std::endl;
    std::cout << "\t\tDirectory test:       \t" << (dirTest ? "Yes" : "No")  << std::endl;
    std::cout << "\t\tTest Remove Perf:     \t" << (testRemove ? "Yes" : "No")  << std::endl;
    std::cout << "\t\tRead file in sequence:\t" << (readInSeq ? "Yes" : "No")  << std::endl;
    std::cout << "\t\tSame dir for threads: \t" << (singledir ? "Yes" : "No")  << std::endl;
    std::cout << "\t\tRecord size :         \t" << recordSize << std::endl;
 
    std::cout << std::endl;
}

static void printResult(std::vector<result*>& res)
{
    std::cout << "\tTest Result:\n";
    if (res.empty()) {
        std::cout << "\t\tNO test result" << std::endl;
    }

    uint64_t avgLat = 0;
    uint64_t minLat = 99999999;
    uint64_t maxLat = 0;
    uint64_t succed = 0;
    pt::ptime start = res[0]->startTime;
    pt::ptime end = res[0]->endTime;
    uint64_t totalSize = 0;

    for (unsigned int i = 0; i < res.size(); i++) {
        succed += res[i]->numSuccess;
        avgLat += res[i]->avgLat;
        totalSize += res[i]->totalSize;
        if (maxLat < res[i]->maxLat) maxLat = res[i]->maxLat;
        if (minLat > res[i]->minLat) minLat = res[i]->minLat;
        if (start > res[i]->startTime) start = res[i]->startTime;
        if (end < res[i]->endTime) end = res[i]->endTime;
    }

    std::cout << "\t\t" << succed << " files with " << totalSize << " Bytes handled in " 
              << (end - start).total_milliseconds() << " ms " << std::endl;
    std::cout << "\t\tTest start:       " << start << std::endl;
    std::cout << "\t\tTest end:         " << end << std::endl;
    double sec = ((end - start).total_milliseconds() * (double)1.0) / 1000;
    std::cout << "\t\tIOPS:             " 
              << (succed * (double)1.0) / sec << std::endl;
    std::cout << "\t\tThroughput:       " 
              << (totalSize * (double)1.0) / (1024*1024*sec) 
              << " MB/s" << std::endl;
    std::cout << "\t\tMinimal latency:  " << minLat << " us" << std::endl;
    std::cout << "\t\tMaxmum latency:   " << maxLat << " us" << std::endl;
    std::cout << "\t\tAverage latency:  " 
              << avgLat / numThreads << " us" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[]) 
{
    std::string usage("\
Usages:\n\
    dayufileperf [option] \n\
Allowed Option");

    try {
        po::options_description desc(usage);
        desc.add_options()
            (   "help,h",
                "Show the help message"
            )
            (   "cfgfile,f",
#ifdef _WIN32
            po::value<std::string>(&cfgfile)->default_value("util.xml"),
#else
            po::value<std::string>(&cfgfile)->default_value(
                "/etc/dayu/util.xml"),
#endif
            "Config file"
            )
            (   "iter,i",
                po::value<unsigned int>(&iterPerThread)->default_value(10000),
                "Iterations per threads"
            )
            (   "threads,t",
                po::value<unsigned int>(&numThreads)->default_value(1),
                "Thread numbers"
            )
            (   "testdir,d",
#ifdef _WIN32                
                po::value<std::string>(&testdir)->default_value(
                    "N:\\dayufiletest"),
#else                
                po::value<std::string>(&testdir)->default_value(
                    "/mnt/dayu/dayufiletest"),
#endif                
                "Test directory"
            )
            (   "prefix,p",
                po::value<std::string>(&prefix)->default_value("test"),
                "Testfile prefix"
            )
            (   "postfix,o",
                po::value<std::string>(&postfix)->default_value(""),
                "Testfile postfix"
            )
            (   "minfilesize,m",
                po::value<uint64_t>(&minFileSize)->default_value(DEFAULT_MIN_FILE_SIZE),
                "min size of test files"
            )
            (   "maxfilesize,x",
                po::value<uint64_t>(&maxFileSize)->default_value(DEFAULT_MAX_FILE_SIZE),
                "max size of test files"
            )
            (   "recordsize,R",
                po::value<unsigned int>(&recordSize)->default_value(512*1024),
                "record size of files"
            )
            (   "api,a",
                "Use DayuFs API directly"
            )
            (   "read,r",
                "Perform read test"
            )
            (   "metadata,M",
                "Get metadata in read test"
            )
            (   "write,w",
                "Perform write test"
            )
            (   "writedir,D",
                "Write directories in write test"
            )
            (   "cleanup,c",
                "Perform remove (cleanup) test"
            )
            (   "verbose,v",
                "Verbose output"
            )
            (   "sequencial,s",
                "Read files in sequence"
            )
            (
                "singledir,l",
                "All threads write files in a single dir"
            );

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc),  vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            exit(1);
        }
        if (vm.count("read")) {
            testRead = true;
        }
        if (vm.count("metadata")) {
            readMeta = true;
        }
        if (vm.count("write")) {
            testWrite = true;
        }
        if (vm.count("writedir")) {
            dirTest = true;
        }
        if (vm.count("cleanup")) {
            testRemove = true;
        }
        if (vm.count("sequencial")) {
            readInSeq = true;
        }
        if (vm.count("singledir")) {
            singledir = true;
        }
        if (vm.count("verbose")) {
            verbose = true;
        }
        if (vm.count("api")) {
            api = true;
        }
 
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    if(testRead == false && testWrite == false && testRemove == false) {
        std::cerr << "please specify -r (read test) "
                  << " -w (write test) or -e (remove test)" << std::endl;
        return 1;
    }

    printConfig();
    
    if(api) {
        dayufs = DayuFs::initialize(cfgfile);
        if(dayufs == NULL) {
            std::cerr << "Failed to initialize DayuFs library!" << std::endl;
            dayufs = NULL;
            return 1;
        }
    }
    
    if (!prepareEnv()) {
        std::cout << "Failed to prepare environments" << std::endl;
        return -1;
    }

    if (testWrite) {
        std::cout << "\tTest write performance ..." << std::endl;
        std::vector<result*> res;
        std::vector<boost::thread*> ths;
        for (unsigned int i = 0; i < numThreads; i++) {
            result* r = new result();
            ths.push_back(new boost::thread(boost::bind(testWriteThread, i, r)));
            res.push_back(r);
        }

        for (unsigned int i = 0; i < numThreads; i++) {
            ths[i]->join();
        }

        printResult(res);

        for (uint i = 0; i < res.size(); i++) {
            delete res[i];
        }
    } 

    if (testRead) {
        std::cout << "\tTest read performance ..." << std::endl;
        std::vector<result*> res;
        std::vector<boost::thread*> ths;
        for (unsigned int i = 0; i < numThreads; i++) {
            result* r = new result();
            ths.push_back(new boost::thread(boost::bind(testReadThread, i, r)));
            res.push_back(r);
        }
        for (unsigned int i = 0; i < numThreads; i++) {
            ths[i]->join();
        }

        printResult(res);

        for (unsigned int i = 0; i < res.size(); i++) {
            delete res[i];
        }
    }

    if (testRemove) {
        std::cout << "\tTest remove performance ..." << std::endl;
        std::vector<result*> res;
        std::vector<boost::thread*> ths;
        for (unsigned int i = 0; i < numThreads; i++) {
            result* r = new result();
            ths.push_back(new boost::thread(boost::bind(testRemoveThread, i, r)));
            res.push_back(r);
        }
        for (unsigned int i = 0; i < numThreads; i++) {
            ths[i]->join();
        }

        printResult(res);

        for (unsigned int i = 0; i < res.size(); i++) {
            delete res[i];
        }
        cleanEnv();
    }

    if(api) {
        DayuFs::terminate();
    }
    return 0;
}
