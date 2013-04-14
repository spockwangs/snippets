/*
 * rotate.c -- Problem B of column 2
 *   Rotate an array left by i positions.
 */

#include <stdio.h>
#include <assert.h>

/*
 * rotate_left1 -- Solution 1
 *   Rotate x[0..n-1] left by i positions.
 */
void rotate_left1(int x[], int n, int i)
{
    int j, k, m;

    j = 0;
    m = 0;
    while (j < n) {
        int t = x[m];
        k = m;
        while ((k+i)%n != m) {
            x[k%n] = x[(k+i)%n];
            k = (k+i)%n;
            ++j;
        }
        x[k] = t;
        ++j;
        ++m;
    }
}

static void reverse(int x[], int i, int j)
{
    assert(i <= j);

    while (i < j) {
        int t = x[i];
        x[i] = x[j];
        x[j] = t;
        ++i;
        --j;
    }
}

/*
 * rotate_left2 -- Solution 2
 */
void rotate_left2(int x[], int n, int i)
{
    reverse(x, 0, i-1);
    reverse(x, i, n-1);
    reverse(x, 0, n-1);
}

static void swap(int x[], int y[], int n)
{
    int t, i;

    assert(n > 0);
    for (i = 0; i < n; i++) {
        t = x[i];
        x[i] = y[i];
        y[i] = t;
    }
}

/*
 * rotate_left3 -- Solution 3
 */
void rotate_left3(int x[], int n, int i)
{
    i = i%n;
    assert(n > i);

    while (i != 0 && i != n) {
        if (i <= n/2) {
            swap(x, x+n-i, i);
            n = n-i;
        } else {
            swap(x, x+i, n-i);
            x = x+n-i;
            int t = n;
            n = i;
            i = 2*i-t;
        }
    }
}
    
int main()
{
    int A[] = { 1, 2, 3, 4, 5, 6 };

    rotate_left3(A, sizeof(A)/sizeof(A[0]), 6);

    for (int i = 0; i < 6; i++)
        printf("%d ", A[i]);

    printf("\n");
    return 0;
}
