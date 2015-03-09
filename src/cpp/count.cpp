#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
void FillValue(T& vect, int first, int last)
{
    if (last >= first) {
        for (int i = first; i <= last; i++) {
            vect.insert(vect.end(), i);
        }
    } else {
        cout << " error: last < first. " << endl;
    }
}

void print(int elem)
{
    cout << elem << " ";
}

bool isEven(int elem)
{
    return (elem % 2 == 0);
}

int main()
{
    vector<int> myvector;
    FillValue(myvector, 1, 10);
    for_each(myvector.begin(), myvector.end(), print);
    cout << endl;
    int ct = count(myvector.begin(), myvector.end(), 4);
    int ctif = count_if(myvector.begin(), myvector.end(), isEven);
    int ctg = count_if(myvector.begin(), myvector.end(), bind2nd(greater<int>(), 2));
    
    cout << "equal to 4: " << ct << endl;
    cout << "Even: " << ctif << endl;
    cout << "greater than 2 : " << ctg << endl;

    return 0;
}
