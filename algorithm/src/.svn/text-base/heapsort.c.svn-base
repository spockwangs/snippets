/*
 * heapsort - Implement a heap sort algorithm.
 *
 * Author: wbb
 * Date: 2010-03-06
 */

#include "../inc/sort.h"
#include <stdlib.h>     // for memcpy()

#define LEFT(i)     (2*i+1)
#define RIGHT(i)    (2*i+2)

static void max_heapify(ElemType A[], int i, int n);
static void build_max_heap(ElemType A[], int n);

/*
 * heapsort --
 *   Sort A[0..n-1] into ascending order.
 */
void heapsort(ElemType A[], int n)
{
    build_max_heap(A, n);
    for (int i = n-1; i >= 1; i--) {
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        max_heapify(A, 0, i);
    }
}

/*
 * max_heapify --
 *   Maintaine max heap property of A[i..n-1] assuming LEFT(i) and
 *   RIGHT(i) are max-heaps.
 */
static void max_heapify(ElemType A[], int i, int n)
{
    int l, r, max;

    l = LEFT(i);
    r = RIGHT(i);
    if (l < n && A[l] > A[i])
        max = l;
    else
        max = i;
    if (r < n && A[r] > A[max])
        max = r;
    if (max != i) {
        int tmp = A[i];
        A[i] = A[max];
        A[max] = tmp;
        max_heapify(A, max, n);
    }
}

/*
 * build_max_heap --
 *   Build a max-heap in A[0..n-1].
 */
static void build_max_heap(ElemType A[], int n)
{
    for (int i = (n-1)/2; i >= 0; i--)
        max_heapify(A, i, n);
}

#undef LEFT
#undef RIGHT
