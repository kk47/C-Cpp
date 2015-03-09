#include <iostream>
#include <string>

using namespace std;

class stuff {
    string name;
    int age;
public:
    stuff(string n, int a):name(n), age(a)
    {
        cout << name << "---" << age << endl;
    }

    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }

    void operator +(int x);
    void operator +(string s);
};

void stuff::operator +(int x)
{
    age = age + x;
}

void stuff::operator +(string s)
{
    name = name +s;
}

int main()
{
    stuff st2("c language website", 3);
    st2 + 2;
    st2 + ".c++ 60 minute primer course";
    cout << st2.getName() << st2.getAge() << endl;

    return 0;
}

















