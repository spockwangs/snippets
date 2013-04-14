/*
 * Solve the selection problem.
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/algorithm.h"
#include <stdlib.h>     // for calloc(), free()
#include <string.h>     // for memcpy()
#include <assert.h>

/*
 * random_select --
 *   Return the kth smallest element of A[0..n-1].
 */
int random_select(int A[], int n, int k)
{
    assert(A && n > 0 && k >= 0 && k < n);
    
    while (1) {
        if (n == 1)
            return A[0];

        int q = random_partition(A, 0, n-1);
        if (k == q)
            return A[q];
        else if (k < q)
            n = q;
        else {
            A += q+1;
            n = n-q-1;
            k = k-q-1;
        }
    }

}

/*
 * linear_select --
 *   Return the kth smallest element of A[0..n-1].
 *   The algorithm used here was devised by Blum, Floyd, Pratt, Rivest
 *   and Tarjan.  See Section 9.3 of "Introduction to ALgorithms",
 *   second edtion for more details on the algorithm.
 */
int linear_select(int A[], int n, int k)
{
    assert(A && n > 0 && k >= 0 && k < n);

    while (1) {
        if (n == 1)
            return A[0];

        /*
         * Divide the n elements of A[] into n/5 groups and insertion
         * sort each group.  Then gather the median of each group into
         * the beginning of A (instead of allocating another array to
         * save space).
         */

        int j = 0;
        for (int i = 0; i < n; i += 5) {
            insert_sort(A+i, MIN(n-i, 5));
            int median = (MIN(n-i, 5)+1)/2 - 1;
            swap(A, j, i+median);
            j++;
        }
        /* here j is the # of groups */

        /*
         * Recursively find the median 'pivot' of n/5 medians and use it
         * as the pivot for partition.
         */

        int pivot = linear_select(A, j, (j-1)/2);
        int q = partition2(A, 0, n-1, pivot);

        /*
         * If k == q then A[q] is the kth smallest element.
         * Otherwise, use linear_select() recursively to find the kth
         * smallest element on the low side if k < q, or the (k-q-1)th
         * smallest element on the high side if k > q.
         * The following code has been optimised using tail recursion.
         */

        if (k == q)
            return A[q];
        else if (k < q)
            n = q;
        else {
            A += q+1;
            n = n-q-1;
            k = k-q-1;
        }
    }
}

/*
 * small_select --
 *   Return the kth smallest element in A[0..n-1].
 *   This algorithm does some improvements when k is small.  See
 *   problem 9-3 of "Introduction to Algorithms", 2/e for more details
 *   on the algorithm.
 */
int small_select(int A[], int n, int k)
{
    assert(A && n > 0 && k >= 0 && k < n);

    if (k >= n/2)
        return linear_select(A, n, k);

    /*
     * Divide A into 2 groups: A[0..n/2-1] and A[n/2..n-1].
     * Compare A[i] with A[i+n/2] and put the smaller one in A[i+n/2].
     */
    for (int i = 0; i < n/2; i++) {
        if (A[i] < A[i+n/2])
            swap(A, i, i+n/2);
    }

    /*
     * Recursively find the kth smallest element in A[n/2..n-1] and
     * partition the array around the kth smallest element.
     * Whenever it exchanges A[n/2+i] and A[n/2+j], it exchanges A[i]
     * and A[j] also.
     */

    int *copy = (int *) calloc((size_t) (n-n/2), sizeof(int));
    memcpy(copy, A+n/2, (n-n/2)*sizeof(int));
    int pivot = small_select(copy, n-n/2, k);
    free(copy);

    int *p = A+n/2;
    int len = n-n/2;
    for (int i = 0; i < len; i++)
        if (p[i] == pivot) {
            swap(p, i, k);
            if (i < n/2)
                swap(A, i, k);
            break;
        }
    int i = 0, j = len-1;
    while (1) {
        while (j > k && p[j] >= pivot)
            j--;
        if (j <= k)
            break;
        while (i < k && p[i] < pivot)
            i++;
        if (i >= k)
            break;
        swap(p, i, j);
        if (j < n/2)
            swap(A, i, j);
    }
    i = 0, j = len-1;
    while (1) {
        while (i < k && p[i] <= pivot)
            i++;
        if (i >= k)
            break;
        while (j > k && p[j] > pivot)
            j--;
        if (j <= k)
            break;
        swap(p, i, j);
        if (j < n/2)
            swap(A, i, j);
    }

    /*
     * Gather A[0..k] and A[n/2..n/2+k] together and compute their kth
     * smallest element.
     */
    for (i = 0; i < k+1; i++)
        swap(A, k+1+i, n/2+i);
    return linear_select(A, 2*k+2, k);
}






