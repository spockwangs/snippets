/*
 * Paricia Trie
 */

#include "../inc/pat.h"
#include <assert.h>
#include <stdlib.h>

#define T PAT

typedef struct node *Link;
struct node {
    Link left, right;
    int bit;
    Item item;
};

struct T {
    Link root;
};


static Link new(Link l, Link r, int bit, Item item);
static void make_empty(Link l);
static Item search(Link h, Key key, int w);
static Link insert(Link l, Item item, int w, Link p);


/*
 * pat_new --
 *   Create a new patricia trie.
 */
T pat_new(void)
{
    T t = malloc(sizeof *t);
    assert(t != NULL);
    t->root = new(NULL, NULL, -1, NULLitem);
    t->root->left = t->root->right = t->root;
    return t;
}


/*
 * pat_free --
 *   Destroy a patricia trie.
 */
void pat_free(T *t)
{
    assert(t != NULL);
    make_empty((*t)->root->left);
    free((*t)->root);
    free(*t);
    *t = NULL;
}


static void make_empty(Link l)
{
    if (l->left->bit > l->bit)
        make_empty(l->left);
    if (l->right->bit > l->bit)
        make_empty(l->right);
    if (l->bit != -1) {
        free(l);
    }
}


/*
 * pat_search --
 *   Search for a item with the 'key'.
 */
Item pat_search(T t, Key key)
{
    Item item = search(t->root->left, key, -1);
    return EQ(key, KEY(item)) ? item : NULLitem;
}


static Item search(Link h, Key key, int w)
{
    if (h->bit <= w)
        return h->item;
    if (DIGIT(key, h->bit) == 0)
        return search(h->left, key, h->bit);
    else
        return search(h->right, key, h->bit);
}


/*
 * pat_insert --
 *   Insert a new item into the 'trie'.
 */
void pat_insert(T trie, Item item)
{
    assert(trie != NULL);

    int i;
    Key v, t;

    v = KEY(item);
    t = KEY(search(trie->root->left, v, -1));
    if (v == t)
        return;
    for (i = 0; DIGIT(v, i) == DIGIT(t, i); i++)
        ;
    trie->root->left = insert(trie->root->left, item, i, trie->root);
}


static Link insert(Link l, Item item, int w, Link p)
{
    Link x;
    if (l->bit >= w || l->bit <= p->bit) {
        x = new(NULL, NULL, w, item);
        x->left = DIGIT(KEY(item), x->bit) ? l : x;
        x->right = DIGIT(KEY(item), x->bit) ? x : l;
        return x;
    }
    if (DIGIT(KEY(item), l->bit) == 0)
        l->left = insert(l->left, item, w, l);
    else
        l->right = insert(l->right, item, w, l);
    return l;
}


static Link new(Link l, Link r, int bit, Item item)
{
    Link x = malloc(sizeof *l);
    assert(x != NULL);
    x->left = l;
    x->right = r;
    x->bit = bit;
    x->item = item;
    return x;
}


/**********************************
 *  Draw an trie.
 **********************************/

#include <string.h>
#include <stdio.h>

typedef struct info {
    struct info *left, *right, *p;
    int col;
    int sz;
    char info[10];
} info_node;

static info_node *build_node_info(const Link node)
{
    assert(node != NULL);

    info_node *r = malloc(sizeof *r);
    assert(r != NULL);

    if (node->left->bit > node->bit)
        r->left = build_node_info(node->left);
    else 
        r->left = NULL;
    if (node->right->bit > node->bit)
        r->right = build_node_info(node->right);
    else
        r->right = NULL;
    if (r->left != NULL)
        r->left->p = r;
    if (r->right != NULL)
        r->right->p = r;
    sprintf(r->info, "%c(%d)", node->item, node->bit);
    r->sz = (r->left == NULL ? 0 : r->left->sz) +
            (r->right == NULL ? 0 : r->right->sz) + 1;
    return r;
}

static void free_node_info(info_node *node)
{
    if (node == NULL)
        return;
    free_node_info(node->left);
    free_node_info(node->right);
    free(node);
}

static void colno(info_node *r, int n)
{
    if (r != NULL) {
        colno(r->left, n);
        int j;
        j = (r->left == NULL ? 0 : r->left->sz) + 1;
        info_node *y = r;
        while (y->p != NULL) {
            if (y == y->p->right)
                j = j + 1 + (y->p->left == NULL ? 0 : y->p->left->sz);
            y = y->p;
        }
        r->col = 40*j/n + 4;
        colno(r->right, n);
    }
}

void pat_draw(const T tree)
{
    if (tree == NULL)
        return;
    info_node *root = build_node_info(tree->root->left);
    info_node *active[root->sz], *waiting[root->sz];
    int k, newk, j;
    info_node *p;
    char line[100];

    colno(root, root->sz);
    waiting[0] = root;

    k = 0;
    while (k >= 0) {
        memset(line, ' ', sizeof line);
        line[sizeof(line)-1] = '\0';
        for (j = 0; j <= k; j++) {
            active[j] = p = waiting[j];
            line[p->col] = '|';
        }
        printf("%s\n%s\n", line, line);
        memset(line, ' ', sizeof line);
        line[sizeof(line)-1] = '\0';
        newk = -1;
        for (j = 0; j <= k; j++) {
            int cl, cr;
            p = active[j];
            cl = cr = p->col;
            if (p->left != NULL) {
                cl = p->left->col;
                newk++;
                waiting[newk] = p->left;
            }
            if (p->right != NULL) {
                cr = p->right->col;
                newk++;
                waiting[newk] = p->right;
            }
            line[cl] = line[cr] = '+';
            for (int i = cl+1; i < cr; i++) {
                line[i] = '-';
            }
            int s = strlen(p->info);
            cl = p->col - s/2;
            for (int i = 0; i < s; i++) {
                line[cl+i] = p->info[i];
            }
        }
        printf("%s\n", line);
        k = newk;
    }
    free_node_info(root);
}
