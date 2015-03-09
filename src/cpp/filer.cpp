#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

int main()
{
    const char* file = "cpu.txt";
    std::ifstream fin;
    std::string line;
    fin.open(file, std::ios_base::in);
    if (!fin.is_open()) {
        std::cout << "Failed to open file cpuinfo" << std::endl;
    }
    
    int corenum = 0;
    int procnum = 0;
    int phynum = 0;
    std::string cpuVendor;
    std::vector<std::string> lineVec1, lineVec2, lineVec3;

    while (getline(fin, line)) {
        if (boost::starts_with(line, "processor")) {
            procnum++;
        }
        if (boost::starts_with(line, "model name")) {
            boost::trim(line);
            boost::split(lineVec1, line, boost::is_any_of(":"));
            //std::vector<std::string>::iterator it = lineVec1.begin();
            // for (; it != lineVec.end(); it++) {
            //    std::cout << *it << std::endl;
            //}
            boost::trim(lineVec1[1]);
        }
        if (boost::starts_with(line, "physical id")) {
            boost::split(lineVec2, line, boost::is_any_of(":"));
            boost::trim(lineVec2[1]);
        }

        if (boost::starts_with(line, "cpu cores")) {
            boost::split(lineVec3, line, boost::is_any_of(":"));
            boost::trim(lineVec3[1]);
        }
    }
    if (!lineVec1.empty()) {
        cpuVendor = lineVec1[1];
    }
    if (!lineVec2.empty()) {
        try {
            phynum = boost::lexical_cast<int>(lineVec2[1]);
        } catch(boost::bad_lexical_cast &) {
            std::cout << "Convert cpu physical id fault" << std::endl;
        }
        phynum += 1;
    }
    if (!lineVec3.empty()) {
        try {
            corenum = boost::lexical_cast<int>(lineVec3[1]);
        } catch(boost::bad_lexical_cast &) {
            std::cout << "Convert value fault" << std::endl;
        }
    }
    std::cout << phynum << "*" << cpuVendor << "( " << corenum << " core, "
                << procnum << " processor )" << std::endl;
    
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    std::cout << "TotalMem: " << pages * page_size << std::endl;

    return 0;
}
