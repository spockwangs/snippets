/*******************************************************************
 * K&R: Exercise 1-21
 *  Write a program entab that replaces strings of blanks by
 *  minimum number of tabs and blanks to achieve the same 
 *  spacing.
 *******************************************************************/

#include <stdio.h>

int main(void)
{
    int c;
    int n = 8;
    int spacebegin, spaceend;   /* identify the column of the beginning
                                   and end of consecutive spaces */
    int col;         /* current column */
    int ntabstop;    /* number of tabstops needed */
    int nspace;      /* number of spaces needed */
    int i;

    spacebegin = spaceend = 0;
    col = 0;
    while ((c = getchar()) != EOF) {
        col++;
        if (c == ' ') {
            if (spacebegin == 0)
            spacebegin = col;
        } else {
            if (spacebegin != 0) {
                spaceend = col-1;
                ntabstop = spaceend/n - spacebegin/n;
                nspace = ntabstop == 0 ? 
                    spaceend-spacebegin+1 : spaceend % n;
                for (i = 0; i < ntabstop; i++) {
                    putchar('\t');
                }
                for (i = 0; i < nspace; i++) {
                    putchar(' ');
                }
                spacebegin = spaceend = 0;
            }
            putchar(c);
        }
        if (c == '\n')
            col = 0;
    }
        
    return 0;
}

