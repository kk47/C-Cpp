#include <iostream>
#include <string>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
    if(argc != 2) {
        std::cout << "./resolve hostname" << std::endl;
        return 1;
    }
    std::string hostname = argv[1];

    struct hostent* hent = NULL;
    hent = gethostbyname(hostname.c_str());
    if(hent != NULL) {
        struct in_addr** addr;
        addr = (struct in_addr**)hent->h_addr_list;
        for(int i = 0; addr[i] != NULL; ++i) {
            std::cout << inet_ntoa(*addr[i]) << std::endl;
        }
    } else {
        std::cout << "Failed to resolve hostname " << hostname << std::endl;
    }
    return 0;
}
