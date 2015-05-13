#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void usage()
{
    std::cout << "./seekwrite position length filename" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc != 4) {
        usage();
        exit(1);
    }
    int pos = atoi(argv[1]);
    int len = atoi(argv[2]);
    char* fn = argv[3];
    int* buf = new int[len];
    memset(buf, 0, len);
    int fd = ::open(fn, O_CREAT | O_RDWR, 0644);
    if(fd < 0) {
        std::cerr << "failed to open " << fn << std::endl;
        return 1;
    } else {
        std::cout << "open mdslog.0" << std::endl;
    }
    lseek(fd, pos, SEEK_SET);
    if(::write(fd, buf, len) != len) {
        std::cerr << "failed to write " << std::string(fn) << std::endl;
    } else {
        std::cout << "write mdslog.0 success" << std::endl;
    }
    return 0;
}
