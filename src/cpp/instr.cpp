#include <iostream>

int main()
{
    using namespace std;
    const int arsize = 20;
    char name[arsize];
    char dessert[arsize];

    cout << "Enter you name:\n";
    cin.get(name, arsize);
    cout << "Enter your favorite dessert: \n";
    cin.get(dessert, arsize);
    cout << "I have some delicious " << dessert;
    cout << " for you, " << name << ".\n";
    return 0;
}
