#include "../inc/SkipList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
/*
    SkipList l;

    // test insertition
    l = SkipList_new();
    for (int i = 0; i < 10; i++) {
        SkipList_insert(l, i);
    }
    SkipList_show(l);
    printf("\n");

    // test delete
    for (int i = 0; i < 10; i++) {
        int j = rand() % 10;
        printf("\ndeleting %d\n", j);
        SkipList_delete(l, j);
        SkipList_show(l);
        printf("\n");
    }

    // test insert
    for (int i = 0; i < 10; i++) {
        int j = rand() % 10 + 10;
        printf("\ninserting %d\n", j);
        SkipList_insert(l, j);
        SkipList_show(l);
        printf("\n");
    }

    SkipList_free(&l);
*/
    /*
     * Test join operation.
     */

    SkipList l1, l2, l3;
    l1 = SkipList_new();
    l2 = SkipList_new();
    for (int i = 0; i < 10; i++) {
        SkipList_insert(l1, 2*i + 100);
        SkipList_insert(l2, 2*i+1 + 100);
    }
    printf("Skip list l1: \n");
    SkipList_draw(l1);
    SkipList_show(l1);
    printf("\n\n");

    printf("Skip list l2: \n");
    SkipList_draw(l2);
    SkipList_show(l2);
    printf("\n\n");
    
    l3 = SkipList_join(l1, l2);
    printf("Skip list l3: \n");
    SkipList_draw(l3);
    SkipList_show(l3);
    printf("\n");
}
