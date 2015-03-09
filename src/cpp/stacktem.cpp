#include <iostream>
#include <string>
#include <cctype>
#include "stacktp.h"
using std::cin;
using std::cout;

int main()
{
    Stack<std::string> st;
    char ch;
    std::string po;
    cout << "A add,P process, Q quit.\n";
    while (cin >> ch && std::toupper(ch) != 'Q'){
        while (cin.get() != '\n')
            continue;
        if (!std::isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch(ch)
        {
            case 'A':
            case 'a':cout << "PO number: ";
                cin >> po;
                if (st.isfull())
                    cout << "stack already full\n";
                else
                    st.push(po);
                break;
            case 'P':
            case 'p': if (st.isempty())
                    cout << "stack already empty\n";
                else{
                    st.pop(po);
                    cout << "PO #" << po << " popped\n";
                    break;
                }
        }
        cout << "A P Q \n";
    }
    cout << "Bye\n";
    return 0;
}
