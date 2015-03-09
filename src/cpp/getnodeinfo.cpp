#include <iostream>
#include <string>
#include <stdlib.h>
#include <arpa/inet.h>
#include <boost/asio.hpp>
#include <netdb.h>

#define NET_ADDR 16

int main()
{
    struct hostent* host;
    char ip[NET_ADDR];
    int i;
    char h_aliases[100];
    int h_addrtype;
    char h_addr_list[100];

    host = gethostent();
    if(host == NULL) {
        std::cerr << "failed to get host's info" << std::endl;
        exit(1);
    }

    std::cout << host->h_name << std::endl;
    for(i = 0; host->h_aliases[i] != NULL; i++)
        std::cout << h_aliases << std::endl;
    
    if(host->h_addrtype == AF_INET)
        std::cout << "af_inet" << std::endl;
    else
        std::cout << "unix_inet" << std::endl;

    for(i = 0; host->h_addr_list[i] != NULL; i++)
        inet_ntop(h_addrtype, host->h_addr_list[i], ip, NET_ADDR);
        std::cout << ip << std::endl;


    std::string hostname = boost::asio::ip::host_name();
    std::cout << "hostname is : " << hostname << std::endl;
    
    return 0;
}
