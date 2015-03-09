#include <stdio.h>

#define MAXLINE 1000

int cut(char line[]);

main()
{
    int i, len;
    
    while (( len = getline(line, MAXLINE)) > 500)
        cut();
    print("%s", line)
    return 0;
}


