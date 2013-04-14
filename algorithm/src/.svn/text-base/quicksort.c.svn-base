/*
 * Quicksort
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include <assert.h>
#include <stdlib.h>      // for rand() 
#include "../inc/sort.h"

static void swap(ElemType A[], int p, int r);
static int partition(ElemType A[], int p, int r);
static void quick_sort_recur(ElemType A[], int p, int r);

/*
 * quicksort --
 *   Sort A[0..n-1] in increasing order.
 */
void quicksort(ElemType A[], int n)
{
    quick_sort_recur(A, 0, n-1);
}

/*
 * random --
 *   Generate a uniformly distributed random integer in [a, b].
 */
static int random(int a, int b)
{
    assert(a <= b);
    return rand()%(b-a+1) + a;
}

static int partition(ElemType A[], int p, int r)
{
    int x, i, j;

    /* choose the median-of-3 */
    int k1, k2, k3, k;
    k1 = random(p, r);
    k2 = random(p, r);
    k3 = random(p, r);
    if (A[k1] < A[k2]) {
        if (A[k2] < A[k3])
            k = k2;
        else if (A[k1] < A[k3])
            k = k3;
        else
            k = k1;
    } else {
        if (A[k2] > A[k3])
            k = k2;
        else if (A[k1] > A[k3])
            k = k3;
        else
            k = k1;
    }
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
    return i+1;
}

void quick_sort_recur(ElemType A[], int p, int r)
{
    while (p < r) {
        int q = partition(A, p, r);
        if (q-p < r-q) {
            quick_sort_recur(A, p, q-1);
            p = q+1;
        } else {
            quick_sort_recur(A, q+1, r);
            r = q-1;
        }
    }
}

static void swap(ElemType A[], int p, int r)
{
    assert(A && p >= 0 && r >= 0);

    ElemType tmp = A[p];
    A[p] = A[r];
    A[r] = tmp;
}
