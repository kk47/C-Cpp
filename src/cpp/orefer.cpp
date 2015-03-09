#include <iostream>

using namespace std;

class myclass {
    int who;
    
public:
    myclass(int n) {
        who = n;
        cout << "构造函数调用" << who << endl;
    }
    ~myclass() {
        cout << "析构函数调用" << who << endl;
    }

    int id() {
        return who;
    }
        
};

void f1(myclass o) {
    cout << "external function call" << o.id() << endl;
}

void f2(myclass *o) {
    cout << "external function call" << o->id() << endl;
}

void f3(myclass &o) {
    cout << "external function call" << o.id() << endl;
}

int main()
{
    myclass x1(1);
    f1(x1);
    cout << "---------" << endl;

    myclass x2(2);
    f2(&x2);
    cout << "---------" << endl;

    myclass x3(3);
    f3(x3);
    cout << "---------" << endl;
    
    return 0;
}

















