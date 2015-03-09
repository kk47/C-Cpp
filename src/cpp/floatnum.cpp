#include <iostream>

int main()
{
    using namespace std;
    //cout.setf(ios_base::fixed, ios_base::floatfield);
    float x = 10.0/3.0;
    double y = 10.3/2.0; 

    const float m = 1.0e6;
    cout << x << "|||" << y << "|||" << m << endl;
    return 0;
}
