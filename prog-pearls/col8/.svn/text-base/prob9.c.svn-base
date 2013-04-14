/*
 * prob9.c -- Problem 9 of column 8
 */

#include <stdio.h>
#include <assert.h>
#include <float.h>              // for FLT_MIN
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

float maxsum1(float x[], int n)
{
    float maxsofar;

    assert(x != NULL && n > 0);

    maxsofar = FLT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // compute sum of x[i..j]
            float sum = 0.0;

            for (int k = i; k <= j; k++) {
                sum += x[k];
            }
            // sum is sum of x[i..j]
            maxsofar = max(maxsofar, sum);
        }
    }
    return maxsofar;
}


float maxsum2a(float x[], int n)
{
    float maxsofar;

    assert(x != NULL && n > 0);

    maxsofar = FLT_MIN;
    for (int i = 0; i < n; i++) {
        float sum = 0;

        for (int j = i; j < n; j++) {
            sum += x[j];
            maxsofar = max(maxsofar, sum);
        }
    }
    return maxsofar;
}


float maxsum2b(float x[], int n)
{
    assert(x != NULL && n > 0);

    float *arr, *cumarr;
    arr = calloc(n + 1, sizeof(float));
    assert(arr != NULL);
    cumarr = arr + 1;
    for (int i = 0; i < n; i++)
        cumarr[i] = cumarr[i - 1] + x[i];

    float maxsofar;

    maxsofar = FLT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            float sum = cumarr[j] - cumarr[i - 1];

            maxsofar = max(maxsofar, sum);
        }
    }

    free(arr);
    return maxsofar;
}


float maxsum_r(float x[], int l, int u)
{
    assert(x != NULL && l <= u);

    // one element
    if (l == u)
        return x[l];

    int m = (l + u) / 2;
    float sum;

    // find max crossing to left
    float lmax = FLT_MIN;

    sum = 0;
    for (int i = m; i >= l; i--) {
        sum += x[i];
        lmax = max(lmax, sum);
    }

    // find max crossing to right
    float rmax = FLT_MIN;

    sum = 0;
    for (int i = m + 1; i <= u; i++) {
        sum += x[i];
        rmax = max(rmax, sum);
    }

    return max(lmax + rmax, max(maxsum_r(x, l, m), maxsum_r(x, m + 1, u)));
}


float maxsum3(float x[], int n)
{
    assert(x != NULL && n > 0);

    return maxsum_r(x, 0, n - 1);
}


float maxsum4(float x[], int n)
{
    float maxsofar, maxendinghere;

    maxsofar = FLT_MIN;
    maxendinghere = 0.0;
    for (int i = 0; i < n; i++) {
        maxendinghere = max(maxendinghere + x[i], x[i]);
        maxsofar = max(maxsofar, maxendinghere);
    }
    return maxsofar;
}


/*
 * sprinkle --
 *   Fill x[] with real numbers uniform on [-1, 1].
 */
void sprinkle(float x[], int n)
{
    assert(x != NULL && n > 0);

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        x[i] = 1 - 2 * ((float) rand() / RAND_MAX);
}


#define MAXN 10000000

float x[MAXN];

int main()
{
    int algnum, start, clicks, n;
    float thisans;

    while (scanf("%d %d", &algnum, &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }
        sprinkle(x, n);
        start = clock();
        thisans = -1;
        switch (algnum) {
        case 1:
            thisans = maxsum1(x, n);
            break;
        case 2:
            thisans = maxsum2a(x, n);
            break;
        case 22:
            thisans = maxsum2b(x, n);
            break;
        case 3:
            thisans = maxsum3(x, n);
            break;
        case 4:
            thisans = maxsum4(x, n);
            break;
        default:
            break;
        }
        clicks = clock() - start;
        printf("%d\t%d\t%f\t%d\t%f\n", algnum, n, thisans,
               clicks, clicks / (float) CLOCKS_PER_SEC);
        if (maxsum1(x, n) != thisans)
            printf(" maxsum error: mismatch with alg4: %f\n",
                   maxsum4(x, n));
    }
    return 0;
}
