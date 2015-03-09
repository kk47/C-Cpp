#include <stdio.h>

#define MAXLINE 1000

/*int max;
char line[MAXLINE];
char longest[MAXLINE];

int getlines(void);
void copy(void);

main()
{
    int len;
    extern int max;
    extern char longest[];

    max = 0;
    while ((len = getlines()) > 0)
        if (len > max){
            max = len;
            copy();
        }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

int getlines(void)
{
    int c;
    int i;
    extern char line[];

    for (i = 0; i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    if (c == '\n'){
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void copy(void)
{
    int i;
    extern char line[], longest[];

    i = 0;
    while ((longest[i] = line[i]) != '\0')
        ++i;
}
*/
int getliness(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = getliness(line, MAXLINE)) > 0)
        if (len > max){
            max = len;
            copy(longest, line);
        }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

int getliness(char s[], int lim)
{
    int c, i;

    for (i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n'){
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
