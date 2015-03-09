#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    int lim = 20;
    char str1[] = "ch34o...";
    char str2[lim], c;
    
    printf("Please input a string(<=20):");
    for(i=0; i<lim -1 && (c=getchar()) != '\n' && c != EOF; ++i)
        str2[i] = c;
    
    while (isalnum(str2[i])) i++;
    printf("The first %d characters are alphanumeric.\n", i);
   
    i = 0;
    while (isalpha(str2[i])) i++;
    printf("The first %d characters are alpha.\n", i);
    
    i = 0;
    while (isblank(str2[i])) i++;
    printf("Last blank is %d.\n", i);

    i = 0;
    while (!iscntrl(str2[i])) {
        putchar(str2[i]);
        i++;
    }
    putchar('\n');

    i = 0;
    while (str2[i]) {
        c = str2[i];
        if (isupper(c)) { 
            c=tolower(c);
        } else if (islower(c)) { 
            c=toupper(c);
        }
        putchar(c);
        i++;
    }
    putchar('\n');

    char str3[] = "1776ad";
    int year;
    if (isdigit(str3[0])) {
        year = atoi(str3);
        printf("The year that followed %d was %d.\n",year,year+1);
    }
    
    FILE* pFile;
    int ch;
    pFile=fopen("myfile.txt", "r");
    if (pFile) {
        do {
            ch = fgetc(pFile);
            if (isgraph(ch) && !ispunct(ch)) putchar(ch);
        } while (ch != EOF);
        fclose(pFile);
    } else {
        printf("read file failed\n");
    }
    putchar('\n');
    
    return 0;
}
