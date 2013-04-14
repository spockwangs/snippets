/*
 * max_sum4.cpp -- algorithm 4 of column 8
 *   Find the maximum sum in any contiguous subvector of the input
 *   vector.
 */

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

double max_sum(std::vector<double> x)
{
    double max_sofar, max_endinghere;
    int i = 0, n = x.size();

    max_endinghere = max_sofar = 0.0;

    // loop invariant: max_endinghere contains max sum of contiguous
    // subvector of x0..i-1] ending with x[i-1] and max_sofar contains
    // max sum of any contiguous subvector of x[0..i-1].
    for (; i < n; i++) {
        max_endinghere = max(0.0, x[i]+max_endinghere);
        max_sofar = max(max_endinghere, max_sofar);
    }

    return max_sofar;
}


int main()
{
    using std::cout;
    using std::endl;

    std::vector<double> x;

    double f;
    while (cin >> f)
        x.push_back(f);
    cout << "max sum: " << max_sum(x) << endl;

    return 0;
}
