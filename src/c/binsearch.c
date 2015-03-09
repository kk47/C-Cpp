#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void)
{
    int v[20];
    int x=4;
    int n;
    binsearch();
    return 0
}

int binsearch(int x, int v[], int n)
{
    int low=0;
    int high=n-1;
    int mid;

    while (low <= high ){
        mid = (low + high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
