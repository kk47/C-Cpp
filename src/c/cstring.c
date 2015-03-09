#include <stdio.h>

int strlens(char s[]);
int atoi(char s[]);
int lowers(char s[]);

int main(void)
{
    char a[30];
    int len;
    int nu;

    printf("Input a string:");
    scanf("%s",a);
    len = strlens(a);
    nu = atoi(a);
    c = lowers(a);
    printf("atoi number is: %d\n", nu);
    printf("The length of string is %d\n", len);
    return 0;
}

int strlens(char s[])
{
    int i;

    i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
