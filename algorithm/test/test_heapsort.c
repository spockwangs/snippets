#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/sort.h"

#define NARRAY  100
#define NTESTS  10000

static int verify_sorted(int A[], int n)
{
    for (int i = 0; i < n-1; i++)
        if (A[i] > A[i+1]) {
            return 0;
        }
    return 1;
}

void test(void)
{
    int A[NARRAY];
    int nsuccess, ntests;

    printf("Testing heapsort: ");

    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {
        /* construct an array for testing */
        for (int i = 0; i < NARRAY; i++)
            A[i] = rand();

        /* test */
        heapsort(A, NARRAY);
        ntests++;

        /* verification */
        if (verify_sorted(A, NARRAY))
            nsuccess++;
    }

    printf("%d/%d, %.2f%%\n", nsuccess, ntests,
            (double) nsuccess/ntests * 100);
}

int main()
{
    srand((unsigned) time(0));
    test();
}
