#include <stdio.h>
#include <crypt.h>
#include <iostream>
#include <string>

int main()
{
    char *s;
    s = crypt("kk123", "$6$kOKvyIYo");
    std::cout << "crypt: " << s << std::endl;
    std::string splus = s;
    unsigned int found = splus.find_last_of('$');
    std::string salt;
    salt = splus.substr(0, found);
    char* authPass = crypt("kk123", salt.c_str());
    std::cout << "salt: " << salt << std::endl;
    std::cout << "athpass: " << authPass << std::endl;
    return 0;
}
