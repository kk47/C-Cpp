#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <fcntl.h>

int main ()
{
    int physsectsize = 0;
    int fd = open("/dev/sdb", O_RDONLY | O_NONBLOCK);
    if (fd < 0)
        return false;
    if (ioctl(fd, _IO(0x12,123), &physsectsize) != 0)
        physsectsize = 0;

    std::cout << physsectsize << std::endl;
}

