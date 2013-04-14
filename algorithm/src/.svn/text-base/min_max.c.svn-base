/*
 * Find both the minimum and maximum of a set.  The algorithm is
 * described in Section 9.1 of "Introduction to Algorithms", second
 * edition.
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/algorithm.h"
#include <assert.h>

/*
 * min_max --
 *   Find the min and max element in A[0..n-1].
 */
void min_max(int A[], int n, int *pmin, int *pmax)
{
    assert(A && n > 0);

    int min, max, i;
    if (n%2 == 0) {     // even
        if (A[0] < A[1]) {
            min = A[0];
            max = A[1];
        } else {
            min = A[1];
            max = A[0];
        }
        i = 2;
    } else {    // odd
        min = max = A[0];
        i = 1;
    }

    while (i < n) {
        if (A[i] < A[i+1]) {
            if (A[i] < min)
                min = A[i];
            if (A[i+1] > max)
                max = A[i+1];
        } else {
            if (A[i+1] < min)
                min = A[i+1];
            if (A[i] > max)
                max = A[i];
        }
        i += 2;
    }

    if (pmin)
        *pmin = min;
    if (pmax)
        *pmax = max;
}


