/*
 * prob10.c -- Problem 10 of column 15
 */

/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* longdup.c -- Print longest string duplicated M times */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int pstrcmp(const void *p, const void *q)
{
    return strcmp(*(const char **) p, *(const char **) q);
}

int comlen(char *p, char *q)
{
    int i = 0;

    while (*p && (*p++ == *q++))
        i++;
    return i;
}

int getword(char *w)
{
    if (scanf("%s", w) == EOF)
        return EOF;
    return strlen(w);
}

#define M 1
#define MAXN 5000000
char c[MAXN], *a[MAXN];

int main()
{
    int i, wordlen, n = 0, maxi, maxlen = -1, nword = 0;

    while ((wordlen = getword(&c[n])) != EOF) {
        a[nword++] = &c[n];
        n += wordlen;
        c[n++] = ' ';
    }
    c[n] = 0;
    qsort(a, nword, sizeof(char *), pstrcmp);
    for (i = 0; i < nword - M; i++)
        if (comlen(a[i], a[i + M]) > maxlen) {
            maxlen = comlen(a[i], a[i + M]);
            maxi = i;
        }
    printf("%.*s\n", maxlen, a[maxi]);
    return 0;
}
