#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

int main()
{
    const char* file = "/proc/cpuinfo";
    std::ifstream fin;
    std::string line;
    fin.open(file, std::ios_base::in);
    if (!fin.is_open()) {
        std::cout << "Failed to open file cpuinfo" << std::endl;
        return false;
    }
    
    int procnum = 0;
    int phynum = 0;
    size_t pos = 0;
    std::vector<std::string> linestr;
    std::string key = "";
    std::string value = "";
    
    
    while (getline(fin, line)) {
        linestr.push_back(line);
    }
    fin.close();
    for (unsigned int i = 0; i < linestr.size(); i++) {
        pos = linestr[i].find(":");
        if (pos != std::string::npos) { // means until the end of the string
            key = linestr[i].substr(0, pos);
            boost::trim(key);
            value = linestr[i].substr(pos + 1);
            boost::trim(value);
        }
        std::cout << key << std::endl;
    }
    
    return 0;
}
