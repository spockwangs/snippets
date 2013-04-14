/*
 * Skip list
 *   See section 13.5, Robert Sedgewick, "Algorithms in C, Parts 1-4", third edtion.
 */

#include "../inc/SkipList.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define T SkipList

typedef struct node *Link;
struct node {
    Link *next;
    int sz;
    Item item;
};

struct T {
    Link head;
    int N;      // # of items in the skip list
    int lgN;    // # of levels in the skip list
};

#define lgNMAX  10      // max # of levels

#define null(x) (x == NULL)


        /* function prototypes */

static Link list_join(Link l1, Link l2, int k);


static inline Link NEW(Item item, int k)
{
    Link x = malloc(sizeof *x);
    assert(x != NULL);
    x->next = malloc((size_t) k*sizeof(Link));
    x->item = item;
    x->sz = k;
    for (int i = 0; i < k; i++)
        x->next[i] = NULL;
    return x;
}


/*
 * SkipList_new --
 *   Create a new skip list.
 */
T SkipList_new(void)
{
    T list = malloc(sizeof *list);
    assert(list != NULL);
    list->head = NEW(NULLitem, lgNMAX+1);
    list->N = 0;
    list->lgN = 0;
    return list;
}


/*
 * SkipList_free --
 *   Destroy the skip list and free all memory.
 */
void SkipList_free(T *skiplist)
{
    assert(skiplist != NULL);

    if (*skiplist == NULL)
        return;

    Link x, y;
    x = (*skiplist)->head;
    while (!null(x)) {
        y = x->next[0];
        free(x);
        x = y;
    }
    free(*skiplist);
    *skiplist = NULL;
}


/*
 * SkipList_search --
 *   Search for the item with key.
 */
Item SkipList_search(T skiplist, Key key)
{
    assert(skiplist != NULL);

    Link x;
    int k;

    x = skiplist->head;
    k = skiplist->lgN;
    while (1) {
        if (EQ(key, KEY(x->item)))
            return x->item;
        if (LESS(key, KEY(x->item))) {
            if (k == 0)
                return NULLitem;
            k--;
        } else {
            x = x->next[k];
        }
    }
}


/*
 * randX --
 *   Return a random integer i with the probability 1/(2**i).
 */
static int randX(void)
{
    int i, j, t = rand();

    for (i = 1, j = 2; i < lgNMAX; i++, j += j) {
        if (t > RAND_MAX/j)
            break;
    }
    return i;
}


/*
 * SkipList_insert --
 *   Insert a new item into the list.
 */
void SkipList_insert(T skiplist, Item item)
{
    assert(skiplist != NULL);

    Link x, t;
    int k;

    k = randX();
    if (k > skiplist->lgN)
        skiplist->lgN = k;
    x = NEW(item, k);
    t = skiplist->head;
    k = skiplist->lgN;
    while (1) {
        if (null(t->next[k]) || LESS(KEY(item), KEY(t->next[k]->item))) {
            if (k < x->sz) {
                x->next[k] = t->next[k];
                t->next[k] = x;
            }
            if (k == 0)
                break;
            k--;
        } else {
            t = t->next[k];
        }
    }
    skiplist->N++;
}


/*
 * SkipList_delete --
 *   Delete a item with the 'key' from the list.
 */
void SkipList_delete(T skiplist, Key key)
{
    assert(skiplist != NULL);

    Link x, t;
    int k;

    k = skiplist->lgN;
    t = skiplist->head;
    while (1) {
        x = t->next[k];
        if (null(x)) {
            if (k == 0)
                return;
            k--;
        } else if (EQ(key, KEY(x->item))) {
            t->next[k] = x->next[k];
            if (k == 0) {
                free(x);
                skiplist->N--;
                return;
            }
            k--;
        } else if (LESS(key, KEY(x->item))) {
            if (k == 0)
                return;
            k--;
        } else {
            t = x;
        }
    }
}
    

/*
 * SkipList_join --
 *   Join two skip lists into one and destroy original 2 lists.
 */
T SkipList_join(T list1, T list2)
{
    assert(list1 != NULL && list2 != NULL);

    /*
     * Make sure # levels of list1 is larger.
     */
    if (list1->lgN < list2->lgN) {
        T t = list1;
        list1 = list2;
        list2 = t;
    }

    for (int i = 0; i < list1->lgN; i++) {
        list1->head->next[i] = list_join(list1->head->next[i], list2->head->next[i], i);
    }
    list1->N += list2->N;
    free(list2);
    return list1;
}


static Link list_join(Link l1, Link l2, int k)
{
    Link r, p, q, x;

    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    p = l1, q = l2;
    if (LESS(KEY(q->item), KEY(p->item))) {
        x = q->next[k];
        q->next[k] = p;
        p = q;
        q = x;
    } 
    r = p;

    /*
     * Now I'm sure that key(p) <= key(q).
     * key(p) <= key(q) is satisfied every time before the loop.
     */
    while (q != NULL && p->next[k] != NULL) {
        if (LESS(KEY(q->item), KEY(p->next[k]->item))) {
            /* insert q just after p */
            x = q->next[k];
            q->next[k] = p->next[k];
            p->next[k] = q;
            p = q;
            q = x;
        } else {
            p = p->next[k];
        }
    }

    if (q != NULL) {
        p->next[k] = q;
    }

    return r;
}


void SkipList_show(const T skiplist)
{
    assert(skiplist != NULL);

    Link x = skiplist->head->next[0];
    int i = 1;
    while (!null(x)) {
        printf("%s%d(%d)", i == 1 ? "" : "->", x->item, x->sz);
        i = 0;
        x = x->next[0];
    }
    printf(" N = %d, lgN = %d", skiplist->N, skiplist->lgN);
}


/*
 * Draw an ascii picture of a skip list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LABEL_LEN   20

struct link_rec {
    int label_len;
    char label[LABEL_LEN+1];
    int *level_len;     /* len of spaces between two links at level k */
    int sz;             /* # levels of this link */
    struct link_rec *next;
};


void *my_alloc(size_t sz)
{
    void *p = malloc(sz);
    if (p == NULL) {
        fprintf(stderr, "Run out of mem. Request size = %u.\n", sz);
        exit(1);
    }
    return p;
}

void my_free(void *p)
{
    free(p);
}

void free_link_rec(struct link_rec *x)
{
    assert(x != NULL);

    struct link_rec *y;
    
    while (x != NULL) {
        y = x->next;
        free(x->level_len);
        free(x);
        x = y;
    }
}

struct link_rec *build_link_rec(const T list)
{
    struct link_rec *r, *p, *q;
    Link x, y;
    
    r = my_alloc(sizeof(*r));
    r->sz = list->lgN;
    r->level_len = my_alloc(r->sz * sizeof(*r->level_len));
    r->label_len = 1;

    x = list->head->next[0];
    p = r;
    while (!null(x)) {
        p->next = my_alloc(sizeof(struct link_rec));
        p = p->next;
        p->sz = x->sz;
        p->level_len = my_alloc(p->sz * sizeof(*p->level_len));
        sprintf(p->label, "%d", KEY(x->item));
        p->label_len = strlen(p->label);
        x = x->next[0];
    }
    p->next = NULL;

    for (int i = 0; i < list->lgN; i++) {
        x = list->head;
        p = r;
        int len;
        while (1) {
            if (null(x->next[i])) {
                p->level_len[i] = 0;
                break;
            }
            len = p->label_len/2;
            y = x->next[0];
            q = p->next;
            while (y != x->next[i]) {
                len += 1 + q->label_len;
                y = y->next[0];
                q = q->next;
            }
            len += 1 + (q->label_len-1)/2;
            p->level_len[i] = len;
            x = y;
            p = q;
        }
    }

    return r;
}

void SkipList_draw(const T list)
{
    struct link_rec *x, *y;

    x = build_link_rec(list);

    int levels = x->sz;
    for (int i = levels-1; i >= 0; i--) {
        y = x;
        while (1) {
            printf("*");
            for (int j = 0; j < y->level_len[i]; j++)
                printf(" ");
            y = y->next;
            while (y != NULL) {
                if (y->sz > i)
                    break;
                y = y->next;
            }
            if (y == NULL)
                break;
        }
        printf("\n");
    }
    
    printf("  ");
    y = x->next;
    while (y != NULL) {
        printf("%s ", y->label);
        y = y->next;
    }
    printf("\n");
    free_link_rec(x);
}
