/*
 * prob7.cpp -- Problem 7 of column 14
 */

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cassert>

using namespace std;


/*
 * Put sorted x[] into heapsearch order in y[].
 */
void preprocess(int x[], int n, int y[])
{
    int k = 0, power;
    for (power = 1; power <= n+1; power *= 2)
        k++;
    // assert: 2^(k-1) <= n+1 < 2^k && power = 2^k
    //    i.e. 2^(k-1)-1 <= n < 2^k-1
    k = n - (power/2-1);

    int i = n;
    int j = 2*(k-1);
    int m = j;
    while (j >= 0) {
        y[i--] = x[j];
        if (j > 0)
            x[m--] = x[j-1];
        j -= 2;
    }
    x += k;
    n -= k;

    power = 2;
    j = n;
    k = n-1;
    while (j > 0) {
        for (i = k; i >= 0; i -= power) {
            y[j--] = x[i];
        }
        k -= power/2;
        power *= 2;
    }
}


int search(int x[], int n, int t)
{
    int i = 1;
    while (i <= n) {
        if (x[i] == t)
            return i;
        else if (t < x[i])
            i = 2*i;
        else
            i = 2*i+1;
    }
    return -1;
}


const int MAXN = 10;
int x[MAXN];

int main()
{
    srand(time(0));
    for (int i = 0; i < MAXN; i++)
        x[i] = i;
    int *y = new int[MAXN+1];
    preprocess(x, MAXN, y);
    copy(y+1, y+MAXN+1, ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
