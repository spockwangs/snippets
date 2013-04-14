/*
 * Unimodal search in O(lgn) time.
 *   An array A[1..n] is unimodal if it consists of an increasing
 *   sequence followed by a decreasing sequence.  The problem is to
 *   search for the maximum element.
 *
 */

#include "../inc/algorithm.h"
#include <stdlib.h>     /* for random() */
#include <assert.h>

/*
 * unimodal_search --
 *   Search for the max element in the unimodal array A[a..b].
 */
int unimodal_search(int A[], int a, int b)
{
    assert(A && a <= b);

    while (a < b) {
        int mid = (a+b) / 2;
        if (A[mid] < A[mid+1])
            a = mid+1;
        else if (A[mid] > A[mid+1] && (mid-1 >= a) && A[mid] > A[mid-1])
            return A[mid];
        else
            b = mid;
    }
    return A[a];
}

