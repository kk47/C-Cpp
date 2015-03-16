#include <stdio.h>
#include <stdlib.h>

void getptr(char* p)
{
    p = (char*)malloc(100);
}

int main()
{
    char* ptr = NULL;
    getptr(ptr);
    ptr[0] = 'a';
    ptr[1] = '\0';
    printf("%s", ptr);
    free(ptr);
    return 0;
}
