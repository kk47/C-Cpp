#include<stdio.h>

int main(void){
    int i=5,j=5,p,q;
    p=(i++)+(i++)+(i++);
    q=(++j)+(++j)+(++j);
    printf("p=%d,q=%d,i=%d,j=%d \n",p,q,i,j);
    return 0;
}
