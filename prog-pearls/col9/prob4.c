/*
 * prob4.c -- Problem 4 of column 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


#define max(a, b) ((a) > (b) ? (a) : (b))

float arrmax(float x[], int n)
{
    if (n == 1)
        return x[0];
    else
        return max(x[n-1], arrmax(x, n-1));
}


#define MAXN 10000

float x[MAXN];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }

        clock_t start, ticks;
        start = clock();
        arrmax(x, n);
        ticks = clock() - start;
        printf("n: %d, ticks: %d, sec: %.2f\n",
                n, (int) ticks, (float) ticks / CLOCKS_PER_SEC);
    }

    return 0;
}
