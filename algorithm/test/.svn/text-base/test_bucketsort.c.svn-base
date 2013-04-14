
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/sort.h"

#define NARRAY  10
#define NTESTS  10000

int verify_sorted(double A[], int n)
{
    for (int i = 0; i < n-1; i++)
        if (A[i] > A[i+1]) {
            printf("failure: ");
            for (int j = 0; j < n; j++)
                printf("%f ", A[j]);
            printf("\n");
            return 0;
        }
    return 1;
}

void test(void)
{
    double A[NARRAY];
    int nsuccess, ntests;

    printf("Testing bucket sort: ");
    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {
        /* construct an array for testing */
        for (int i = 0; i < NARRAY; i++)
            A[i] = (rand()%100) / 100.0;

        /* test */
        bucket_sort(A, NARRAY);
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
