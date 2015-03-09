#include <vector>
#include <iostream>
#include <boost/assign.hpp>

int main()
{
    using namespace std;
    using namespace boost::assign;
    std::vector<int> numbers = list_of(1)(2)(3)(10);
    
    for(int i=0; i<numbers.size(); i++) {
        cout << numbers[i] << endl;
    }
    return 0;
}
