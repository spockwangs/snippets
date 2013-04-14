/*
 * maxmem.c - Calculate max memory we can get from OS.
 *
 * Date: 2009-09-30
 * Author: wbb
 *
 * Compile
 *   gcc -W -Wall -ansi -pedantic maxmem.c
 */

#include <stdio.h>

const int debug = 1;

int main(void)
{
    unsigned i;
    unsigned long sum;
    void *sbrk(unsigned);

    i = 12;
    sum = 0;
    while (1) {
        if (sbrk((unsigned) 1<<i) == (void *) -1) {
            if (i > 0)
                i--;
            else
                break;
        } else
            sum += (unsigned) 1<<i;
    }
    printf("Max memory we can get from OS: %lu(MB)\n", sum/1024/1024);
    if (debug) {
        printf("And now program break is: %p\n", sbrk(0));
        printf("Stack bottom is: %p\n", (void *) &sum);
    }
    return 0;
}
