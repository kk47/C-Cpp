#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    stack<int> st;
    vector<string> st1(10);
    for(int i = 0; i < 10; i++)
        st.push(i);
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    for(int j = 0; j < 10; j++) {
        cout << st1[j] << endl;
    }
    cout << endl;
    return 0;
}
