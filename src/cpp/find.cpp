#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
void FillValue(T& vect, int first, int last)
{
    if (last >= first) {
        for (int i = first; i <= last; ++i) {
            vect.insert(vect.end(), i);
        }
    } else {
        cout << " error last < first. " << endl;
    }
}

void print(int elem)
{
    cout << elem << " ";
}

int main()
{
    vector<int> mvect;
    FillValue(mvect, -3, 12);
    for_each(mvect.begin(), mvect.end(), print);
    cout << endl;
    vector<int>::iterator pos1;
    //pos1 = find(mvect.begin(), mvect.end(), 5);
    //vector<int>::iterator pos2;
    //pos2 = find_if(mvect.begin(), mvect.end(), bind2nd(greater<int>(), 3));
    //cout << distance(mvect.begin(), pos1) + 1 << endl;
    //cout << distance(mvect.begin(), pos2) + 1 << endl;
    
    pos1 = search_n(mvect.begin(), mvect.end(), 4, 3);
    if (pos1 != mvect.end()) {
        cout << distance(mvect.begin(), pos1) + 1 << endl;
    } else {
        cout << " there is no 4 numbers equal to 3. " << endl;
    }

    vector<int>::iterator pos2;
    pos2 = search_n(mvect.begin(), mvect.end(), 4, 3, greater<int>());
    if (pos2 != mvect.end()) {
        cout << distance(mvect.begin(), pos2) + 1 << endl;
    } else {
        cout << "there is no 4 numbers greater than 3. " << endl;
    }

    return 0;
}
