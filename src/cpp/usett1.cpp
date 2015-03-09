#include <iostream>
#include "tabtenn1.h"

int main()
{
    using std::cout;
    using std::endl;
    TableTennisPlayer player1("kk", "keven", false);
    RatedPlayer rplayer1(1140, "lili", "kasrin", true);
    player1.Name();
    if(rplayer1.HasTable())
        cout << " has a table\n";
    else
        cout << " hasn't a tablei\n";

    cout << "Name:";
    rplayer1.Name();
    cout << ": rating " << rplayer1.Rating() << endl;
    RatedPlayer rplayer2(1212, player1);
    cout << "Name:";
    rplayer2.Name();
    cout << ": Rating: " << rplayer2.Rating() << endl;

    return 0;
}
