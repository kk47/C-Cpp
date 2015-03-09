#include <iostream>
#include <string>

using namespace std;
// <class T1> is the same as <typename T1>
template <class T1, class T2> void print(const T1& var1, const T2& var2)
{
    cout << var1 << "," << var2 << endl;
}

int main()
{
    string str("Hello beijing!");
    size_t num = str.length();
    print(str, num);
    //cin.get();
    return 0;
}
