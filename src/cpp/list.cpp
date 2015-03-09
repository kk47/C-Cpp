#include <iostream>
#include <list>

int main() {
    using namespace std;
    list<int> a(1,2);
    list<int> b(2,3);
    a.push_back(5);
    a.push_back(9);
    list<int> c = a;
    // c = b;
    c.splice(c.end(), b);
 
    list<int>::iterator it = c.begin();
    //a.splice(a.end(), b);
    while(it != c.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
    return 0;
}
