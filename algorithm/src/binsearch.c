/*
 * Implement a binary search algorithm.
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/binsearch.h"
#include <assert.h>

static int binsearch_range(Item A[], int p, int r, Key key);

/*
 * binsearch --
 *   Search for key in A[0..n-1] assuming A[0..n-1] is in ascending
 *   order.  Return its index if found or -1 if not found.
 */
int binsearch(Item A[], int n, Key key)
{
    assert(A && n > 0);

    return binsearch_range(A, 0, n-1, key);
}

/*
 * inter_search --
 *   Interpolation search.
 *   See P. 500 of "Algorithms in C (Parts 1-4)", 3/e for the
 *   algorithm.
 */
int inter_search(Item A[], int n, Key key)
{
    assert(A && n > 0);

    if (LESS(key, KEY(A[0])) || LESS(KEY(A[n-1]), key))
        return -1;
    while (n > 0) {
        int m = (key-KEY(A[0])) * (n-1) / ( KEY(A[n-1])-KEY(A[0]) );
        if (EQ(KEY(A[m]), key))
            return m;
        else if (LESS(key, KEY(A[m])))
            n = m;
        else {
            A += m+1;
            n -= m+1;
        }
    }
    return -1;
}

static int binsearch_range(Item A[], int p, int r, Key key)
{
    assert(p <= r);

    if (LESS(key, KEY(A[p])) || LESS(KEY(A[r]), key))
        return -1;
    while (p <= r) {
        int mid = p+(r-p)/2;
        if (EQ(KEY(A[mid]), key))
            return mid;
        else if (LESS(key, KEY(A[mid])))
            r = mid-1;
        else
            p = mid+1;
    }
    return -1;
}

