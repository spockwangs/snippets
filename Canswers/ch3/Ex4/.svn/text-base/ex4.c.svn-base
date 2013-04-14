/*************************************************************************
 * K&R Exercise 3-4
 *     In a two's complement number representation, our version of itoa
 *     does not handle the largest negative number. Explain why not.
 *     Modify it to print that value correctly, regardless of the machine
 *     on which it runs.
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

void reverse(char s[]);

int abs(int a)
{
    return a > 0 ? a : -a;
}

/* iota: convert n to characters in s */
void iota(int n, char s[])
{
    int i;
    int sign;

    sign = 0;
    if (n < 0)
        sign = -1;
    i = 0;
    do {
        s[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/**
 * reverse - reverse the character string in 's'
 *
 * Requires:
 *     s is a null terminated string.
 * Modifies:
 *     s
 */
void reverse(char s[])
{
    int len;
    int i;
    char tmp;

    len = strlen(s);
    assert(s[len] == '\0');
    for (i = 0; i < len/2; i++) {
        tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = tmp;
    }
}

int main()
{
    int n;
    char s[100];

    printf("Input a integer: ");
    scanf("%x", &n);
    n = INT_MAX;
    iota(n, s);
    printf("It is %s.\n", s);

    return 0;
}
