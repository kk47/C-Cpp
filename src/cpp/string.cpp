#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

int main()
{
    string s1 = "/mnt/dayu";
    string s2,s3,s4;
    s2 = s1;
    s2 = "/filetest/0/1";
    s3 = s1 + s2;
    s4 = "/mnt/dayu" + s2;
    s2 = "kk";
    char c = s1[s1.length() - 1];
    cout << s1 << ":" << s1.length() << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4.c_str() << endl;
    s2 += " for a day";
    cout << "s2 += \" for a day \" yields s2 = " << s2 << endl;


    return 0;
}
