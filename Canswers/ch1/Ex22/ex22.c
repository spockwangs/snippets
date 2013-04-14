/*********************************************************************
 * K&R Exercise 1-22
 *      Write a program to "fold" long input lines into two or more
 *      short lines after the last non-blank character that occurs
 *      before the n-th column of input.
 *
 *********************************************************************/

#include <stdio.h>
#include <string.h>

#define TEXTWIDTH  20 
#define TABSTOP     8

int main(void)
{
    int c;
    int col;    /* current column of input */
    char line[TEXTWIDTH+1]; /* store word */
    int i, j;
    
    col = 0;
    i = 0;
    while ((c = getchar()) != EOF) {
        col++;
        if (c == ' ' || c == '\t' || c == '\n') {
            if (i > 0) {    /* we have a word in 'line' */
                line[i] = '\0';
                if (col-1 > TEXTWIDTH) {
                    printf("\n%s", line);
                    col = i;
                    i = 0;
                } else {
                    printf("%s", line);
                    i = 0;
                }
            } 
            if (col <= TEXTWIDTH) {
                putchar(c);
                if (c == '\t') {
                    col = ((col-1)/TABSTOP+1) * TABSTOP;
                } else if (c == '\n') {
                    col = 0;
                }
            } else {
                if (c == '\t') {
                    putchar('\n');
                    putchar('\t');
                    col = TABSTOP;
                } else if (c == '\n') {
                    putchar('\n');
                    col = 0;
                } else {
                    putchar('\n');
                    putchar(' ');
                    col = 1;
                }
            }
        } else {    /* we get a non-blank character */
            if (col <= TEXTWIDTH) {
                line[i++] = c;
            } else {
                if (i < TEXTWIDTH) {
                    putchar('\n');
                    line[i++] = c;
                    col = i;
                } else {
                    line[i] = '\0';
                    printf("%s\n", line);
                    i = 1;
                    col = 1;
                    line[0] = c;
                }
            }
        }
    }
    /* cope with the situation that the file don't end with newline */
    for (j = 0; j < i; j++) {
        putchar(line[j]);
    }

    return 0;
}
