#include <iostream>

using namespace std;

int main()
{
    int a = 3450;
    int b = 3000;

    int c = (a % 1000) ? ( a - 3 * 1000) : 1000;
    int d = b % 100 ? (b / 100 + 1) : (b / 100);
    cout << "c: " << c << endl;
    cout << "d: " << d << endl;
    
    return 0;
}
