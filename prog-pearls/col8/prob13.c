/*
 * prob13.c -- Problem 13 of column 8
 *   In the maximum subarray problem we are given an nxn array of
 *   reals, and we must find the maximum sum contained in any
 *   ractangular subarray.  Waht is the complexity of this problem?
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

/*
 * maxsum --
 *   x is a 2-dimentional n by n array, which is represented in
 *   row-major 1-dimentional array.
 */
float maxsum(float x[], int n)
{
    assert(x != NULL && n > 0);

    // col_cumarr[i, j] contains cumulative sum of x[0, j], x[1, j],
    // ..., x[i, j]
    float col_cumarr[n*n];
    for (int i = 0; i < n; i++) {   // i is the row
        for (int j = 0; j < n; j++) {   // j is the column
            if (i == 0)
                col_cumarr[j] = x[j];
            else 
                col_cumarr[i*n+j] = col_cumarr[(i-1)*n+j] + x[i*n+j];
        }
    }

    float maxsofar, maxendinghere;
    maxsofar = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            maxendinghere = 0;
            // loop invariant: maxsofar and maxendinghere are accurate
            // for x[i..j, 0..n-1]
            for (int k = 0; k < n; k++) {
                // sum_ij is the sum of x[i..j, k]
                float sum_ij = col_cumarr[j*n+k] - col_cumarr[(i-1)*n+k];
                maxendinghere = max(maxendinghere + sum_ij, 0);
                maxsofar = max(maxsofar, maxendinghere);
            }
        }
    }
    return maxsofar;
}


float maxsum_slow(float x[], int n)
{
    assert(x != NULL && n > 0);

    // col_cumarr[i, j] contains cumulative sum of x[0, j], x[1, j],
    // ..., x[i, j]
    float col_cumarr[n*n];
    for (int i = 0; i < n; i++) {   // i is the row
        for (int j = 0; j < n; j++) {   // j is the column
            if (i == 0)
                col_cumarr[j] = x[j];
            else 
                col_cumarr[i*n+j] = col_cumarr[(i-1)*n+j] + x[i*n+j];
        }
    }

    float maxsofar = 0;
    float sum;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int l = 0; l < n; l++) {
                sum = 0;
                for (int m = l; m < n; m++) {
                    // sum_ij is the sum of x[i..j, m]
                    float sum_ij = col_cumarr[j*n+m] - col_cumarr[(i-1)*n+m];
                    sum += sum_ij;
                    maxsofar = max(maxsofar, sum);
                }
            }
        }
    }
    return maxsofar;
}


#define MAXN 1000

float x[MAXN*MAXN];

int main()
{
    srand(time(0));
    for (int i = 0; i < MAXN*MAXN; i++)
        x[i] = (float) rand() / RAND_MAX;

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n > MAXN) {
            printf("n should not be no more than %d\n", MAXN);
            continue;
        }

        clock_t start = clock();
        float sum = maxsum(x, n);
        clock_t ticks = clock() - start;
        printf("n: %d, maxsum: %.2f, ticks: %d, sec: %.2f\n",
                n, sum, (int) ticks, (float) ticks / CLOCKS_PER_SEC);

        float chk_sum = maxsum_slow(x, n);
        if (sum != chk_sum)
            printf("error: mismatch with maxsum_slow(): %.2f\n", chk_sum);
    }
    return 0;
}

