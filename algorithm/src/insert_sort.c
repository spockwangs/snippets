#include "../inc/sort.h"

void insert_sort(ElemType A[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i-1;
        while (j >= 0 && A[j] > key) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = key;
    }
}
