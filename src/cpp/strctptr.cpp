#include <iostream>
#include <cmath>

using namespace std;

struct polar{
    double distance;
    double angle;
};

struct rect{
    double x;
    double y;
};

void rect_to_polar(const rect* pxy, polar* pda);
void show_polar(const polar* pda);

int main()
{
    rect rplace;
    polar pplace;

    cout << "x, y:";
    while (cin>> rplace.x >> rplace.y){
        rect_to_polar(&rplace, &pplace);
        show_polar(&pplace);
        cout << "Next two number(q):";
    }
    cout << "Done.\n";
    return 0;
}

void show_polar(const polar* pda){
    const double Rad_to_deg = 21.34530945;
    cout << pda->
}
