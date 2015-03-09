#include <sys/stat.h>
#include <iostream>

int main()
{
    struct stat sb;
    
    int ret = stat("/mnt/dayu", &sb);
     
    if ((ret == 0) && (S_ISDIR(sb.st_mode))) {
        uid_t uid = sb.st_uid;
        gid_t gid = sb.st_gid;

        std::cout << uid << ":" << gid << std::endl;
    } else {
        std::cout << "not a dir" << std::endl;
    }
    return 0;
}
