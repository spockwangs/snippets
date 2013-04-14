#include "../inc/suffix_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

char *test_cases[] = {
    "",
    "a",
    "ab",
    "aa",
    "abc",
    "abb",
    "aab",
    "aaa",
    "inintmainintpf",
    "mississippi",
    NULL
};

char *test_ms[] = {
    "", "",
    "", "a",
    "", "ab",
    "a", "a",
    "a", "ba",
    "a", "",
    "a", "bac",
    "a", "aa",
    "a", "cd",
    "aa", "",
    "aa", "a",
    "aa", "aa",
    "aa", "ab",
    "aa", "ba",
    "aa", "aaa",
    "aa", "abc",
    NULL
};


/*
 * compute_ms --
 *   A naive algorithm for computing mathcing statistics.
 */
void compute_ms(const char *s1, const char *s2, int *ms)
{
    int i, j, k;

    for (i = 0; (size_t) i < strlen(s2); i++) {
        int max = 0;
        for (j = 0; (size_t) j < strlen(s1); j++) {
            int m = 0;
            for (k = j; (size_t) k < strlen(s1); k++) {
                if (s2[i+m] == s1[k])
                    m++;
            }
            if (max < m)
                max = m;
        }
        ms[i] = max;
    }
}


int main()
{
    ST st;

    // Test suffix tree construction
    for (int i = 0; test_cases[i] != NULL; i++) {
        st = st_new(test_cases[i]);
        self_test(st);
        st_free(&st);
    }

    // Test matching statistics
    for (int i = 0; test_ms[i] != NULL; i += 2) {
        int len, *ms1, *ms2;

        st = st_new(test_ms[i]);
        len = strlen(test_ms[i+1]);
        ms1 = malloc(len * sizeof(int));
        if (ms1 == NULL)
            error(1, errno, "malloc failure");
        ms2 = malloc(len * sizeof(int));
        if (ms2 == NULL)
            error(1, errno, "malloc failure");
        st_ms(st, test_ms[i+1], ms1);

        compute_ms(test_ms[i], test_ms[i+1], ms2);
        if (memcmp(ms1, ms2, len * sizeof(int)) != 0) {
            printf("s1: %s, s2: %s\n", test_ms[i], test_ms[i+1]);
            printf("ms1: ");
            for (int j = 0; j < len; j++)
                printf("%d ", ms1[j]);
            printf("\nms2: ");
            for (int j = 0; j < len; j++)
                printf("%d ", ms2[j]);
            printf("\n");
            break;
        }
        st_free(&st);
    }
        

    return 0;
}
