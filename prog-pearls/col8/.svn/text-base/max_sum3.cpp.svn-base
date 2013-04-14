/*
 * max_sum3.cpp -- algorithm 3 of column 8
 *   Find the maximum sum in any contiguous subvector of the input
 *   vector.
 */

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

double max_sum(const vector<double>& x, int l, int r)
{
    if (l > r)  // 0 elements
        return 0.0;
    if (l == r) // 1 element
        return max(0.0, x[l]);

    int m = (l+r)/2;
    double sum, lmax, rmax;

    // find max crossing to left
    lmax = sum = 0;
    for (int i = m; i >= l; i--) {
        sum += x[i];
        lmax = max(lmax, sum);
    }

    // find max crossing to right
    rmax = sum = 0;
    for (int i = m+1; i <= r; i++) {
        sum += x[i];
        rmax = max(rmax, sum);
    }

    return max(lmax+rmax, max(max_sum(x, l, m), max_sum(x, m+1, r)));
}

double max_sum(const vector<double>& x)
{
    return max_sum(x, 0, x.size()-1);
}


#define NELEM(a) (sizeof(a)/sizeof(a[0]))

int main()
{
    using std::cout;
    using std::endl;

    double arr[] = { 31, -41, 59, 26, -53, 58, 97, -93, -23, 84 };
    std::vector<double> x(arr, arr+NELEM(arr));

    cout << "max sum: " << max_sum(x) << endl;

    return 0;
}
