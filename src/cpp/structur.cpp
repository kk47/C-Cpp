#include <iostream>

struct inflatable
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    using namespace std;
    inflatable guest =
    {
        "Wite",
        1.88,
        29.0
    };
    inflatable pal = {"Black", 2.00, 30.99};
    cout << pal.name << endl;
    cout << guest.price + pal.price << endl;
    return 0;
}
