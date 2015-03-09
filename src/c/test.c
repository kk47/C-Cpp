#include <stdio.h>

int main(void)
{
    int i;
    char c1='\v', c2='\t';

    for (i = 0 ; i < 10; i++)
        printf("%d%c",i, c1);
    for (i = 0 ; i < 10; i++)
        printf("%c%d\n", c2, i);
    return 0;
}
