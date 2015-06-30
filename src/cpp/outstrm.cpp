#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

void Display(vector<int>& v, const char* s);

int main()
{
    srandom(time(NULL));

    vector<int> kkvector(10);
    for (int i = 0; i < 10; i++)
        kkvector[i] = random() % 10000;

    Display(kkvector, "Before sorting");
    sort(kkvector.begin(), kkvector.end());
    Display(kkvector, "After sorting");
    return 0;
}

void Display(vector<int>& v, const char* s)
{
    cout << endl << s << endl;
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "\t"));
    cout << endl;
}
