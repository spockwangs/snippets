/**********************************************************************
 * K&R Exercise 2-8
 *     Write a function rightrot(x, n) that returns the value of the
 *     integer x rotated to the right by n bit positions.
 */

#include <stdio.h>
#include <limits.h>

unsigned rightrot(unsigned x, int n)
{
    size_t s = sizeof(x) * CHAR_BIT;
    size_t p;

    p = n%s;
    if (x == 0 || p == 0)
        return x;
    return (x >> p) | (x << (s-p));
}

int main()
{
    unsigned x;
    int n;

    printf("Input x (hexdecimal): ");
    scanf("%x", &x);
    printf("Input n (decimal): ");
    scanf("%d", &n);
    printf("After rotating: %#x\n", rightrot(x, n));

    return 0;
}
