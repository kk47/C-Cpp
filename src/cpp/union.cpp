#include <iostream>

union one4all {
    int int_val;
    float float_val;
    double double_val;
};

int main()
{
    using namespace std;
    one4all pail;
    pail.int_val = 12;
    cout << pail.int_val << endl;
    pail.double_val = 1.85;
    cout << pail.double_val << endl;
    return 0;

}
