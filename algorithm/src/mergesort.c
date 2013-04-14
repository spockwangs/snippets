/*
 * This file implements a merge sort algorithm from Section 2.3,
 * "Introduction to Algorithms", second edition.
 */

#include "../inc/sort.h"
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <error.h>

/*
 * merge --
 *   array[p..q] and array[q+1..r] are in sorted order.  Merge them
 *   into sorted order.
 */
static void merge(ElemType array[], int p, int q, int r)
{
    /*
     * Create 2 arrays to hold array[p..q] and array[q+1..r].
     */
    int n1, n2;
    n1 = q - p + 1;
    n2 = r - q;
    int *L = (int *) malloc((n1+1) * sizeof(int));   /* +1 for sentinel */
    if (L == NULL) 
        error(1, errno, "malloc failed");
    int *R = (int *) malloc((n2+1) * sizeof(int));
    if (R == NULL)
        error(1, errno, "malloc failed");
    for (int i = 0; i < n1; i++)
        L[i] = array[p+i];
    for (int i = 0; i < n2; i++)
        R[i] = array[q+1+i];
    L[n1] = INT_MAX;    /* sentinel */
    R[n2] = INT_MAX;

    /*
     * Do the merge stuff.
     */

    int i, j;
    i = j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
    }
    free(L);
    free(R);
}

/*
 * merge_sort --
 *   Sort array[p..r] using merge sort algorithm.
 */
void merge_sort(ElemType array[], int n)
{
    int m;
    if (n > 1) {
        m = n/2;
        merge_sort(array, m);
        merge_sort(array+m, n-m);
        merge(array, 0, m-1, n-1);
    }
}
