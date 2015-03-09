#include <iostream>

struct inflatable {
    char name[20];
    float volume;
    double price;
};

int main()
{
    using namespace std;
    inflatable* ps = new inflatable;
    cout << "name: ";
    cin.get(ps->name, 20);
    cout << "volume: ";
    cin >> (*ps).volume;
    cout << "price: $";
    cin >> ps->price;
    cout << (*ps).name << ps->volume << ps->price << endl;
    delete ps;
    return 0;
}
