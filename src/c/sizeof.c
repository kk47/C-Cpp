#include<stdio.h>

int main(){
    short x;
    int a;
    long b;
    float f;
    double d;
    char c;
    printf("short:%d\nint:%d\nlong:%d\nfloat:%d\ndouble:%d\nchar:%d\n",sizeof(x),sizeof(a),sizeof(b),sizeof(f),sizeof(d),sizeof(c));
    return 0;
}
