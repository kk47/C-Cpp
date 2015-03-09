#include <iostream>
#include <string>

using namespace std;

class stuff {
    string name;
    int age;

public:
    /*stuff() {
        cout << name << "---" << endl;
        name = "space";
        age = 0;
        cout << name << "---" << age << endl;
    }*/
    
    stuff(string n, int a) :
        name(n),
        age(a)
    {
        cout << name << "---" << age << endl;
    }
    
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
};

int main()
{
//    stuff st2();
    stuff st1("c language website", 3);

    return 0;
}
