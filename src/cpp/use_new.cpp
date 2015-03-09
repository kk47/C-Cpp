#include <iostream>

int main()
{
    using namespace std;
    int* pt = new int;
    *pt = 1001;
    cout << "int value = " << *pt << ": location = " << pt << endl;

    double* pd = new double;
    cout << "double value = " << *pd << ": location = " << pd << endl;
    cout << sizeof(pt) << sizeof(*pt) << endl;
    cout << sizeof(pd) << sizeof(*pd) << endl;

    return 0; 
}
