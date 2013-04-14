/*
 * binary_search.cpp -- column 5
 *   A binary search algorithm impelemntation.
 */

#include <iostream>
#include <cassert>

template <class T>
int binarysearch(T x[], int n, T t)
{
    int l, u, m;

    l = 0;
    u = n-1;
    while (l <= u) {
        m = l + (u-l)/2;
        if (x[m] < t)
            l = m+1;
        else if (x[m] == t)
            return m;
        else // x[m] > t
            u = m-1;
    }
    assert((u < 0 || x[u] < t) && (u+1 >= n || x[u+1] > t));
    return -1;
}


int main()
{
    const int n = 100;
    int x[n];
    for (int i = 0; i < n; i++)
        x[i] = 10*i;
    for (int i = 0; i < n; i++) {
        assert(binarysearch(x, n, 10*i) == i);
        assert(binarysearch(x, n, 10*i-5) == -1);
    }
    assert(binarysearch(x, n, 10*n-5) == -1);
    assert(binarysearch(x, n, 10*n) == -1);

    return 0;
}
