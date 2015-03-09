#include <stdio.h>

unsigned setbits(unsigned x, unsigned y, int p, int n);

int main(void)
{
    unsigned int x = 100;
    unsigned int y = 178;
    int p = 4;
    int n = 2;
    setbits(x, y, p, n);
    return 0;
}

unsigned setbits(unsigned x, unsigned y, int p, int n)
{
    unsigned int y1,y2,xt;
    y1 = (~(( ~0 >> n ) << n)) << p-n;
    y2 = (y & (~(( ~0 >> n ) << n)))<< p-n;
    xt = (x & ~y1) | y2;
    printf("%d\n", xt);
}
