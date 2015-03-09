#include <stdio.h>

int main(void){
    int c,nl=0,sl=0,tl=0;
    int count=0;

    c = getchar();
    while ((c = getchar()) != EOF){
        if (c == ' '){
            if (count == 0){
                count++;
                putchar(c);
            }
        else
            putchar(c);
        }
                
        /*    ++nl;
        else if (c == ' ')
            ++sl;
        else if (c == '\t')
            ++tl;
        else
            continue;
    printf("%d,%d,%d\n", nl,sl,tl);*/
    }
}
