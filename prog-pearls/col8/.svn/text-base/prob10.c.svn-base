/*
 * prob10.c -- Problem 10 of column 8
 */

#include <stdio.h>
#include <float.h>  // for FLT_MAX
#include <math.h>   // for fabs()
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

static int floatcmp(const void *pf1, const void *pf2)
{
    float f1 = *(float *) pf1;
    float f2 = *(float *) pf2;
    if (f1 < f2)
        return -1;
    else if (f1 == f2)
        return 0;
    else
        return 1;
}


float closer_to_zero(float a, float b)
{
    float aa = fabs(a);
    float bb = fabs(b);
    if (aa < bb)
        return a;
    else
        return b;
}


/*
 * sumzero --
 *   Find the sum of any contiguous subvector of x[], which is closest
 *   to zero.
 */
float sumzero(float x[], int n)
{
    assert(x != NULL && n > 0);

    // cumarr[i] is the cumulative sum of x[0..i] and cumarr[-1] is 0.
    // So sum of x[i..j] = cumarr[j] - cumarr[i-1].
    // According to above discussion the cumarr needs n+1 elements.
    float *arr = malloc((n+1)*sizeof(*arr));
    assert(arr != NULL);
    float *cumarr = arr+1;
    cumarr[-1] = 0;
    for (int i = 0; i < n; i++)
        cumarr[i] = cumarr[i-1] + x[i];

    // Find which sum of x[i..j] is closest to zero is equivalent to
    // finding the cloeset two adjacent cumarr elements.  We can do
    // this by sorting.
    qsort(arr, n+1, sizeof(arr[0]), floatcmp);

    float nearestsofar;
    nearestsofar = cumarr[0]-cumarr[-1];
    for (int i = 0; i < n; i++)
        nearestsofar = closer_to_zero(nearestsofar, cumarr[i]-cumarr[i-1]);
    return nearestsofar;
}


float closer_tot(float a, float b, float t)
{
    if (fabs(a - t) < fabs(b - t))
        return a;
    else
        return b;
}


int iscloser_tot(float a, float b, float t)
{
    if (fabs(a-t) < fabs(b-t))
        return 1;
    else
        return 0;
}


/*
 * sumtot --
 *   Find the sum of any contiguous subvector of x[], which is closest
 *   to 't'.
 */
float sumtot(float x[], int n, float t)
{
    assert(x != NULL && n > 0);

    // cumarr[i] is the cumulative sum of x[0..i] and cumarr[-1] is 0.
    // So sum of x[i..j] = cumarr[j] - cumarr[i-1].
    // According to above discussion the cumarr needs n+1 elements.
    float *arr = calloc(n+1, sizeof(*arr));
    assert(arr != NULL);
    float *cumarr = arr+1;
    cumarr[-1] = 0;
    for (int i = 0; i < n; i++)
        cumarr[i] = cumarr[i-1] + x[i];

    // Find which sum of x[i..j] is closest to 't' is equivalent to
    // finding the cloeset two cumarr elements whose difference is
    // closest to 't'.  Sorting them will facilitate us to find it.
    qsort(arr, n+1, sizeof(arr[0]), floatcmp);

    float nearestsofar;
    int i, j;
    i = -1, j = 0;
    nearestsofar = cumarr[0]-cumarr[-1];
    while (j < n) {
        // Find whose difference with cumarr[i] is closest to 't'.
        while (j < n && iscloser_tot(cumarr[j]-cumarr[i], nearestsofar, t)) {
            nearestsofar = cumarr[j]-cumarr[i];
            ++j;
        }
        assert(j > i);
        ++i;
        if (j <= i)
            ++j;
    }
    free(arr);
    return nearestsofar;
}


#define MAXN 10000000

float x[MAXN];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        srand(time(0));
        for (int i = 0; i < n; i++)
            x[i] = (float) rand() / RAND_MAX;
        
        clock_t start = clock();
        float thisans = sumtot(x, n, 0.0);
        clock_t ticks = clock() - start;
        float chkans = sumzero(x, n);
        printf("n: %d, ans: %.2f, ticks: %d, secs: %.2f\n",
                n, thisans, (int) ticks, (float) ticks/CLOCKS_PER_SEC);
        if (chkans != thisans)
            printf("error: mismatch with sumzero(): %.2f\n", chkans);
    }
    return 0;
}
