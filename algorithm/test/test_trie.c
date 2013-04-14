#include <stdio.h>
#include <stdlib.h>
#include "../inc/trie.h"

int main()
{
    Trie t = trie_new();

    trie_draw(t);
    for (int i = 0; i < 10; i++) {
        trie_insert(t, rand()%10);
        trie_draw(t);
    }

    trie_draw(t);
    Item item;
    for (int i = 0; i < 10; i++) {
        item = trie_search(t, i);
        if (item == NULLitem)
            printf("%d: miss\n", i);
        else if (item == i)
            printf("%d: hit\n", i);
        else
            printf("%d: error\n", i);
    }
    trie_free(&t);
    return 0;
}
