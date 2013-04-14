#include "../inc/pat.h"

#include <stdio.h>

int main()
{
    PAT t = pat_new();

    pat_draw(t);
    pat_insert(t, 'A');
    pat_draw(t);
    puts("");
    pat_insert(t, 'S');
    pat_draw(t);
    puts("");
    pat_insert(t, 'E');
    pat_draw(t);
    puts("");
    pat_insert(t, 'R');
    pat_draw(t);
    puts("");
    pat_insert(t, 'C');
    pat_draw(t);
    puts("");
    pat_insert(t, 'H');
    pat_draw(t);
    puts("");
    pat_insert(t, 'N');
    pat_draw(t);
    puts("");

    Item i;
    Key k;
    while ((k = getchar()) != EOF) {
        if (k == '\n' || k == ' ')
            continue;
        i = pat_search(t, k);
        if (i == NULLitem)
            printf("%c: miss\n", k);
        else
            printf("%c: hit\n", k);
    }

    pat_free(&t);
    pat_draw(t);

    return 0;
}
