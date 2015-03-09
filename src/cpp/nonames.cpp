#include <iostream>

using namespace std;

namespace na {
    namespace {
        int sum(int a, int b)
        {
            return a + b;
        }
    }
    
    int calc(int x, int y)
    {
        return sum(x, y);
    }
}


int main()
{
    cout << na::calc(6, 23) << endl;
    
    return 0;
}
