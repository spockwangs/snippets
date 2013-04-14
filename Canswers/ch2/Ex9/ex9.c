/**********************************************************************
 * K&R Exercise 2-9
 *     In a two's complement number system, x &= (x-1) deletes the
 *     rightmost 1-bit in x. Explain why. Use this observation to write
 *     a faster version of bitcount.
 */

#include <stdio.h>

/* bitcount - count 1 bits in x
 * Note: this program work properly only in two's complement machine.
 */
int bitcount(unsigned x)
{
    int b = 0;

    while (x > 0) {
        x &= x-1;
        b++;
    }
    return b;
}

int main()
{
    unsigned x;

    printf("Input a x (hexdecimal): ");
    scanf("%x", &x);
    printf("Number of 1-bit in x is: %d\n", bitcount(x));

    return 0;
}

