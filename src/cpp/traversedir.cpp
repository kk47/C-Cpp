#include <iostream>
#include <boost/filesystem>

namespace boost::filesystem fs



int main() {
    
    fs::path path("/mnt/dayu/11");
    boost::filesystem::recursive_directory_iterator iter(path.string());
    boost::filesystem::recursive_directory_iterator end;
    for (; iter != end; ++iter) {
        cout <<     
    }
}
    

