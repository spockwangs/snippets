/*
 * Impelement the counting sort algorithm.
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/sort.h"
#include <assert.h>
#include <stdlib.h>     // for malloc()
#include <errno.h>
#include <error.h>      // for error()

/*
 * counting_sort --
 *   Sort A[0..n-1] into ascending order and put the output sequence
 *   in B assuming the elements of A is in the range [0, k].
 *   See Section 8.2 of "Introduction to Algorithms", second edition.
 */
void counting_sort(ElemType A[], ElemType B[], int n, int k)
{
    assert(A && B && n > 0 && k >= 0);

    int *C = (int *) malloc((k+1) * sizeof(ElemType));
    if (C == NULL)
        error(1, errno, "malloc error");

    for (int i = 0; i <= k; i++)
        C[i] = 0;
    for (int i = 0; i < n; i++)
        C[A[i]]++;
    for (int i = 1; i <= k; i++)
        C[i] += C[i-1];
    for (int i = n-1; i >= 0; i--) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    free(C);
}
