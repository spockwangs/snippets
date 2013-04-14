/*
 * prob5.c -- Problem 5 of column 11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void swap(char *x[], int i, int j);


void bsort(char *x[], int l, int u, int depth)
{
    if (l >= u)
        return;
    for (int i = l; i <= u; i++) {
        if (strlen(x[i]) <= (size_t) depth)
            swap(x, i, l++);
    }
    int m = l;
    for (int i = l; i <= u; i++)
        if (x[i][depth] == '0')
            swap(x, i, m++);
    bsort(x, l, m-1, depth+1);
    bsort(x, m, u, depth+1);
}


void swap(char *x[], int i, int j)
{
    char *t = x[i];
    x[i] = x[j];
    x[j] = t;
}


#define MAXN 1000
#define MAXLEN  100

int main()
{
    char *str, *x[MAXN];
    int i = 0;
    str = malloc(MAXLEN*sizeof(char));
    assert(str != NULL);
    printf("Input bit strings: \n");
    while (scanf("%s", str) != EOF) {
        x[i++] = str;
        str = malloc(MAXLEN*sizeof(char));
        assert(str != NULL);
    }
    bsort(x, 0, i-1, 0);
    printf("Sorted bit strings: \n");
    for (int j = 0; j < i; j++)
        printf("%s\n", x[j]);
    return 0;
}
