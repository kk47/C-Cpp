#include <iostream>
#include <string>
#include <fstream>
#include <sys/utsname.h>

int main()
{
    /*std::ifstream fin;
    std::string line = "";
    fin.open("/etc/issue", std::ios_base::in);
    if (fin.is_open()) {
        if (getline(fin, line)) {
            std::cout << line << std::endl;
        }
    }*/
    struct utsname name;
    uname(&name);
    std::cout << name.sysname << std::endl;
    std::cout << name.release << std::endl;

}
