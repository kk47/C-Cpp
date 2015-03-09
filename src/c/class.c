#include <iostream>

using namespace std;

class CA {
    int a;
public:
    CA() {
        a = 0;
        cout << "constraction: " << a << endl;
    }
    ~CA() {
        cout << "destruct: " << a << endl;
    }

    void setA(int x) {
        a = x;
    }

    void print() {
        cout << "print: " << a << endl;
    }
};

int main() {
    CA ca;

    ca.setA(10);
    ca.print();

    return 0;
}
