#include <iostream>
#include "util/xorcrypt.hpp"

int main()
{
    std::string estr = "123456";
    std::string pass = encrypt(estr);
    std::cout << pass << std::endl;
    std::cout << decrypt(pass) << std::endl;
    return 0;
}
