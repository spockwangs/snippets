/*
 * Sort an array of variable-length strings using radix sort.  
 *
 * See problem 8-3 of "Introduction to Algorithms", second edition.  The
 * algorithm used here is described in the solution to Problem 8-3 of
 * the accompanied book "Instructor's manual".
 *
 * Author: wbb 
 * Date: 2010-03-07
 */

#include <stdlib.h>     // for calloc() 
#include <assert.h>     // for assert()
#include <string.h>     // for memcpy()

static void count_sort(char *str_array[], int begin, int end, int k);

/*
 * sort_strings --
 *   Sort an array of variable-length strings in alphabetical order.
 */
void sort_strings(char *str_array[], int n)
{
    count_sort(str_array, 0, n, 0);
}

static void count_sort(char *str_array[], int begin, int end, int k)
{
    int C[27], C2[27];
    char **B = (char **) calloc((unsigned) (end-begin), sizeof(char *));
    assert(B);

    /*
     * apply counting sort on the kth character of
     * str_array[begin..end-1].
     */

    for (int i = 0; i < 27; i++)
        C[i] = 0;

    for (int i = begin; i < end; i++)
        if (str_array[i][k] == 0)
            C[0]++;
        else
            C[str_array[i][k]-'a'+1]++;
    memcpy(C2, C, 27 * sizeof(C[0]));

    for (int i = 1; i < 27; i++)
        C[i] += C[i-1];

    for (int i = end-1; i >= begin; i--) {
        int idx = str_array[i][k] == 0 ? 0 : str_array[i][k]-'a'+1;
        B[C[idx]-1] = str_array[i];
        C[idx]--;
    }

    /* copy B[0..end-begin] back to str_array[begin..end] */
    for (int i = begin; i < end; i++)
        str_array[i] = B[i-begin];
    free(B);

    /*
     * Gather together all strings with the same kth char as a group.
     * Then recursively apply counting sort on the (k+1)th
     * character of each group which has more than 1 string.
     */

    begin += C2[0];
    for (int i = 1; i < 27; i++) {
        if (C2[i] > 1)  // #element of this group > 1 
            count_sort(str_array, begin, begin+C2[i], k+1);
        begin += C2[i];
    }
}

#include <stdio.h>

int main()
{
    char *str[] = {
        "africa",
        "a",
        "def",
        "afrikaner"
        "edification",
        "agni",
        "sort",
        "ahmad",
        "aiken",
        "ab",
        "akron",
        "basil",
        "alan",
        "belau",
        "cantor",
        "canute"
        "knuth",
        "wbb",
        "alana",
        "derek",
        "descarte",
        "china",
        "amber",
        "adams",
        "amur",
    };

    sort_strings(str, sizeof(str)/sizeof(str[0]));
    for (int i = 0; (size_t) i < sizeof(str)/sizeof(str[0]); i++)
        printf("%s\n", str[i]);
}

