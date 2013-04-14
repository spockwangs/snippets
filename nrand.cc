/*
 * Copyrith (c) 2010 wbb.
 *
 * Date: 2010-12-26
 *
 * Compute a random integer in the range [0, n) no matter how big n is.
 * The system provides a function rand() which returns a random integer in
 * the range [0, RAND_MAX].
 */

#include <cstdlib>
#include <iostream>
#include <cassert>

using namespace std;

/*
 * nrand_small --
 *   Return a random integer in the range [0, n), where n must be no more
 *   than RAND_MAX.
 */
int nrand_small(int n)
{
    assert(n >= 0 && n <= RAND_MAX);

    const int bucket_size = RAND_MAX/n;
    int r;

    do {
        r = rand() / bucket_size;
    } while (r >= n);
    return r;
}

/*
 * nrand --
 *   Return a random integer in the range [0, n), where n may be any
 *   positive integer.
 */
int nrand(int n)
{
    assert(n >= 0);

    if (n <= RAND_MAX)
        return nrand_small(n);

    int q = n/RAND_MAX;
    if (n%RAND_MAX != 0)
        ++q;
    int r;
    do {
        r = nrand(q)*RAND_MAX + nrand_small(RAND_MAX);
    } while (r >= n);

    return r;
}

int main()
{
    for (int i = 0; i < 10; i++)
        cout << nrand(10) << endl;
    return 0;
}
