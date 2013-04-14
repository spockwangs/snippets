#include <stdio.h>
#include <stdlib.h>
#include "../inc/rbtree.h"

#define N   10

void print(Item item)
{
    printf("%d ", item);
}

int main()
{
    RBtree t1, t2;

    t1 = tree_new();
    for (int i = 0; i < N; i++)
        tree_insert(t1, i);
    printf("t1\n");
    printf("--\n");
    tree_draw(t1);

    t2 = tree_new();
    for (int i = 0; i < N; i++)
        tree_insert(t2, i+2*N);
    printf("t1\n");
    printf("--\n");
    tree_draw(t2);

    RBtree t3 = tree_join(t1, N, t2);
    printf("t3\n");
    printf("--\n");
    tree_draw(t3);

/*
    for (int i = 0; i < 3*N; i++) {
        int k = rand() % (3*N);
        tree_delete(t3, k);
        printf("---------\n");
        printf("deleting %d\n", k);
        printf("---------\n");
        tree_show(t3);
    }

    tree_walk(t3, print);
    printf("\n");
    for (int i = 0; i < tree_size(t3); i++) {
        printf("#%d: %d\n", i, tree_select(t3, i));
    }
*/
    tree_free(&t3);
}
