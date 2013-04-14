/*
 * prob8.c -- Problem 8 of column 8 
 *   Modify Algorithm 3 (the divide-and-conquer algorithm) to run in
 *   linear worst-case time.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

float maxsum_r(float x[], int l, int u, float *allsum, float *plmax, float *prmax)
{
    assert(x != NULL && l <= u);

    if (l == u) {
        if (allsum)
            *allsum = x[l];
        if (plmax)
            *plmax = max(0, x[l]);
        if (prmax)
            *prmax = max(0, x[l]);
        return max(0, x[l]);
    }

    float lallsum, rallsum, llmax, lrmax, rlmax, rrmax, lmaxsum, rmaxsum;
    int m = (l+u)/2;
    lmaxsum = maxsum_r(x, l, m, &lallsum, &llmax, &lrmax);
    rmaxsum = maxsum_r(x, m+1, u, &rallsum, &rlmax, &rrmax);
    if (plmax)
        *plmax = max(llmax, lallsum+rlmax);
    if (prmax)
        *prmax = max(rrmax, rallsum+lrmax);
    if (allsum)
        *allsum = lallsum+rallsum;
    return max(lmaxsum, max(rmaxsum, lrmax+rlmax));
}

float maxsum(float x[], int n)
{
    return maxsum_r(x, 0, n-1, NULL, NULL, NULL);
}


#define MAXN 100000000

float x[MAXN];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }
        srand(time(0));
        for (int i = 0; i < n; i++)
            x[i] = 1-2*((float) rand()/RAND_MAX);

        clock_t start = clock();
        float sum = maxsum(x, n);
        clock_t ticks = clock() - start;
        printf("n: %d, maxsum: %.2f, ticks: %d, sec: %.2f\n",
                n, sum, (int) ticks, (double) ticks/CLOCKS_PER_SEC);
    }
    return 0;
}
