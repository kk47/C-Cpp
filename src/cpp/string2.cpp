#include <iostream>
#include <string>
#include <sstream>
#include <cstring>

int main()
{
    using namespace std;
    char charr1[20];
    char charr2[20] = "beijing";
    
    string st1;
    string st2 = "shanghai";

    st1 = st2;
    strcpy(charr1, charr2);
    st1 += " paste";
    strcat(charr1, " huangpu");

    int len1 = st1.size();
    int len2 = strlen(charr1);

    cout << "The string " << st1 << " contains " << len1 << " characters.\n";
    cout << "The string " << charr1 << " contains " << len2 << " characters.\n";

    // sstream stuff
    ostringstream outstr;
    string hdisk;
    cout << "name of your hdisk ";
    getline(cin, hdisk);

    int cap;
    cout << "capacity in GB ";
    cin >> cap;
    outstr << "The disk: " << hdisk << " has a capacity of " << cap << " gigabytes.\n";
    string result = outstr.str();
    cout << result;

    return 0;    
}
