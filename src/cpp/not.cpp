#include <iostream>
#include <climits>

bool is_int (double);
int main()
{
    using namespace std;
    double num;

    cout << "integer:";
    cin >> num;
    while (!is_int(num)){
        cout << "out of range, again:";
        cin >> num;
    }
    int val = int(num);
    cout << "integer" << val << "\nBye\n";
    return 0;
}

bool is_int (double x){
    if (x < INT_MAX && x >= INT_MIN)
        return true;
    else
        return false;
}
