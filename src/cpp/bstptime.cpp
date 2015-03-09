// compile : g++ bstptime.cpp -I /dayudep/branches/devel/boost/boost_1_57_0/ -lboost_system -L /dayudep/branches/devel/boost/boost_1_57_0/stage/lib/
#include <iostream>
#include <boost/date_time.hpp>
#include <boost/thread.hpp>

namespace pt = boost::posix_time;
using namespace std;

int main()
{
    pt::ptime t1 = pt::second_clock::universal_time();
    pt::ptime t2 = pt::second_clock::local_time();
    pt::ptime t3 = pt::microsec_clock::local_time();
    pt::ptime t0 = boost::get_system_time();
    pt::ptime t4(boost::gregorian::date(1970,1,1));

    cout << "UTC: " << (t0 - t4).total_seconds() << endl;
    cout << "universal_time: " << t1 << endl;
    cout << "local_time: " << t2 << endl;
    cout << "local_time in microsec: " << t3 << endl;
    return 0;
}
