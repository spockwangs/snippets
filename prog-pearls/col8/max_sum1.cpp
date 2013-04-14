/*
 * max_sum1.cpp -- algorithm 1 of column 8
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
    int i, j, k;

    double max_sofar = 0;
    for (i = 0; (size_t) i < x.size(); i++) {
        for (j = i; (size_t) j < x.size(); j++) {
            double sum = 0;
            for (k = i; k <= j; k++) {
                sum += x[k];
            }
            max_sofar = std::max(max_sofar, sum);
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
