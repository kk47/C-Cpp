#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include <array>

int main()
{
    // construction user aggregate initialization
    std::array<int, 3> a1{{1, 2, 3}};
    std::array<int, 3> a2 = {2, 3, 4};
    std::array<std::string, 2> a3 = { {std::string("a"), "b"} };

    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
    for(auto& s: a3)
        std::cout << s << ' ';
}

