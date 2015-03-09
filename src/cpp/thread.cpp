#include <iostream>
#include <boost/thread.hpp>

boost::mutex io_mutex;

/*struct count {
    count(int id): id(id) {}
    void operator()() {
        for (int i = 0; i<10; ++i) {
            boost::mutex::scoped_lock lock(io_mutex);
            std::cout << id << ":" << i << std::endl;
        }
    }
    int id;
};

void hello()
{
    std::cout << "Hello world, I'm a thread!" << std::endl;
}*/

void count(int id) {
    for (int i=0; i<10; ++i) {
        boost::mutex::scoped_lock lock(io_mutex);
        std::cout << id << ":" << i << std::endl;
    }
}

int main() 
{
    boost::thread thrd1(boost::bind(&count, 1));
    boost::thread thrd2(boost::bind(&count, 2));
    thrd1.join();
    thrd2.join();
    return 0;
}
