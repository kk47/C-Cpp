#include <iostream>
#include <boost/thread.hpp>

int main()
{
    std::cout << boost::thread::hardware_concurrency();
    return 0;
}
