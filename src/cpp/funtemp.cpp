#include <iostream>

template <class Any>
void Swap(Any &a, Any &b);

int main()
{
    using namespace std;
    int i = 10;
    int j = 20;
    cout << i << j << endl;
    Swap(i, j);
    cout << i << j << endl;

    double x = 12.00;
    double y = 34.55;
    cout << x << y << endl;
    Swap(x, y);
    cout << x << y << endl;
    return 0;
}

template <class Any>
void Swap(Any &a, Any &b){
    Any temp;
    temp = a;
    a = b;
    b = temp;
}
