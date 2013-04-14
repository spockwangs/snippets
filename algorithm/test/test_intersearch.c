
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/binsearch.h"

#define NARRAY  10000
#define NTESTS  1000000

static int cmp(const void *key, const void *mem)
{
    int a = *(int *) key;
    int b = *(int *) mem;
    return a-b;
}

void test(void)
{
    int A[NARRAY];
    int nsuccess, ntests;

    printf("Testing interpolation search: ");
    /* construct an array for testing */
    for (int i = 0; i < NARRAY; i++)
        A[i] = i;

    nsuccess = ntests = 0;
    for (int count = 0; count < NTESTS; count++) {

        /* test */
        int key = rand() % (2*NARRAY);
        int idx = inter_search(A, NARRAY, key);
        ntests++;

        /* verification */
        int *pkey = (int *) bsearch(&key, A, NARRAY, sizeof(A[0]), cmp);
        if ((pkey == NULL && idx < 0) ||
            (pkey-A == idx))
            nsuccess++;
    }

    printf("%d/%d, %.2f%% success\n", nsuccess, ntests, 
            (double) nsuccess/ntests *100);
}

int main()
{
    srand((unsigned) time(0));
    test();
}
