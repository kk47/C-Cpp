#include<stdio.h>

int max(int, int); //function declare

int main(){
    int a, b, n;
    printf("Input two integers:");
    scanf("%d|%d", &a, &b);
    n=max(a, b);
    printf("The max integer between %d and %d is %d.\n", a, b, n);
    return 0;
}

int max(int num1, int num2){
    if(num1>num2){
        return num1;
    }
    else{
        return num2;
    }
}
