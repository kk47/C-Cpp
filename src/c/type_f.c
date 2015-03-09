#include<stdio.h>

int main(void){
    float a,b;
    float x,f=5.75;
    double y;
    printf("conv_f=%d,f=%f\n",(int)f,f);
    x=33333.33333;
    b=33333.33333333333333;
    printf("x=%f\ny=%f\n",x,y);
    a=123456.789e5;
    b=a+20;
    printf("a=%f\n",a);
    printf("b=%f\n",b);
    printf("c=%f\n",1.0/3*3);
    return 0;
}
