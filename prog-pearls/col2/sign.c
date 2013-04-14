/*
 * sign.c -- Problem C, column 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORDMAX 100

int charcmp(const void *x, const void *y)
{
    return *(char *)x - *(char *)y;
}

static void lower(char *s)
{
    while (*s != '\0') {
        *s = tolower(*s);
        s++;
    }
}

int main(void)
{
    char word[WORDMAX], sig[WORDMAX];
    while (scanf("%s", word) != EOF) {
        lower(word);
        strcpy(sig, word);
        qsort(sig, strlen(sig), sizeof(char), charcmp);
        printf("%s %s\n", sig, word);
    }
    return 0;
}
