#include <iostream>
#include <stdio.h>

using namespace std;
int main()
{
    int x = 3;
    int y = 10;
    char flag;
    cout << "Please enter flag:" << endl;
    scanf("%c", flag);
    switch(flag)
    {
        case "A":
            return x & y;
        case "B":
            return x | y;
        case "C":
            return !x ;
        case "D":
            return x != y ;
        case "E":
            return x == y ;
        case "F":
            return (!x) | y ;
    }
    
    return 0;
}
