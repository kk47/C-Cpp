#include <iostream>
#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>


typedef boost::mt19937 randeng;
typedef boost::uniform_int<uint64_t> intdis;
typedef boost::variate_generator<randeng, intdis > intrand;

static intrand unifomRandomGenerator(uint64_t min, uint64_t max)
{
    randeng eng;
    eng.seed(static_cast<uint64_t>(time(NULL)));
    intdis dis(min, max);
    return intrand(eng, dis);
}

int main()
{
    uint64_t min = 1;
    uint64_t max = 10;
    intrand die = unifomRandomGenerator(min, max);
    for (int i=0; i <= 5; i++) {
        std::cout << die() << std::endl; 
    }
    return 0;
}
