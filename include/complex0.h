#ifndef COMPLEX0_H_
#define COMPLEX0_H_
#include <iostream>

class Complex {
public:
    int real;
    int image;

public:
    Complex();
    Complex(int r, int i);
    
    Complex operator+ (const Complex & c) const;
    Complex operator- (const Complex & c) const;
    Complex operator* (const Complex & c) const;
    Complex operator* (const int m) const;
    friend Complex operator* (const int m, const Complex & c);
    Complex operator~ ();
    friend std::ostream& operator<< (std::ostream& os, const Complex & c);
    friend std::istream& operator>> (std::istream& is, Complex & c);
};
#endif
