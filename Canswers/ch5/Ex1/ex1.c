/* ex1.c 
 *
 * K&R Exercise 5-1
 *     As written, getint treats a + or - not followed by a digit
 *     as a valid representation of zero. Fix it to push such a
 *     character back on the input.
 */

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

const int debug = 0;

/* getfloat: get next int from input into *pn.
 * The int format is [+-][0-9]*
 */
int getint(int *pn)
{
    int c, sign, ret;

    ret = EOF - 1;

    /* skip white space */
    while (isspace(c = getchar()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetc(c, stdin);     /* bad format */
        return ret;
    } else if (c == EOF)
        return c;

    /* The sign part. */
    sign = (c == '-') ? -1 : 1;
    if (debug)
        printf("getfloat: sign = %d\n", sign);
    if (c == '+' || c == '-')
        c = getchar();

    /* The integer part. */
    *pn = 0;
    if (isdigit(c)) {
        ret = 0;
        for (; isdigit(c); c = getchar()) {
            *pn = 10 * (*pn) + (c - '0');
            if (*pn < 0)
                ret = EOF - 2;
        }
    }

    *pn *= sign;
    if (c != EOF) {
        ungetc(c, stdin);
        return ret;
    }
    return c;
}


int main(void)
{
    int r, n;

    n = 0;
    for (;;) {
        printf("Enter a string: ");
        r = getint(&n);
        if (r == EOF - 2) {
            printf("Overflow!\n");
        } else if (r == EOF - 1)
            printf("Bad format!\n");
        else if (r == EOF) {
            printf("\nByebye!\n");
            break;
        } else
            printf("The integer is: %d\n", n);

        /* Swallow all the remaining characters. */
        while (getchar() != '\n')
            ;
    }

    return 0;
}

