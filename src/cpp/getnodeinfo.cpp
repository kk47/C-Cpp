#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "util/convertor.hpp"

#include "cms.pb.h"

#ifdef _WIN32
#include <windows.h>
#include <iphlpapi.h>
// "interface" will be used in cms proto, can not be replace by macro
#ifdef interface
#undef interface
#endif

#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <sys/utsname.h>
#endif

#ifdef _WIN32
bool getnodeinfo(dayu::NodeInfo& nodeInfo)
{
    // set mem;
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    int ret = GlobalMemoryStatusEx(&statex);
    if (ret) {
        std::string meminfo = Convertor::val2ReadableStr(statex.ullTotalPhys,
            1024);
        nodeInfo.set_mem(meminfo);
    }

    // set cpu;
    SYSTEM_INFO siSysInfo;
    std::string arch = "";
    std::string protype = "";
    //std::string bits = "";
    GetSystemInfo(&siSysInfo);
    if (siSysInfo.dwOemId == PROCESSOR_ARCHITECTURE_AMD64) {
        arch = "x64(AMD or INTEL)";
        //bits = "64";
    } else if (siSysInfo.dwOemId == PROCESSOR_ARCHITECTURE_ARM) {
        arch = "ARM";
    } else if (siSysInfo.dwOemId == PROCESSOR_ARCHITECTURE_IA64) {
        arch = "Intel Itanium-based";
    } else if (siSysInfo.dwOemId == PROCESSOR_ARCHITECTURE_INTEL) {
        arch = "x86";
        //bits = "32";
    } else {
        arch = "";
    }
    std::string vendor = "INTEL";
    if (siSysInfo.dwProcessorType == PROCESSOR_INTEL_386) {
        protype = "INTEL 386";
    } else if (siSysInfo.dwProcessorType == PROCESSOR_INTEL_486 ) {
        protype = "INTEL 486";
    } else if (siSysInfo.dwProcessorType == PROCESSOR_INTEL_PENTIUM) {
        protype = "INTEL pentium 586";
    } else if (siSysInfo.dwProcessorType == PROCESSOR_INTEL_IA64) {
        protype = "INTEL IA64";
    } else {
        protype = "AMD";
        vendor = "AMD";
    }
    protype = protype + " " + arch;

    dayu::CpuInfo* cpuInfo = nodeInfo.add_cpu();
    cpuInfo->set_vendor(vendor);
    cpuInfo->set_product(protype);
    cpuInfo->set_threads(Convertor::val2Str(siSysInfo.dwNumberOfProcessors));
    //cpuInfo->set_bits(bits);

    // set nic;
    PIP_ADAPTER_INFO pAdapterInfo;
    std::string ip = "";
    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
    ULONG buflen = sizeof (IP_ADAPTER_INFO);
    
    if(GetAdaptersInfo(pAdapterInfo, &buflen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) malloc(buflen);
    }
    
    if(GetAdaptersInfo(pAdapterInfo, &buflen) == NO_ERROR) {
         PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
         while(pAdapter) {
            ip = pAdapter->IpAddressList.IpAddress.String;
            if (ip != "0.0.0.0") {
                dayu::NicInfo* nicInfo = nodeInfo.add_nic();
                std::string adpname = pAdapter->AdapterName;
                nicInfo->set_interface(adpname);
                IP_ADDRESS_STRING ip = pAdapter->IpAddressList.IpAddress;
                nicInfo->set_ip(Convertor::val2Str(ip.String));
            }
            pAdapter = pAdapter->Next;
         } 
    } 
    if (pAdapterInfo) {
        free(pAdapterInfo);
    }

    // set os;
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    int vret = GetVersionEx((OSVERSIONINFO *)&osvi);
    if(vret) {
        std::string dist = "";
        std::string kernel = "";
        if(osvi.dwMajorVersion == 6) {
            if(osvi.dwMinorVersion == 0) {
                if(osvi.wProductType == VER_NT_WORKSTATION) {
                    dist = "Windows Vista";
                } else {
                    dist = "Windows server 2008";
                }
            } else if(osvi.dwMinorVersion == 1) {
                 if (osvi.wProductType == VER_NT_WORKSTATION)
                    dist = "Windows 7";
                 else
                    dist = "Windows server 2008 R2";
            }  else if (osvi.dwMinorVersion == 2) {
                if (osvi.wProductType == VER_NT_WORKSTATION)
                    dist = "Windows 8";
                else
                    dist = "Windows Server 2012";
            }
        } else {
            dist = "Windows";
        }
        
        std::ostringstream stream;
        stream << osvi.dwMajorVersion << "." << osvi.dwMinorVersion 
            << "." << osvi.dwBuildNumber;
        kernel = stream.str();
        dayu::OsInfo* os = nodeInfo.mutable_os();
        os->set_dist(dist);
        os->set_kernel(kernel);
    }

    return true;
}
#else
bool getnodeinfo(dayu::NodeInfo& nodeInfo)
{
    // Set network info;
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) != -1) {
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
                if (s == 0) {
                    std::string ifn = ifa->ifa_name;
                    std::string ip = host;
                    dayu::NicInfo* nicInfo = nodeInfo.add_nic();
                    nicInfo->set_interface(ifn);
                    nicInfo->set_ip(ip);
                }
            }
        }
    }

    if (ifaddr) {
        freeifaddrs(ifaddr);
    }

    // Set cpu info;
    const char* file = "/proc/cpuinfo";
    std::ifstream fin;
    std::string line;
    std::vector<std::string> linestr;

    fin.open(file, std::ios_base::in);
    if (fin.is_open()) {
        while (getline(fin, line)) {
            linestr.push_back(line);
        }
    }
    fin.close();

    int threads = 0;
    std::string key = "";
    std::string value = "";
    std::string vendor = "";
    std::string product = "";
    std::string cores = "";
    std::string speed = "";
    std::string bits = "";
    size_t pos = 0;

    for (unsigned int i = 0; i < linestr.size(); i++) {
        pos = linestr[i].find(":");
        // means until the end of the string
        if (pos == std::string::npos) { 
            continue;
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
            continue;
        } else if (key == "model name") {
            product = value;
            continue;
        } else if (key == "cpu MHz") {
            speed = value;
            speed += "MHz";
            continue;
        } else if (key == "cpu cores") {
            cores = value;
            continue;
        } else if (key == "flags") {
            if (boost::contains(value, "lm"))
                bits = "64";
            else {
                bits = "32";
            }
            continue;
        }
    }
     
    dayu::CpuInfo* cpuInfo = nodeInfo.add_cpu();
    cpuInfo->set_vendor(vendor);
    cpuInfo->set_product(product);
    cpuInfo->set_cores(cores);
    cpuInfo->set_threads(Convertor::val2Str(threads));
    cpuInfo->set_speed(speed);
    cpuInfo->set_bits(bits);
    
    // Set mem info;
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    if (pages != -1 || page_size != -1) {
        std::string meminfo = Convertor::val2ReadableStr(
            pages * page_size, 1024);
        nodeInfo.set_mem(meminfo);
    }

    // Set os info;
    struct utsname name;
    uname(&name);
    std::string dist = "";
    fin.open("/etc/issue", std::ios_base::in);
    if (fin.is_open()) {
        getline(fin, dist);
    }
    fin.close();
    dayu::OsInfo* os = nodeInfo.mutable_os();
    if (dist == "") {
        os->set_dist(name.sysname);
    } else {
        os->set_dist(dist);
    }
    os->set_kernel(name.release);

    return true;
}
#endif

void get_hostname(std::string& hostname)
{
    char name[255];
    int ret = gethostname(name, 255);
    if (ret != -1) {
        hostname = name;
    }
}
