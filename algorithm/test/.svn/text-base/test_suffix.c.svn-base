#include "../inc/suffix_tree.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXN 10000000

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "2 arguments required\n");
        exit(1);
    }

    int c;
    FILE *fp = fopen(argv[1], "r");
    char *texts = malloc(MAXN);
    int n = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (n < MAXN-1)
            texts[n++] = c;
        else
            break;
    }
    fclose(fp);
    texts[n-1] = '\0';

    ST st = st_new(texts);
    free(texts);
    self_test(st);
    printf("Search for string: ");
    char str[1000];
    while (scanf("%s", str) != EOF) {
        st_substr(st, str);
        printf("Search for string: ");
    }
    st_free(&st);
    return 0;
}
