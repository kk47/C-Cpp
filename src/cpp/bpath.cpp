#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

int main() {
    std::string ps = "/usr/local/dayu/scripts"; 
    boost::filesystem::path p(ps);
    p /= "kk.py";
    
    std::cout << p.string() << std::endl;
    std::cout << p.stem() << std::endl;
    std::cout << p.parent_path() << std::endl;
    std::cout << p.filename() << std::endl;
    std::cout << p.extension() << std::endl;

    std::cerr << "Something error occurred." << std::endl;

    return 0;
}
