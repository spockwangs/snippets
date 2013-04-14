
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/algorithm.h"

#define NARRAY  111
#define NTESTS  10000

const int debug = 0;

static int cmp(const void *p, const void *q)
{
    int a = *(int *) p;
    int b = *(int *) q;
    return a-b;
}

void test(void)
{
    int A[NARRAY];
    int B[NARRAY];
    int nsuccess, ntests;

    printf("Testing select: ");

    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {
        /* construct an array for testing */
        if (debug)
            printf("A: ");
        for (int i = 0; i < NARRAY; i++) {
            A[i] = rand() % 10;
            if (debug)
                printf("%d ", A[i]);
        }

        memcpy(B, A, sizeof(int) * NARRAY);

        /* test */
        qsort(B, NARRAY, sizeof(int), cmp);
        int k;
        for (k = 0; k < NARRAY; k++) {
            int key = small_select(A, NARRAY, k);
            if (key != B[k])
                break;
        }
        if (k == NARRAY) {
            nsuccess++;
            if (debug) printf("OK\n");
        } else {
            if (debug) printf("OOPS!\n");
            break;
        }
        ntests++;
    }

    printf("%d/%d, %.2f%%\n", nsuccess, ntests,
            (double) nsuccess/ntests * 100);
}

int main()
{
    srand((unsigned) time(0));
    test();
}
