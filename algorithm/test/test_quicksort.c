#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/sort.h"

#define NARRAY  100
#define NTESTS  10000

static int cmp(const void *p, const void *q)
{
    int a = *(int *) p;
    int b = *(int *) q;
    return a-b;
}

void test(void)
{
    int A[NARRAY];
    int nsuccess, ntests;

    printf("Testing quicksort: ");

    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {
        /* construct an array for testing */
        for (int i = 0; i < NARRAY; i++)
            A[i] = rand();

        /* test */
        quicksort(A, NARRAY-1);
        ntests++;

        /* verification */
        int B[NARRAY];
        memcpy(B, A, sizeof(int) * NARRAY);
        qsort(B, NARRAY, sizeof(int), cmp);
        for (int i = 0; i < NARRAY; i++) {
            if (B[i] != A[i])
                continue;
        }
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
