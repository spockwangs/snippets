/*
 * prob2.cpp -- Problem 2 of column 4
 */

#include <iostream>
#include <iterator>
#include <cassert>
#include <cstdio>
#include <cstdlib>

using namespace std;

/*
 * binary_search --
 *   Return index of the first occurence of 't' in the array[i..j] if
 *   any, or return -1.
 */
template <class T>
int binary_search(T array[], int n, T t)
{
    int l, u, m;
    
    l = -1;
    u = n;
    // loop invariant: x[l] < t && t <= x[u] && l < u
    while (l+1 != u) {
        m = (l+u)/2;
        if (array[m] < t)
            l = m;
        else
            u = m;
    }
    // assert l+1 = u && x[l] < t && t <= x[u]
    if (u >= n || array[u] != t)
        return -1;
    return u;
}


/*
 * sequential_search --
 *   Return index of the first occurence of 't' in x[] if any, or -1.
 *   It is used for checking binary_search.
 */
template <class T>
int sequential_search(T x[], int n, T t)
{
    assert(x != NULL && n > 0);

    for (int i = 0; i < n; i++) {
        if (x[i] == t)
            return i;
    }
    return -1;
}


#define NELEM(a) (sizeof(a)/sizeof(a[0]))
#define MAXN 100000000

int x[MAXN];

int main()
{
    for (int i = 0; i < MAXN; i++)
        x[i] = 2*i;

    int n;
    while (scanf("%d", &n) != EOF) {
        if (n > MAXN) {
            printf("n should be no more than %d\n", MAXN);
            continue;
        }

        clock_t start = clock();
        int thisans, target = rand() % n;
        thisans = binary_search(x, n, target);
        clock_t ticks = clock() - start;
        printf("n: %d, ans: %d, ticks: %d, sec: %.2f\n",
                n, thisans, (int) ticks, (float) ticks/CLOCKS_PER_SEC);
        int chkans = sequential_search(x, n, target);
        if (thisans != chkans)
            printf("error: mismatch with sequential_search(): %d\n", chkans);
    }

    return 0;
}
