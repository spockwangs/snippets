#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include "sort.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// round x up to the nearest multiples of n
#define ROUNDUP(x, n) ((x) % (n) == 0 ? (x) : ((x)/(n)+1)*(n))

#define NSIZE(a)    (sizeof(a)/sizeof(a[0]))

void swap(int A[], int i, int j);
int random(int a, int b);
void min_max(int A[], int n, int *pmin, int *pmax);
int partition(int A[], int p, int r, int pivot);
int partition2(int A[], int p, int r, int pivot);
int random_partition(int A[], int p, int r);
int unimodal_search(int A[], int a, int b);
int random_select(int A[], int n, int k);
int linear_select(int A[], int n, int k);
int small_select(int A[], int n, int k);

#endif /* !__ALGORITHM_H */
