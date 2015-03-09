#include <iostream>

using namespace std;

namespace na
{
    void print(int n) {
        cout << "na::print: " << n << endl;
    }
}

namespace nb
{
    void print(int n) {
        cout << "nb::print: " << n << endl;
    }
}

namespace na
{
    void print2(int a, int b) {
        print(a);
        print(b);
    }
}

int main()
{
    na::print(3);
    nb::print(4);
    na::print2(5, 6);

    return 0;
}
