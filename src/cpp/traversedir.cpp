#include <iostream>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main() {
    
    fs::path path("/mnt/dayu/11");
    fs::remove(path);
    /*
    boost::filesystem::recursive_directory_iterator iter(path.string());
    boost::filesystem::recursive_directory_iterator end;
    for (; iter != end; ++iter) {
        cout <<     
    }*/
    return 0;
}
    

