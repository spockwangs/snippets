/******************************************************************************
 * K&R Exercise 4-12
 *      Adapt the ideas of printd to write a recursive version of itoa,; that
 *      is, convert an integer into a string by calling a recursive routine.
 *
 * Author: wbb
 * Date: 2009-08-12
 */


#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>


char *itoa(int a, char s[], int base);
char *utoa(unsigned int a, char str[], int base);


int main(void)
{
    char s1[100], s2[100];
    int i, fail = 0;

    for (i = INT_MIN; i < INT_MAX-10000; i += 10000) {
        sprintf(s1, "%d", i);
        itoa(i, s2, 10);
        if (strcmp(s1, s2)) {  /* Not match */
            printf("Error:%d: %s, expect %s\n", i, s2, s1);
            fail++;
        }
        printf("%d\n", i);
    }

    if (fail == 0)
        printf("Pass all tests.\n");
    else 
        printf("%d failures.\n", fail);

    return 0;
}


char *itoa(int a, char str[], int base)
{
    assert(base >= 2 && base <= 36);

    if (a < 0) {
        *str = '-';
        utoa(-a, str+1, base);
    } else
        utoa(a, str, base);
    return str;
}


char *utoa(unsigned int a, char str[], int base)
{

    char s[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char *ps = str;

    assert(base >= 2 && base <= 36);

    *str = '\0';
    if (a >= (unsigned int)base)
        itoa(a/base, str, base);
    while (*str != '\0')
        str++;
    *str++ = s[a%base];
    *str = '\0';
    return ps;
}
