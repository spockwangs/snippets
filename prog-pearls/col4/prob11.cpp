/*
 * prob11.cpp -- Problem 11 of column 4
 *
 *   Write a recursive binary search function with this declaration
 *      int binarysearch(DataType x[], int n, DataType t)
 *   (Note: original declaration in the book has problem.  It does not
 *   indicate what we are looking for.)
 */

#include <iostream>
#include <cassert>

/*
 * binarysearch --
 *   Find the occurence of 't' in x[0..n-1] and return its index.
 *   If not found return -1.
 */
template <class DataType>
int binarysearch(DataType x[], int n, DataType t)
{
    assert(x != 0 && n >= 0);

    if (n <= 0)
        return -1;

    int mid = n/2;
    if (x[mid] == t)
        return mid;
    else if (x[mid] > t) {
        return binarysearch(x, mid, t);
    } else {
        // Note we are returning the index in the original array so we
        // should fix the returning index.
        int p = binarysearch(x+mid+1, n-mid-1, t);
        if (p != -1)
            return mid+1+p;
        else
            return -1;
    }
}

#define NELEM(a) (sizeof(a)/sizeof(a[0]))

int main()
{
    int array[100];

    for (int i = 0; (size_t) i < NELEM(array); i++)
        array[i] = 10*i;
    for (int i = 0; (size_t) i < NELEM(array); i++) {
        assert(binarysearch(array, NELEM(array), array[i]) == i);
        assert(binarysearch(array, NELEM(array), array[i]+5) == -1);
    }
    assert(binarysearch(array, NELEM(array), -5) == -1);

    return 0;
}
