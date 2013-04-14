/*
 * LIS - Longest Increasing Subsequence
 *   See exercise 15.4-6 of CLRS (2/e).
 */


#include <assert.h>
#include <stdio.h>

/*
 * lis --
 *   Compute the longest increasing subsequence in A[0..n-1] and
 *   return the length of LIS.
 *   The running time is O(nlg(n)) and space is O(n).
 */
int lis(int A[], int n)
{
    assert(A != NULL && n > 0);

    int p[n], d[n];
    int k;

    p[0] = -1;
    d[0] = 0;
    k = 0;
    for (int i = 1; i < n; i++) {
        if (A[d[k]] < A[i]) {
            p[i] = d[k];
            d[++k] = i;
            continue;
        }

        int l, r;
        for (l = 0, r = k; l < r;) {
            int m = (l+r)/2;
            if (A[d[m]] < A[i])
                l = m+1;
            else
                r = m;
        }
        if (A[i] < A[d[l]]) {
            if (l > 0)
                p[i] = d[l-1];
            d[l] = i;
        }
    }

    // Construct the LIS.
    int j = d[k];
    int r = k+1;
    for (; k >= 0; k--) {
        d[k] = j;
        j = p[j];
    }
    for (int i = 0; i < r; i++)
        printf("%d ", A[d[i]]);
    printf("\n");
    return r;
}
