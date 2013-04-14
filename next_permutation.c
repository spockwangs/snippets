/*************************************************************************
 * next_permutation
 *   Compute next permutation of a sequence in lexicographical order.
 *   This function resembles next_permutation() in <algorithm> of C++
 *   standard library.
 *
 * Author: wbb
 * Date: 2010-03-01
 *
 * COMPILE
 *   gcc -W -Wall -pedantic -std=c99 next_permutation.c
 *************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>     /* for qsort() */
#include <string.h>

static void swap(char *p, char *q);
static int cmp(const void *p, const void *q);

/*
 * next_permutation --
 *   Return 1 if there is a new permutation and store the permutation
 *   in place, otherwise 0. 'begin' points to the first element and
 *   'end' points to beyond the last element.
 */
int next_permutation(char *begin, char *end)
{
    assert(begin < end);

    if (end-begin == 1)
        return 0;

    if (next_permutation(begin+1, end))
        return 1;
    else {
        qsort(begin+1, (unsigned) (end-begin-1), 1, cmp);

        char *p;
        for (p = begin+1; p < end; p++)
            if (*p > *begin)
                break;
        if (p >= end)
            return 0;
        else {
            swap(begin, p);
            return 1;
        }
    }
}


void swap(char *p, char *q)
{
    char tmp = *p;
    *p = *q;
    *q = tmp;
}

int cmp(const void *p, const void *q)
{
    return *(const char *)p - *(const char *)q;
}

int main()
{
    char perm[] = "abcd";
    
    printf("%s\n", perm);
    while (next_permutation(perm, perm+strlen(perm)))
        printf("%s\n", perm);
    return 0;
}
