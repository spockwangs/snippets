/*
 * prob14 -- Problem 14 of column 8
 *   Given integers m and n and the real vector x[n], find the integer
 *   i (0 <= i < n-m) such that the sum x[i]+...+x[i+m] is nearest
 *   zero.
 */

#include <stdio.h>
#include <assert.h>
#include <math.h>   // for fabs()
#include <stdlib.h> // for rand(), RAND_MAX
#include <time.h>


/*
 * closer --
 *   Return whichever is closer to 0.
 */
float closer(float a, float b)
{
    if (a < 0 && b < 0)
        return a > b ? a : b;
    if (a >= 0 && b >= 0)
        return a < b ? a : b;
    if (a < 0 && b >= 0)
        return fabs(a) < b ? a : b;
    if (a >= 0 && b < 0)
        return a < fabs(b) ? a : b;

    // should not reach here
    assert(0);
}

int nearzero(float x[], int n, int m)
{
    assert(x != NULL && n > 0 && n > m);

    float sum, nearest_sofar;
    int i;

    sum = 0;
    for (i = 0; i <= m; i++) {
        sum += x[i];
    }
    // sum is sum of x[0..m]
    nearest_sofar = sum;

    // loop invariant: nearest_sofar is accurate for x[0..i+m-1] and
    // sum is sum of x[i-1..i-1+m].
    for (i = 1; i < n-m; i++) {
        sum = sum-x[i-1]+x[i+m];
        nearest_sofar = closer(nearest_sofar, sum);
    }
    return nearest_sofar;
}


#define MAXN 10000

float x[MAXN];

int main()
{
    int n, m;

    scanf("%d %d", &n, &m);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        x[i] = (float) rand() / RAND_MAX;
        printf("%f ", x[i]);
    }
    printf("\n");
    printf("nearzero = %d\n", nearzero(x, n, m));

    return 0;
}
