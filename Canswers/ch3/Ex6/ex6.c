/*************************************************************************
 * K&R Exercise 3-6
 *     Write a function of itoa that accepts three arguments instead of
 *     two. The third argument is a minimum field width; the converted
 *     number must be padded with blanks on the left if necessary to make
 *     it wide enough.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void reverse(char s[]);
int abs(int);

void itoa(int n, char s[], int width)
{
    int i, sign;

    assert (s != NULL && width > 0);

    sign = 0;
    if (n < 0)
        sign = -1;
    i = 0;
    do {
        s[i++] = abs(n%10) + '0';
    } while ((n /= 10) != 0);
    while (i < width) {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

/** reverse
 * 
 * Parameters:
 *     s is null-terminated string.
 */
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

int abs(int n)
{
    return n > 0 ? n : -n;
}

int main()
{
    int n;
    char s[100];

    printf("Input a integer: ");
    scanf("%d", &n);
    itoa(n, s, 5);
    printf("It is %s.\n", s);

    return 0;
}
