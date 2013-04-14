/*
 * partition is usually called by quicksort() or select().
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/algorithm.h"
#include <assert.h>

/*
 * partition --
 *   Partition A[p..r] into 2 groups around the pivot A[pivot] and
 *   return the index of the pivot.
 */
int partition(int A[], int p, int r, int pivot)
{
    assert(A && p >= 0 && r >= 0 && pivot >= 0);
    assert(p <= r && pivot >= p && pivot <= r);

    int x, i, j;

    if (r != pivot)
        swap(A, r, pivot);
    i = p-1;
    for (j = p; j <= r-1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A, i, j);
        }
    }
    swap(A, i+1, r);
    return i+1;
}

/*
 * partition2 --
 *   Partition A[p..r] around the pivot 'pivot' and return the index
 *   of the pivot.
 */
int partition2(int A[], int p, int r, int pivot)
{
    assert(A && p >= 0 && r >= p);
    
    int i, j, d;
    d = 0;
    i = p-1;
    for (j = p; j <= r-1; j++) {
        if (d == 0 && A[j] == pivot) {
            swap(A, j, r);
            d = 1;
        }
        if (A[j] <= pivot) {
            i++;
            swap(A, i, j);
        }
    }
    assert(d == 1 || A[r] == pivot);
    swap(A, i+1, r);
    return i+1;
}

/*
 * random_partition --
 *   Partition A[p..r] into 2 groups around a randomly chosen pivot.
 */
int random_partition(int A[], int p, int r)
{
    int x, i, j;

    int k = random(p, r);
    x = A[k];
    A[k] = A[r];
    A[r] = x;

    i = p-1;
    for (j = p; j <= r-1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A, i, j);
        }
    }
    swap(A, i+1, r);
    assert(i+1 >= p && i+1 <= r);
    return i+1;
}
