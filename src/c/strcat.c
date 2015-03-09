#include <stdio.h>

void strcats(char *s, char *t){

    while (*s++ != '\0')
        ;
    while ((*s++ = *t++) != '\0')
        ;
}

int main(void)
{
    char a[30];
    char b[10];
    printf("enter 2 string:");
    scanf("%s %s", a, b);
    strcats(a, b);
    printf("%s,%s\n", a, b);
    return 0;
}
