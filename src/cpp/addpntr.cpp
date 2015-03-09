#include <iostream>

int main()
{
    using namespace std;
    double wages[3] = {10000.0, 20000.0, 30000.0};
    short stacks[3] = {3, 2, 1};
    
    double* pw = wages;
    short* ps = &stacks[0];

    cout << pw << " " << *pw << endl;
    pw = pw + 1;
    cout << pw << " " << *pw << endl;
    
    cout << ps << " " << *ps << endl;
    ps = ps + 1;
    cout << ps << " " << *ps << endl;

    cout << stacks[0] << stacks[1] << endl;
    cout << *stacks << *(stacks + 1) << endl;

    cout << sizeof(wages) << sizeof(pw) << endl;
    return 0;
}
