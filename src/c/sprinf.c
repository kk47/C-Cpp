#include <stdio.h>
#include <stdlib.h>

int main()
{
    char buf[20];
    int id = 10;

    memset(buf, 0, 20);
    sprintf(buf + strlen(buf), "BUF: %d",id);
    // printf("%s",buf);
    return 0;

}
