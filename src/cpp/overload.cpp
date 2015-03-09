#include <iostream>

using namespace std;

float fun(float x);
double fun(double x);

int main()
{
    float f = 132.64;
    double d = 132.64;

    cout << fun(f) << endl;
    cout << fun(d) << endl;

    return 0;
}

float fun(float x) {
    return x / 2.0;
}

double fun(double y) {
    return y / 3.0;
}
