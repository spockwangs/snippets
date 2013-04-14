/******************************************************************************
 * K&R Exercise 4-13
 *      Write a recursive version of the function reverse(s), which reverses
 *      the string s in place.
 *
 * Authro: wbb
 * Date: 2009-08-12
 */


#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

/* function declarations */
char *reverse(char s[]);


int main(void)
{
    char buf[BUFSIZE];

    printf("Enter a string: ");
    scanf("%s", buf);
    printf("Its reversive version: %s\n", reverse(buf));

    return 0;
}


char *reverse(char s[])
{
    int i, j, t;

    i = 0, j = strlen(s) - 1;
    if (s == NULL || *s == '\0')
        return s;
    while (j > i) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
    return s;
}

