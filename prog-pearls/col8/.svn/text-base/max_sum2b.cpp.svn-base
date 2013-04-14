/*
 * max_sum2b.cpp -- algorithm 2b of column 8
 *   Find the maximum sum in any contiguous subvector of the input
 *   vector.
 */

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

double max_sum(std::vector<double> x)
{
    int n = x.size();
    vector<double> cumarr;  // cumarr[i] contains cumulative sum of x[0..i]

    cumarr.push_back(x[0]);
    for (int i = 1; i < n; i++)
        cumarr.push_back(x[i]+cumarr[i-1]);

    double sum, max_sofar = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            sum = cumarr[j] - cumarr[i-1];
            // sum is sum of x[i..j]
            max_sofar = max(max_sofar, sum);
        }
    }
    return max_sofar;
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
