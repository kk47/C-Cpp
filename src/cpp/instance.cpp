#include <iostream>
#include <string>

using namespace std;

int main()
{
    string strA("c language website");
    cout << strA << " " << strA.length() << endl;

    string strB;
    strB = string("C++ primer course");
    cout << strB << " " << strB.length() << endl;

    string *strC;
    strC = new string("http://see.xidian.edu.cn/cpp/biancheng/cpp/jichu/");
    cout << *strC << " " << strC->length() << endl;
    delete strC;

    return 0;
}
