/*
 * prob1.cpp -- Problem 1 of column 14
 */

#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * Template to represent priority queue.
 *
 * Using array to represent it.
 */
template <class T>
class priqueue1 {
public:
    priqueue1(int m) {
        assert(m > 0);
        x = new int[m];
        maxsize = m;
        n = 0;
    }
    ~priqueue1() {
        delete[] x;
    }

    void insert(T t) {
        int j = bsearch(t);
        for (int i = n-1; i >= j; i--)
            x[i+1] = x[i];
        x[j] = t;
        n++;
    }

    T extractmin() {
        int r = x[0];
        for (int i = 1; i <= n-1; i++)
            x[i-1] = x[i];
        n--;
        return r;
    }

private:
    T *x;
    int n, maxsize;

    /*
     * Find the index to the smallest element which is greater than t
     * so we can insert t there to maintain the sorted sequence.
     */
    int bsearch(T t) {
        int l, u;
        l = -1, u = n;
        while (l+1 != u) { 
            // invariant: l < u && x[l] < t <= x[u]
            int m = (l+u)/2;
            if (x[m] < t)
                l = m;
            else
                u = m;
        }
        // assert: l+1 = u && x[l] < t <= x[u]
        return u;
    }
};


/**
 * Template to represent priority queue.
 *
 * Using heap to represent it.
 */
template <class T>
class priqueue2 {
public:
    priqueue2(int m) {
        assert(m > 0);
        x = new int[m+1];   // x[0] is not used
        maxsize = m;
        n = 0;
    }
    ~priqueue2() {
        delete[] x;
    }

    void insert(T t) {
        int i, p;
        x[++n] = t;
        for (i = n; i > 1 && x[p=i/2] > x[i]; i = p)
            swap(p, i);
    }

    T extractmin() {
        int i, c;
        T t = x[1];
        x[1] = x[n--];
        for (i = 1; (c = 2*i) <= n; i = c) {
            if (c+1 <= n && x[c+1] < x[c])
                c++;
            if (x[i] <= x[c])
                break;
            swap(c, i);
        }
        return t;
    }
private:
    T *x;
    int n, maxsize;
    void swap(int i, int j) {
        T t = x[i];
        x[i] = x[j];
        x[j] = t;
    }
};


template <class PQ, class T>
void pqsort(T v[], int n)
{
    PQ pq(n);
    int i;
    for (i = 0; i < n; i++)
        pq.insert(v[i]);
    for (i = 0; i < n; i++)
        v[i] = pq.extractmin();
}

const int MAXN = 10000000;
int x[MAXN];

int main()
{
    int algnum, n;
    while (cin >> algnum >> n) {
        if (n > MAXN) {
            cerr << "n should be no more than " << MAXN << endl;
            exit(1);
        }
        clock_t start, ticks;
        start = clock();
        switch (algnum) {
        case 1:
            pqsort<priqueue1<int> >(x, n);
            break;
        case 2:
            pqsort<priqueue2<int> >(x, n);
            break;
        }
        ticks = clock() - start;
        cout << "algnum: " << algnum << ", n: " << n << ", ticks: " << ticks << endl;
    }
        return 0;
}

