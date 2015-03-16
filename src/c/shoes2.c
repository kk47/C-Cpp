#include <stdio.h>

#define SCALE 0.325
#define ADJUST 7.64

int main(void)
{
    double shoe, foot;

    printf("Shoe size (man's) foot length\n");
    shoe = 3.0;
    while (shoe < 18.5)
    {
        foot = SCALE*shoe + ADJUST;
        printf("%10.1f %15.2f inches\n", shoe, foot);
        shoe += 1.0;
    }
    printf("If the shoe fits, wear it.\n");
    return 0;
}