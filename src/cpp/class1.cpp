#include <iostream>
#include "class.h"

using namespace std;

CA::CA() {
    a = 0;
    cout << "Construction: " << a << endl;
}

CA::~CA() {
    cout << "Destruct: " << a << endl;
}

void CA::setA(int x) {
    a = x;
}

void CA::print() {
    cout << "print: " << a << endl;
}

int main()
{
    CA ca;
    ca.setA(10);
    ca.print();

    return 0;
}
