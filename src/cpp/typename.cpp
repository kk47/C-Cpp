#include <iostream>

template <class T> 
class Table {
    typename T::iter t;
public:
    explicit Table(const typename T::iter& ti): t(ti) 
    {}

    void show() {
        typename T::iter* y;
        y = &t;
        std::cout << (*y)->p << std::endl;
    }
};

class card {
public:
    typedef card* iter;
    int p;
    card(int pos) : p(pos)
    {}
};

int main()
{
    card pc(3);
    Table<card>S_Table(&pc);
    S_Table.show();
    return 0;
}
