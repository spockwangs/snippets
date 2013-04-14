/*
 * prob11.c -- Problem 11 of column 11
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


void swap(int x[], int i, int j)
{
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

void fat_partiton(int x[], int l, int u, int *pa, int *pb)
{
    if (l >= u) {
        *pa = l-1;
        *pb = u+1;
        return;
    }

    int i, j, a, b;
    i = a = l-1;
    j = b = u+1;
    for (;;) {
        // loop invariant:
        //   x[l..a] == x[l] && x[b..u] == x[l] &&
        //   x[a+1..i] < x[l] && x[u..b-1] >= x[l]
        while (++i < b && x[i] <= x[l]) {
            if (x[i] == x[l])
                swap(x, i, ++a);
        }
        while (--j > a && x[j] >= x[l]) {
            if (x[j] == x[l])
                swap(x, j, --b);
        }
        if (i > j) {
            --i;
            ++j;
            assert(i+1 == j);
            break;
        }
        swap(x, i, j);
    }
    while (a >= l) {
        swap(x, a--, i--);
    }
    while (b <= u) {
        swap(x, b++, j++);
    }
    *pa = i;
    *pb = j;
}


void fat_qsort(int x[], int l, int u)
{
    int i, j;
    if (l >= u)
        return;
    fat_partiton(x, l, u, &i, &j);
    fat_qsort(x, l, i);
    fat_qsort(x, j, u);
}


int validate_sorted(int x[], int n)
{
    for (int i = 0; i < n-1; i++) {
        if (x[i] > x[i+1])
            return 0;
    }
    return 1;
}

#define MAXN 10000000

int x[MAXN];

int main()
{
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
        fat_qsort(x, 0, n-1);
        ticks = clock();
        printf("n: %d, ticks: %d, secs: %.2f\n",
                n, (int) ticks, (float) ticks / CLOCKS_PER_SEC);
        if (!validate_sorted(x, n))
            printf("error: qsort is incorrect\n");
    }
    return 0;
}

