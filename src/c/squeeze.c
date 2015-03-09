#include <stdio.h>

int squeeze(char s1[], char s2[]);
char st3[20];

int main(void)
{
    char s1[20];
    char s2[20];

    printf("Please input 2 string:");
    scanf("%s,%s", s1, s2);
    printf("s1=%s,s2=%s", s1, s2);
    squeeze(s1,s2);
    printf("%s\n", st3);
    return 0;
}

int squeeze(char st1[], char st2[])
{
    int i;
    int j;
    
    i = 0;
    while ( st1[i] != '\0' ){
        i++;
        j = 0;
        while ( st2[j] != '\0' && st1[i] != st2[j] )
            st3[i] = st2[i];
        }
}
