#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f1;
    if (!f1.is_open()) {
        cout << "not open" << endl;
    } else {
        cout << "opened" << endl;
    }
    ofstream f2;
    char filename1[256];
    char filename2[256];
    char content[256];

    cout << "source file:";
    cin >> filename1;
    cout << "dest file:";
    cin >> filename2;
    f1.open(filename1, ios::in);
    f2.open(filename2, ios::out);
    while(!f1.eof()) {
        f1.getline(content, 128);
        f2 << content  << endl;
    }
    f1.close();
    f2.close();
    return 0;
}

