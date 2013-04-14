#include <stdio.h>
#include <stdlib.h>
#include "../inc/bst.h"

int main()
{
    BSTree tree;

    tree = tree_new();
    for (int i = 0; i < 10; i++)
        tree_insert(tree, i);
    tree_draw(tree);
    for (int i = 0; i < 10; i++) {
        int k = rand() % 10;
        tree_delete(tree, k);
        printf("---------\n");
        printf("deleting %d\n", k);
        printf("---------\n");
        tree_draw(tree);
    }
}
