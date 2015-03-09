#include<stdio.h>

void chars(void);
void getch(void);

int main(void){
    /*char c;
    printf("input a character\n");
    c=getchar();
    putchar(c);
    chars(); */
    getch();
    return 0;
}

void chars(void){
    int a=15;
    double b=123555555678;
    double c=12345678.1234567;
    char d='p';
    printf("a=%d\n",a);
    printf("a(%%d)=%d, a(%%5d)=%5d, a(%%o)=%o, a(%%x)=%x\n\n",a,a,a,a);
}

void getch(void){
    int c,o;
    /*o = (getchar() != EOF);
    printf("%d",o);*/
    printf("EOF=%d",EOF);
    
    /*while ((c = getchar()) != EOF)
        putchar(c);*/
}
