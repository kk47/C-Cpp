#include <iostream>
#include "complex0.h"

using namespace std;

Complex::Complex() {
    real = image = 0;
}

Complex::Complex(int r, int i) {
    real = r;
    image = i;
}

Complex Complex::operator+ (const Complex & c) const {
   Complex sum;
   sum.real = real + c.real;
   sum.image = image + c.image;
   return sum;
}

Complex Complex::operator- (const Complex & c) const {
    Complex minus;
    minus.real = real - c.real;
    minus.image = image - c.image;
    return minus;
}

Complex Complex::operator* (const Complex & c) const {
    Complex multi;
    multi.real = real * c.real - image * c.image;
    multi.image = real * c.image + image * c.real;
    return multi;
}

Complex Complex::operator* (const int m) const {
    Complex mu;
    mu.real = m * real;
    mu.image = m * image;;
    return mu;
}

Complex operator* (const int m, const Complex & c) {
    return c * m;
}

Complex Complex::operator~ () {
    this->image = -this->image;
    return *this;
}
ostream& operator<< (ostream& os, const Complex& c) {
    os << "(" << c.real << ", " << c.image << ")";
    return os;
}

istream& operator>> (istream& is, Complex& c) {
    cout << "real:";
    is >> c.real;
    cout << "imagianry:";
    is >> c.image;
    return is;
}
