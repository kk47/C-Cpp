#include <iostream>
#include <string>
#include <vector>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
// compile command :
//  g++ threadsafe_cout.cpp -I /dayudep/trunk/include/ /dayudep/trunk/lib/libboost_date_time.a /dayudep/trunk/lib/libboost_thread.a -lpthread

boost::mutex mutex;

class Print{
public:
    static void exec(std::string content)
    {
        boost::mutex::scoped_lock lock(mutex);
        std::cout<<"Hello  "<<boost::this_thread::get_id() << content << std::endl;
    }

    void operator <<(std::ostream& s);
};

void Print::operator <<(std::ostream& s)
{
    ostream 
}

void nsexec(std::string content)
{
    //boost::mutex::scoped_lock lock(mutex);
    std::cout << "unsafe cout : " << content << std::endl;
}


int main()
{
    Print* printer;
    std::vector<boost::thread*> ths;
    std::string c = "haha";

    for (int i=0; i < 10; i++) {
        ths.push_back(new boost::thread(boost::bind(printer->exec, c)));
    }

    /*for (int i=0; i < 10; i++) {
        ths.push_back(new boost::thread(boost::bind(nsexec, c)));
    }*/

    for (int i=0; i < 10; i++) {
        ths[i]->join();
    }

    for (int i=0; i < 10; i++) {
        delete ths[i];
    }
    
    return 0;
}
