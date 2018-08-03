#include <iostream>
#include <vector>

int main() {
    /*std::vector<int> first;
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
    test.pop_back();*/
    std::vector<int> vec ;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    for(int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << std::endl;
    }
    return vec[1] = 4;
}
