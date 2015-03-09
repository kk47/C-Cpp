#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

namespace pt = boost::posix_time;


int main()
{
    pt::ptime t1 = boost::get_system_time();
    std::cout << t1 << std::endl;
    std::cout << time(NULL) << std::endl;

    return 0;
}
