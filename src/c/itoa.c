#include <stdio.h>
#include <ctype.h>

int itoa(char s[]);

int main(void)
{
    char s[20];
    int d

    printf("Please input something:\n");
    scanf("%d", d);
    printf("number is:%d\n", itoa(d,s));
    return 0;
}

int itoa(char s[])
{
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}
