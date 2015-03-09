#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
void print(int& n) {
    cout << n << endl;
}
void print_v(vector<int>& v) {
    for_each(v.begin(), v.end(),print);
}
int main()
{
    int dim[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    vector<int> a;
    vector<int> c;
    list<vector<int> > d;
    a.assign(dim, dim+15);
    for(int i=0; i<9; i++) {
        cout << a[i] << endl;
    }
    cout << a.size() << endl;
    vector<int> b(a.begin(), a.begin()+4);
    cout << b.size() << endl;
    for (int j=1; j<=3; j++) {
        vector<int>::iterator start,end;
        start = b.end();
        if (j = 3) {end = b.end() + 4 * j;};
        vector<int> b(start, end);
        cout << b.size() << endl;
        //for_each(b.begin(),b.end(),print);
        //d.push_back(b);
    }
    
    //for_each(d.begin(),d.end(),print_v);

    //copy(a.begin(),a.begin()+5,back_inserter(c));
    //for_each(c.begin(),c.end(),print);
    return 0;
}
