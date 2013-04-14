#include <stdio.h>

#define MAXLINE     1000

int main()
{
    int i, c, lim;
    char s[MAXLINE];

    lim = MAXLINE;
    i = 0;
    while (i < lim-1) {
        c = getchar();
        if (c == '\n')
            break;
        if (c == EOF)
            break;
        s[i++] = c;
    }
    s[i] = '\0';

    return 0;
}
