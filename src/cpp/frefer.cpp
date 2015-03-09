#include <iostream>

using namespace std;

void swap(int &x, int &y);

int main()
{
    int i = 12;
    int j = 25;

    cout << "i=" << i << " j=" << j << endl;

    swap(i, j);
    cout << "i=" << i << " j=" << j << endl;

    return 0;
}

void swap(int &x, int &y)
{
    int t;

    t = x;
    x = y;
    y = t;
}
