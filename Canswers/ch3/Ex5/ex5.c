/*************************************************************************
 * K&R Exercise 3-5
 *     Write a function itob(n, s, b) that converts the integer n into
 *     a base b character representation in the string s. In particular
 *     itob(n, s, 16) formats n as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void reverse(char s[]);
int abs(int n);

int abs(int n)
{
    return n > 0 ? n : -n;
}

void itob(int n, char s[], int b)
{
    int i, sign, m;

    assert(s != NULL && b > 0);

    sign = 0;
    if (n < 0)
        sign = -1;
    i = 0;
    do {
        m = abs(n%b);
        if (m < 10)
            s[i++] = m + '0';
        else
            s[i++] = m - 10 + 'a';
    } while ((n /= b) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    int len;
    char tmp;

    assert(s != NULL);

    len = strlen(s);
    for (i = 0, j = len-1; i < j; i++, j--) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

int main()
{
    char s[100];
    int n, b;

    printf("Input a n: ");
    scanf("%d", &n);
    printf("Input a b: ");
    scanf("%d", &b);
    itob(n, s, b);
    printf("It is %s.\n", s);

    return 0;
}

