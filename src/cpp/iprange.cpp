#include <iostream>
#include <string>

#include <boost/asio/ip/address_v4.hpp>
#include <boost/algorithm/string.hpp>

namespace ba = boost::asio::ip;

int main()
{
    std::string iprang = "192.168.174.0/24";

    ba::address_v4 ip;
    boost::system::error_code errno;
    ip = ba::address_v4.from_string("192.168.174.213", errno);
    std::cout << "GetIP - " << errno.message() << std::endl;
    std::cout << "IP: " << ip << std::endl;


    return 0;
}
