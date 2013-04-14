/*
 * trie
 */

#include "../inc/trie.h"
#include "../inc/item.h"
#include <assert.h>
#include <stdlib.h>

#define T Trie

typedef struct node* Link;
struct node {
    Link left, right;
    Item item;
};

struct T {
    Link root;
};

#define null(l) (l == NULL)

static Link new(Item item, Link l, Link r);
static Item search(Link h, Key key, int w);
static Link insert(Link t, Item item, int w);
static Link split(Link p, Link q, int w);
static void make_empty(Link l);


/*
 * trie_new --
 *   Create a new empty trie.
 */
T trie_new(void)
{
    T trie = malloc(sizeof(*trie));
    assert(trie != NULL);
    trie->root = NULL;
    return trie;
}


/*
 * trie_search --
 *   Search for the item with the 'key'.
 */
Item trie_search(T trie, Key key)
{
    return search(trie->root, key, 0);
}


static Item search(Link h, Key key, int w)
{
    if (null(h))
        return NULLitem;
    if (null(h->left) && null(h->right))
        return EQ(key, KEY(h->item)) ? h->item : NULLitem;
    if (DIGIT(key, w) == 0)
        return search(h->left, key, w+1);
    else
        return search(h->right, key, w+1);
}

static Link new(Item item, Link l, Link r)
{
    Link x = malloc(sizeof(*x));
    assert(x != NULL);
    x->item = item;
    x->left = l;
    x->right = r;
    return x;
}


/*
 * trie_insert --
 *   Insert a item into a trie.
 */
void trie_insert(T trie, Item item)
{
    assert(trie != NULL);
    trie->root = insert(trie->root, item, 0);
}


static Link insert(Link t, Item item, int w)
{
    if (null(t))
        return new(item, NULL, NULL);
    if (null(t->left) && null(t->right)) {
        if (EQ(KEY(item), KEY(t->item)))
            return  t;
        else
            return split(new(item, NULL, NULL), t, w);
    }
    if (DIGIT(item, w) == 0)
        t->left = insert(t->left, item, w+1);
    else
        t->right = insert(t->right, item, w+1);
    return t;
}

static Link split(Link p, Link q, int w)
{
    Link t = new(NULLitem, NULL, NULL);
    switch (DIGIT(p->item, w)*2 + DIGIT(q->item, w)) {
    case 0:
        t->left = split(p, q, w+1);
        break;
    case 1:
        t->left = p;
        t->right = q;
        break;
    case 2:
        t->right = p;
        t->left = q;
        break;
    case 3:
        t->right = split(p, q, w+1);
        break;
    default:
        assert(0);
    }
    return t;
}


void trie_free(T* trie)
{
    if (trie == NULL || *trie == NULL)
        return;
    make_empty((*trie)->root);
    free(*trie);
    *trie = NULL;
}


static void make_empty(Link l)
{
    if (l != NULL)
        free(l);
    else {
        make_empty(l->left);
        make_empty(l->right);
        free(l);
    }
}


/**********************************
 *  Draw an ascii trie.
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
    if (node == NULL)
        return NULL;

    info_node *r = malloc(sizeof *r);
    if (node == NULL)
        r->p = NULL;
    r->left = build_node_info(node->left);
    r->right = build_node_info(node->right);
    if (r->left != NULL)
        r->left->p = r;
    if (r->right != NULL)
        r->right->p = r;
    sprintf(r->info, "(%d)", node->item);
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
        r->col = 50*j/n + 4;
        colno(r->right, n);
    }
}

void trie_draw(const T trie)
{
    info_node *root = build_node_info(trie->root);
    if (root == NULL)
        return;
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
