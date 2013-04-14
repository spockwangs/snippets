/*
 * prob8.c -- Problem 8 of column 9
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


int max1(int x[], int n)
{
    assert(x != NULL && n > 0);

    int maximum = x[0];
    for (int i = 1; i < n; i++)
        if (x[i] > maximum)
            maximum = x[i];
    return maximum;
}


int max2(int x[], int n)
{
    assert(x != NULL && n > 0);

    int maximum
