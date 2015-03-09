#include <iostream>
template <class Any>
void swap(any &a, any &b);

struct job{
    char name[40];
    double salary;
    int floor;
};

template <> void swap<job>(job &j1, job &j2);
void show(job &j);

int main()
{
    using namespace std;
    
}
