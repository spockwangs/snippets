/**********************************************************************
 * K&R Exercise 2-6
 *     Write a function invert(x, p, n) that returns x with the n bits
 *     that begin at position p inverted (i.e., 1 changed into 0 and
 *     vice versa), leaving others unchanged.
 */

#include <stdio.h>

int invert(unsigned x, int p, int n)
{
    unsigned y;

    y = ~((~0)<<n);
    y <<= p-n+1;
    return x ^ y;
}

int main()
{
    unsigned x;
    int p, n;

    p = 8, n = 3;
    printf("Input a x: ");
    scanf("%x", &x);
    printf("After invert: %#x\n", invert(x, p, n));

    return 0;
}
