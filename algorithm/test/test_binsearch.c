
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>        /* for time() */
#include "../inc/algorithm.h"
#include "../inc/binsearch.h"

#define NTESTS  1000000

static int cmp(const void *key, const void *mem)
{
    int a = *(int *) key;
    int b = *(int *) mem;
    return a-b;
}

void test(void)
{
    int A[11111];
    int nsuccess, ntests;
    int size[10] = { 1, 2, 3, 5, 7, 11, 23, 77, 111, 11111 };

    printf("Testing binsearch: ");

    /* construct an array for testing */
    for (int i = 0; i < 11111; i++)
        A[i] = i;

    nsuccess = ntests = 0;
    for (int i = 0; (size_t) i < NSIZE(size); i++) {
        for (int count = 0; count < size[i]; count++) {

            /* test */
            int key = rand() % (2*size[i]);
            int idx = binsearch(A, size[i], key);
            ntests++;

            /* verification */
            int *pkey = (int *) bsearch(&key, A, size[i], sizeof(A[0]), cmp);
            if ((pkey == NULL && idx < 0) ||
                (pkey-A == idx))
                nsuccess++;
        }
    }

    printf("%d/%d, %.2f%% success\n", nsuccess, ntests, 
            (double) nsuccess/ntests *100);
}

int main()
{
    srand((unsigned) time(0));
    test();
}
