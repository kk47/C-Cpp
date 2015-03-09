#include<stdio.h>

int main()
{
    int i, j;
    for(i=1; i<=9; i++){
        for(j=1; j<=i; j++){
            printf("%-3d", i*j); //-3d stand of interger and take 3 character width, go right
        }
        printf("\n");
    }
    return 0;
}
