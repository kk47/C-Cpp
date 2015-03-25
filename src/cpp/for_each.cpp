#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/foreach.hpp>

using namespace std;

template <class T>
void FillValue(T& vect, int first, int last)
{
    if(last >= first) {
        for(int i = first; i<= last; ++i)
            vect.insert(vect.end(), i);
    } else {
        cout << " The indexes is error: last < first." << endl;
    }
}

void print(int elem)
{
    cout << elem << " ";
}

int main()
{
    vector<int> myvector;
    FillValue(myvector, 1, 10);
    for_each(myvector.begin(), myvector.end(), print);
    cout << endl;
    BOOST_FOREACH(int item, myvector) {
        if (item > 5) {
            cout << item << " is big than 5" << endl;
        } else {
            cout << item << " is small than 5" << endl;
        }
    }

    return 0;
}
