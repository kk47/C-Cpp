#include <iostream>
#include <vector>

int main() {
    std::vector<int> first;
    std::vector<int> second(4, 100);
    std::vector<int> third(second.begin(), second.end());
    std::vector<int> fourth(third);

    int myints[] = {15, 3, 64, 6};
    std::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for(std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';


    std::vector<int> test(1,3);
    test.push_back(4);
    test.push_back(11);
    std::cout << test.back() << std::endl;
    test.pop_back();
    std::cout << test.back() << std::endl;
    return 0;
}
