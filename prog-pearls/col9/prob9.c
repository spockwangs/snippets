/*
 * prob9.c -- Problem 9 of column 9
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


int binarysearch(int x[], int n, int t)
{
    int l, u, m;

    l = -1;
    u = n;
    while (l+1 != u) {
        // loop invariant: l < u && x[l] < t && t <= x[u]
        m = (l+u) / 2;
        if (x[m] < t)
            l = m;
        else
            u = m;
    }
    // assert l+1 = u && x[l] < t && t <= x[u]
    if (u == n || x[u] != t)
        return -1;
    else
        return u;
}


int ssearch(int x[], int n, int t)
{
    int hold = x[n];
    x[n] = t;

    int i;
    for (i = 0; ; i++) {
        if (x[i] == t)
            break;
    }
    x[n] = hold;
    if (i == n)
        return -1;
    else
        return i;
}


#define MAXN 10000000

int x[MAXN];

int main()
{
    for (int i = 0; i < MAXN; i++) {
        x[i] = 2*i;
    }

    int algnum, n;
    while (scanf("%d %d", &algnum, &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }

        clock_t start, ticks;
        int thisans, chkans, t = rand();
        start = clock();
        switch (algnum) {
        case 1:
            thisans = binarysearch(x, n, t);
            break;
        case 2:
            thisans = ssearch(x, n, t);
            break;
        default:
            break;
        }
        ticks = clock() - start;
        printf("algnum: %d, n: %d, ans: %d, ticks: %d, sec: %.2f\n",
                algnum, n, thisans, (int) ticks, (float) ticks / CLOCKS_PER_SEC);
        chkans = ssearch(x, n, t);
        if (thisans != chkans)
            printf("error: mismatch with ssearch(): %d\n", chkans);
    }
    return 0;
}
