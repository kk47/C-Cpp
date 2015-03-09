#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <unistd.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "util/convertor.hpp"
#include "cms.pb.h"

dayu::NodeInfo nodeInfo;

bool get_ip(std::string& ipstring)
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        std::cerr << "getifaddrs" << std::endl;
        return false;
    }

    /* Walk through linked list, maintaining head pointer so we
       can free list later */

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;
        
        family = ifa->ifa_addr->sa_family;
        /* For an AF_INET* interface address, display the address */

        if (family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0) {
            s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                    host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                std::cout << "getnameinfo() failed: " << gai_strerror(s) << std::endl;
                return false;
            }
            if (ipstring != "") {
                ipstring += ",";
                ipstring += ifa->ifa_name;
                ipstring += ":";
                ipstring += host;
            } else {
                ipstring = ifa->ifa_name;
                ipstring += ":";
                ipstring += host;
            }
        }
    }
    
    freeifaddrs(ifaddr);
    return true;
}

void get_hostname(std::string& hostname)
{
    char name[255];
    gethostname(name, 255);
    hostname = name;
}

bool get_cpuinfo(std::string& cpuinfo)
{
    const char* file = "/proc/cpuinfo";
    std::ifstream fin;
    std::string line;
    fin.open(file, std::ios_base::in);
    if (!fin.is_open()) {
        std::cout << "Failed to open file cpuinfo" << std::endl;
        return false;
    }
    
    int threads = 0;
    std::vector<std::string> linestr;
    
    while (getline(fin, line)) {
        linestr.push_back(line);
    }
    fin.close();

    for (unsigned int i = 0; i < linestr.size(); i++) {
        std::string key = "";
        std::string value = "";
        std::vendor = "";
        size_t pos = 0;

        pos = linestr[i].find(":");
        // means until the end of the string
        if (pos != std::string::npos) { 
            continue
        }

        key = linestr[i].substr(0, pos);
        boost::trim(key);
        value = linestr[i].substr(pos + 1);
        boost::trim(value);
        if (key == "processor") {
            threads++;
            continue;
        } else if (key == "vendor_id") {
            vendor = value;
        } else if (key == "model name") {
            product = value;
        } else if (key == "cpu MHz") {
            speed = value;
        } else if (key == "cpu cores") {
            cores = value;
        } else if (key == "flags") {
            bits = value;
        }
    }
    
    /*std::string cpuVendor, corestr;
    std::vector<std::string> lineVec1, lineVec2, lineVec3;
    

    while (getline(fin, line)) {
        pos = line.find(':');
        if (boost::starts_with(line, "processor")) {
            procnum++;
            continue;
        }
        if (boost::starts_with(line, "model name")) {
            boost::split(lineVec1, line, boost::is_any_of(":"));
            boost::trim(lineVec1[1]);
            continue;
        }
        if (boost::starts_with(line, "physical id")) {
            boost::split(lineVec2, line, boost::is_any_of(":"));
            boost::trim(lineVec2[1]);
            continue;
        }

        if (boost::starts_with(line, "cpu cores")) {
            boost::split(lineVec3, line, boost::is_any_of(":"));
            boost::trim(lineVec3[1]);
            continue;
        }

        if (boost::starts_with(line, "cpu MHz")) {
            boost::split(lineVec4, line, boost::is_any_of(":"));
            boost::trim(lineVec3[1]);
            continue;
        }
    }
    if (!lineVec1.empty()) {
        cpuVendor = lineVec1[1];
    }
    if (!lineVec2.empty()) {
        int ret = Convertor::str2Val(lineVec2[1], phynum);
        if (!ret) {
            std::cout << "Convert cpu physical id fault" << std::endl;
            return false;
        }
        phynum += 1;
    }
    if (!lineVec3.empty()) {
        corestr = lineVec3[1];
    }
    std::string phystr, procstr;
    phystr = Convertor::val2Str(phynum);
    procstr = Convertor::val2Str(procnum);
    cpuinfo = phystr + "*" + cpuVendor + "( " + corestr + " core, " + procstr + " processor )"; */
    return true;
}

void get_meminfo(std::string& meminfo)
{
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    meminfo = Convertor::val2ReadableStr(pages * page_size, 1024);
}

int main()
{
    std::string ipstring;
    std::string hostname;
    std::string cpuinfo;
    std::string meminfo;
    dayu::NodeInfo nodeInfo;

    // get ip list
    bool ret = get_ip(ipstring);
    if (ret) {
        std::cout << ipstring << std::endl;
    } else {
        std::cout << "Failed to get ip list" << std::endl;
    }

    // get hostname
    get_hostname(hostname);
    std::cout << hostname << std::endl;

    // get cpuinfo
    ret = get_cpuinfo(cpuinfo);
    if (ret) {
        std::cout << cpuinfo << std::endl;
    } else {
        std::cout << "Failed to get cpuinfo" << std::endl;
    }

    // get meminfo
    get_meminfo(meminfo);
    std::cout << meminfo << std::endl;
    return 0;
}
