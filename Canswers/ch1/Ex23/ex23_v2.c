/**********************************************************************
 * K&R Exercise 1-23
 *      Write a program to remove all comments from a C program. Don't
 *      forget to handle quoted strings and character constants
 *      properly. C comments do not nest.
 *
 * This program has a state transition table stored in 'p[]'. The table
 * is divided to rows, each row has 4 characters. In each row the first
 * character represent curret state, the second is current input of
 * which '.' means any input other than '/', '"', ''' and '*'. The
 * third is some action depends on input and current state. The fourth
 * is next state.
 *
 * The whole program mimics a state transition in digital circuit.
 * Whenever get a input character, it perform some action according
 * to current state and the input and calculate next state.
 */

#include <stdio.h>

/* state transition table */
char p[] = "0/!1" 
           "0\"04"
           "0\'05"
           "0.00"
           "1/!8"
           "1*!2"
           "1\"/4"
           "1\'/5"
           "1./0"
           "2*!3"
           "2.!2"
           "3/!0"
           "3*!3"
           "3.!2"
           "4\"00"
           "4\\06"
           "4.04"
           "5\'00"
           "5\\07"
           "5.05"
           "6.04"
           "7.05"
           "8\n00"
           "8\\!9"
           "8.!8"
           "9.!8";

int main()
{
    int c, i, d;
    char s;     /* current state */
    char n;     /* next state */

    s = '0';    /* initial state */
    while ((c = getchar()) !=EOF){
        d = 0;
        for (i = 0; p[i] != '\0' && d == 0; i = i + 4) {
            if (p[i] == s && (p[i+1] == c || p[i+1] == '.')) {
                if (p[i+2] == '0') {
                    putchar(c);
                } else if (p[i+2] == '/') {
                    putchar('/');
                    putchar(c);
                } else if (p[i+2] == ' ')
                    putchar(' ');
                n = p[i+3];
                d = 1;
            }
        }
        s = n;
    }
    return 0;
}

