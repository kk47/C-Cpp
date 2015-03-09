#include <iostream>

using namespace std;

int main()
{
    int a;
    int &b = a;

    b = 100;
    cout << a << endl;

    cout << &a << endl;
    cout << &b << endl;

    return 0;
}
