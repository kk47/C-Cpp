#include <iostream>
#include <string>

using namespace std;

int main()
{
    char array1[20];
    char array2[20] = "kuangkai";

    string st1;
    string st2 = "handsome boy";

    cout << "Enter array1: \n";
    cin >> array1;
    cout << "Enter st1: \n";
    cin >> st1;

    cout << array1 << array2 << st1 << st2 << endl;
    cout << array2[3] << st2[3] << endl;

    return 0;
    
}
