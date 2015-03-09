#include <stdio.h>
#include <string.h>

char s[20];

void reverse(char s[]);


int main(void)
{

    printf("Please input something:\n");
    scanf("%s", s);
    reverse(s, 0, strlen(s));
    printf("%s", s);
    return 0;
    
}

void reverse(char s[], int x, int y)
{

    if (s[x] > s[y]){
        swap(s, x, y)
        reverse(s, ++x, --y);
    } else
        reverse(s, ++x, --y);
}

void swap(int s[], int i, int j){
    
    int temp;

    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
