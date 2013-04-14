/*
 * missing1.c -- Solution 1 to Problem A of Column 2
 *   Find one missing integer in a file containing at most four
 *   billion 32-bit integergs in random order.
 *
 *   Use a bit vector to record integers seen so far.  After reading
 *   the whole input file we can tell which integers do not exist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BPW     32
#define SHIFT   5
#define MASK    0x1F
#define N       0xFFFFFFFF

uint32_t bits[1+N/BPW];

void set(uint32_t i)
{
    bits[i>>SHIFT] |= (1<<(i & MASK));
}

void clr(uint32_t i)
{
    bits[i>>SHIFT] &= ~(1<<(i & MASK));
}

int test(uint32_t i)
{
    return   bits[i>>SHIFT] &   (1<<(i & MASK));
}

int main(void)
{
    uint32_t i;

    while (scanf("%u", &i) != EOF)
        set(i);
    if (!test(0)) {
        printf("%u\n", 0);
        return 0;
    }
    for (i = 1; i != 0; i++) {
        if (!test(i)) {
            printf("%u\n", i);
            break;
        }
    }

    return 0;
}

