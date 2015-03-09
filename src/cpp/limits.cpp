#include <iostream>
#include <climits>

int main()
{
    using namespace std;
    int n_int = INT_MAX;
    short n_short = SHRT_MAX;
    long n_long = LONG_MAX;

    cout << sizeof(int) << endl;
    cout << sizeof(short) << endl;
    cout << sizeof(long) << endl;

    cout << "------MAX-----------" << endl;
    
    cout << n_int << endl;
    cout << n_short << endl;
    cout << n_long << endl;

    cout << "Minimum:" << INT_MIN << endl;
    cout << "Bits per byte:" << CHAR_BIT << endl;
    
    return 0;
}
