#include <iostream>
#include <cctype>
#include "stack.h"

int main()
{
    using namespace std;
    Stack st;
    char ch;
    unsigned long po;
    cout << "Please enter A,P,Q:\n";
    
    while (cin >> ch && toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')
            continue;
        if(!isalpha(ch)){
            cout << '\a';
            continue;
        }
        switch(ch){
            case 'A':
            case 'a': cout << "Enter a po number to add: ";
                cin >> po;
                if (st.isfull())
                    cout << "Stack already full\n";
                else
                    st.push(po);
                break;
            case 'p': if (st.isempty())
                        cout << "PO #" << po << " popped\n";
                    else {
                        st.pop(po);
                        cout << "PO #" << po << " popped\n";
                    }
                    break;
        }
        cout << "Please enter A to add a purchase order. \n"
         << "P to process a PO, or Q to quit. \n";
    }
    cout << "Bye\n";
    return 0;
}
