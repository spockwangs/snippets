/*
 * prob12.c -- Problem 12 of column 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


/* 
 * poly1 --
 *   Compute a[n]*x^n + a[n-1]*x^(n-1) + ... + a[1]*x^1 + a[0].
 */
float poly1(float a[], int n, float x)
{
    float y, xi;
    y = a[0];
    xi = 1;
    for (int i = 1; i <= n; i++) {
        xi *= x;
        y += a[i] * xi;
    }
    return y;
}


/*
 * poly2 --
 *   Compute the same polynomial using Horner's rule.
 */
float poly2(float a[], int n, float x)
{
    float y;
    y = a[n];
    for (int i = n-1; i >= 0; i--) {
        y = y*x + a[i];
    }
    return y;
}


#define MAXN 10000000

float a[MAXN];

int main()
{
    srand(time(0));
    for (int i = 0; i < MAXN; i++)
        a[i] = 1 - 2 * ((float) rand()/RAND_MAX);

    int algnum, n;
    while (scanf("%d %d", &algnum, &n) != EOF) {
        if (n > MAXN-1) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }

        clock_t start, ticks;
        float thisans, chkans, x = 1 - 2*((float) rand() / RAND_MAX);
        start = clock();
        switch (algnum) {
        case 1:
            thisans = poly1(a, n, x);
            break;
        case 2:
            thisans = poly2(a, n, x);
            break;
        default:
            break;
        }
        ticks = clock() - start;
        printf("n: %d, ans: %.2f, ticks: %d, sec: %.2f\n",
                n, thisans, (int) ticks, (float) ticks / CLOCKS_PER_SEC);
        chkans = poly1(a, n, x);
        if (thisans != chkans)
            printf("error: mismatch with poly1(): %.2f\n", chkans);
    }
    return 0;
}
