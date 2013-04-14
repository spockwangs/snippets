#include "../inc/algorithm.h"
#include <stdio.h>

#define NARRAY 100
#define NTESTS 10000

void test()
{
    int A[NARRAY], m;
    int nsuccess, ntests;

    printf("Testing unimodal search: ");

    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {
        /* construct an array for testing */
        m = random(0, NARRAY-1);
        for (int i = 0; i <= m; i++)
            A[i] = i;
        for (int i = m+1; i < NARRAY; i++)
            A[i] = A[i-1]-1;

        /* test */
        ntests++;
        int max = unimodal_search(A, 0, NARRAY-1);
        if (max == A[m])
            nsuccess++;
        else {
            /* print the array */
            printf("failure: A: ");
            for (int i = 0; i < NARRAY; i++)
                printf("%d ", A[i]);
            printf("max = %d, expect %d\n", max, A[m]);
        }
    }

    printf("%d/%d, %.2f%%\n", nsuccess, ntests,
            (double) nsuccess/ntests * 100);
}

int main()
{
    test();
}
