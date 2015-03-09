#include <iostream>

using namespace std;

int main()
{
    /*wchar_t kk = L'P';
    wcout << sizeof(kk) << endl;
    wcout << L"talk" << endl;
    */
    cout << "Year:\n";
    int year;
    cin >> year;
    cout << "address:\n";
    cin.get();
    char address[80];
    cin.getline(address, 80);
    cout << year << endl;
    cout << address << endl;
    return 0;
}
