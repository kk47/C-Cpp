#include <iostream>
#include <complex>
#include "convert.hpp"

using namespace std;

int main()
{
    int i = 1234;
    float j = 567.90;
    complex<float> c(1.4, 4.1);
    cout << "i==\"" << toString(i) << "\"" << endl;
    cout << "j==\"" << toString(j) << "\"" << endl;
    cout << "c==\"" << toString(c) << "\"" << endl;

    i = fromString<int>(string("1234"));
    j = fromString<float>(string("569.21"));
    c = fromString<complex<float> >(string("(2.4,5.1)"));
    cout << i << endl;
    cout << j << endl;
    cout << c << endl;

    return 0;
}

