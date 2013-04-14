/*
 * generate.c
 *   Generate a sample test file with k integers less than n without
 *   duplicates.  The k integers are in random order.
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bit.h"


static void usage(void)
{
    printf("Usage: gen k n\n");
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    int k, n, i;
    Bit_T bits;

    if (argc != 3)
        usage();

    k = atoi(argv[1]);
    n = atoi(argv[2]);
    srand(time(0));
    bits = Bit_new(n);
    for (i = 0; i < k; i++) {
        int j;
        do {
            j = rand()%n;
        } while (Bit_get(bits, j));
        Bit_put(bits, j, 1);
        printf("%d\n", j);
    }
    Bit_free(&bits);

    return 0;
}
