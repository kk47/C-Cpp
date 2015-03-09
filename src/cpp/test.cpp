#include <iostream>
#include <stdint.h>
#include <errno.h>

using namespace std;
struct rec {
    int x;
    int y;
};

void test()
{
    cout << "this is a.x:" << a.x << endl; 
}
int main()
{
    uint32_t o;
    uint64_t p;
    long q;
    ulong f;

    rec a = {10, 20};
    rec* b;
    b = &a;

    cout << "uint32_t:" << sizeof(o) <<"\nuint64_t:"<< sizeof(p) << endl;
    cout << sizeof(q) << endl;
    cout << "f size :" << sizeof(f) << endl;
    cout << sizeof(int) << endl;
    cout << a.x << a.y << endl;
    cout << b->x << b->y << endl;
    cout << EEXIST << endl;
    return 0;
}
