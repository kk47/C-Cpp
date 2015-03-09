#include <stdio.h>

unsigned bitcount(unsigned x);

int main(void)
{
    unsigned int x = 100;
    bitcount(x);
    return 0;
}

unsigned bitcount(unsigned x)
{
    int b;
    while ( x > 0){
        x &= x-1;
        b++;
    }
    printf("%d\n", b);
}
