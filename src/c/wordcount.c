#include <stdio.h>

#define IN 1
#define OUT 0

int main(void){
    int c, nl, nw, nc, state;
    int i=0;
    state = OUT;
    nl = nw = nc = 0;
    c = getchar();
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    for (i = 0; i <= (nc*10)/nc; i++)
        print("")
    printf("%d %d %d\n", nl, nw, nc);
}
