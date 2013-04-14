/**********************************************************************
 * K&R Exercise 2-8
 *     Write a function rightrot(x, n) that returns the value of the
 *     integer x rotated to the right by n bit positions.
 */

#include <stdio.h>

unsigned rightrot(unsigned x, int n)
{
    for (; n > 0; n--) {
        if ((x&1) == 1)
            x = (x>>1) | ~(~0u >> 1);
        else
            x = (x>>1);
    }

    return x;
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
