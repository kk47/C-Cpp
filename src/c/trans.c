#include <stdio.h>

unsigned long int next = 1;

int rand(void);
void srand(unsigned int seed);

int main(void)
{

    int res;

    res = rand();
    printf("%d", res);
    return 0;

}

int rand(void)
{
    
    next = next * 1103515246 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}
