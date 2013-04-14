/******************************************************************************
 * printprimes.c - print primes in increasing order
 *
 * 采用筛法打印某一范围内的所有质数。
 * 
 * Author: wbb
 * Date: 2009-04-29
 ******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

/* printPrimes - print all primes not larger than n and return number of
 * primes printed */
int printPrimes(int n)
{
    int *p;     /* to store primes not larger than n */
    int i, j, d, k;
    char s[21];     /* wide enough to store 64-bit integers */

    assert(n >= 2);

    p = (int *) malloc(n * sizeof(int));
    if (p == NULL) {
        fprintf(stderr, "error: malloc() failed\n");
        return -1;
    }
    j = 0;
    p[j++] = 2;
    for (i = 3; i <= n; i++) {
        d = 0;
        /* Is i a prime ? */
        for (k = 0; d == 0 && p[k]*p[k] <= i; k++) {
            if (i % p[k] == 0)
                d = 1;
        }
        if (d == 0)     /* yes, i is a prime */
            p[j++] = i;
    }

    /* print all primes 10 per line */
    printf("There are %d primes between 2 and %d.\n", j, n);
    d = sprintf(s, "%d", p[j-1]);   /* width of max primes */
    for (i = 0; i < j-1; i++) {
        if (i % 10 == 9)
            printf("%*d\n", d, p[i]);
        else
            printf("%*d, ", d, p[i]);
    }
    printf("%*d\n", d, p[i]);
    free(p);

    return j;
}

int main()
{
    int n;

    printf("All primes up to ");
    scanf("%d", &n);
    printf("\n");
    printPrimes(n);
    return 0;
}
