#include <iostream>

double add(double x, double y);
double calculate(double a, double b, double (*pf)(double, double));

int main()
{
    double o = 10.0;
    double p = 20.0;
    double q;
    q = calculate(o, p, add);    
    std::cout << q << std::endl;
    return 0;
}

double add(double x, double y){
    return x+y;
}
double calculate(double a, double b, double (*pf)(double, double)){
    return (*pf)(a, b);
}
