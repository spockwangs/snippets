/**********************************************************
 * Count blanks, tabs and newlines from standard input.
 */

#include <stdio.h>

int main(void)
{
    int nb;     /* blanks */
    int ntab;   /* tabs */
    int nl;     /* newlines */
    int c, lastchar;

    nb = 0;
    ntab = 0;
    nl = 0;
    lastchar = 0;
    while ((c = getchar()) != EOF) {
        lastchar = c;
        switch (c) {
            case ' ':
                nb++;
                break;
            case '\t':
                ntab++;
                break;
            case '\n':
                nl++;
                break;
            default:
                break;
        }
    }
    /* Sometimes text files might not end with a newline. */
    if (lastchar != '\n') {
        nl++;
    }
    printf("blanks: %d\ntabs: %d\nnewlines: %d\n",
            nb, ntab, nl);

    return 0;
}
