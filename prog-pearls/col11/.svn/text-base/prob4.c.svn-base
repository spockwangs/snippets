/*
 * prob4.c -- Problem 4 of column 11
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

void swap(int x[], int i, int j)
{
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

void qsort1(int x[], int l, int u)
{
    assert(x != NULL);

    for (;;) {
        if (l >= u)
            break;

        int m;
        m = l-1;
        for (int i = l; i <= u; i++) {
            // invariant: x[l..m] <= x[u] &&
            //            x[m+1..i-1] > x[u]
            if (x[i] <= x[u])
                swap(x, ++m, i);
        }
        if (m-l < u-m) {    // the left part is smaller; recurse into it
            qsort1(x, l, m-1);
            l = m+1;
        } else {    // the right part is smaller; recurse into it
            qsort1(x, m+1, u);
            u = m-1;
        }
    }
}


int validate_sorted(int x[], int n)
{
    assert(x != NULL && n >= 0);

    for (int i = 0; i < n-1; i++)
        if (x[i] > x[i+1])
            return 0;
    return 1;
}


#define MAXN 1000000

int x[MAXN];

int main()
{
    srand(time(0));

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }
        for (int i = 0; i < n; i++)
            x[i] = rand();
        clock_t start, ticks;
        start = clock();
        qsort1(x, 0, n-1);
        ticks = clock() - start;
        if (!validate_sorted(x, n))
            printf("error: qsort1 is incorrect!\n");
        else
            printf("n: %d, ticks: %d, sec: %.2f\n",
                    n, (int) ticks, (float) ticks/CLOCKS_PER_SEC);
    }

    return 0;
}
