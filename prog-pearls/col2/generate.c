/*
 * generate.c
 *   Generate n random integers.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


static void usage(void)
{
    printf("Usage: gen n\n");
    exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
    uint32_t n, i;

    if (argc != 2)
        usage();

    n = strtoul(argv[1], NULL, 10);
    srand(time(0));
    for (i = 0; i < n; i++) {
        printf("%u\n", ((unsigned int) rand()) & 0xFFFF);
    }

    return 0;
}
