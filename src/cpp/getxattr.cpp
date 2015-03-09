#include <iostream>
#include <sys/types.h>
#include <attr/xattr.h>
#include <boost/algorithm/string.hpp>

#include "cms.pb.h"

using namespace std;

int main()
{
    char value[XATTR_SIZE_MAX];
    uint buflen = XATTR_SIZE_MAX;

    string mntpnt = "/mnt/dayu/";
    int ret = getxattr(mntpnt.c_str(),
                       "dayu.client.statics",
                       value,
                       buflen);
    if(ret < 0) {
        int errcode = errno;
        cerr << strerror(errcode) << endl;
        return errcode;
    } else {
        cout << value << endl;
    }

    string status(value, ret);
    
    return 0;
}
