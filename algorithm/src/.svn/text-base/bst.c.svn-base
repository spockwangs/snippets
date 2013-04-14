/*
 * Binary Search Tree
 *
 * Author: wbb
 * Date: 2010-03-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/bst.h"

#define T BSTree

typedef struct node {
    struct node *left, *right, *parent;
    Item item;
} BinaryNode;

struct T {
    BinaryNode *root;
};


static void inorder_walk(const BinaryNode *node, void (*fun)(Item));
static BinaryNode *search(const T tree, Key key);
static BinaryNode *successor(BinaryNode *t);
static BinaryNode *predecessor(BinaryNode *t);
static BinaryNode *minimum(const BinaryNode *node);
static BinaryNode *maximum(const BinaryNode *node);
static void make_empty(BinaryNode *node);
static BinaryNode *left_rotate(BinaryNode *x);
static BinaryNode *right_rotate(BinaryNode *y);
static void display(const BinaryNode *node, int depth);


/*
 * tree_new --
 *   Create a new binary search tree.
 */
T tree_new(void)
{
    T tree = (T) malloc(sizeof *tree);
    if (tree == NULL)
        return NULL;
    tree->root = NULL;
    return tree;
}


/*
 * tree_free --
 *   Free all the nodes of the tree.
 */
void tree_free(T *tree)
{
    assert(tree);

    if (*tree == NULL)
        return;
    make_empty((*tree)->root);
    free(*tree);
    *tree = NULL;
}


/*
 * tree_walk --
 *   Inorder traverse the tree and apply the fun to the item of each
 *   node.
 */
void tree_walk(const T tree, void (*fun)(Key))
{
    assert(tree);

    inorder_walk(tree->root, fun);
}


void tree_show(const T tree)
{
    assert(tree);

    display(tree->root, 1);
}


/*
 * tree_search --
 *   Search for the item whose key is equal to 'k'.
 */
Item tree_search(const T tree, Key k)
{
    assert(tree);

    BinaryNode *node = tree->root;
    while (node != NULL && !EQ(k, KEY(node->item)))
        if (LESS(k, KEY(node->item)))
            node = node->left;
        else
            node = node->right;
    if (node)
        return node->item;
    else
        return NULLitem;
}

/*
 * tree_min --
 *   Return the item with the smallest key.
 */
Item tree_min(const T tree)
{
    assert(tree);

    BinaryNode *node = minimum(tree->root);
    if (node)
        return node->item;
    return NULLitem;
}

/*
 * tree_max --
 *   Return the item with the maximum key.
 */
Item tree_max(const T tree)
{
    assert(tree);

    BinaryNode *node = maximum(tree->root);
    if (node)
        return node->item;
    return NULLitem;
}


/*
 * tree_insert --
 *   Insert the item into the key.
 *   See section 12.3, "Introduction to Algorithms", 2/e for details
 *   on the algorithm.
 */
void tree_insert(const T tree, Item item)
{
    assert(tree);

    BinaryNode *p, *q;

    p = NULL;
    q = tree->root;
    while (q) {
        p = q;
        if (LESS(KEY(item), KEY(q->item)))
            q = q->left;
        else
            q = q->right;
    }

    BinaryNode *new_node = (BinaryNode *) malloc(sizeof(*new_node));
    assert(new_node);
    new_node->left = new_node->right = NULL;
    new_node->item = item;
    new_node->parent = p;
    if (p == NULL)
        tree->root = new_node;
    else if (LESS(KEY(item), KEY(p->item)))
        p->left = new_node;
    else
        p->right = new_node;
}

/*
 * tree_delete --
 *   Delete the item whose key is equal to 'key' from the tree.  See
 *   section 12.3 of "Introduction to ALgorithms", 2/e for details on
 *   the algorithm.
 */
void tree_delete(const T tree, Key key)
{

    BinaryNode *node, *q, *x;
    
    node = search(tree, key);
    if (node == NULL)
        return;

    if (node->left == NULL || node->right == NULL)
        q = node;
    else
        q = successor(node);
    if (q->left != NULL)
        x = q->left;
    else
        x = q->right;
    if (x)
        x->parent = q->parent;
    if (q->parent == NULL)
        tree->root = x;
    else if (q == q->parent->left)
        q->parent->left = x;
    else
        q->parent->right = x;
    if (q != node)
        node->item = q->item;
    free(q);
}


static void inorder_walk(const BinaryNode *node, void (*fun)(Item))
{
    if (node != NULL) {
        inorder_walk(node->left, fun);
        if (fun)
            fun(node->item);
        inorder_walk(node->right, fun);
    }
}

static BinaryNode *search(const T tree, Key key)
{
    assert(tree);

    BinaryNode *node = tree->root;
    while (node != NULL && !EQ(key, KEY(node->item)))
        if (LESS(key, KEY(node->item)))
            node = node->left;
        else
            node = node->right;
    return node;
}


static BinaryNode *successor(BinaryNode *t)
{
    assert(t);

    if (t->right)
        return minimum(t->right);
    BinaryNode *p = t->parent;
    while (p && t == p->right)
        t = p, p = p->parent;
    return p;
}


static BinaryNode *predecessor(BinaryNode *t)
{
    assert(t);

    if (t->left)
        return maximum(t->left);
    BinaryNode *p = t->parent;
    while (p && t == p->left)
        t = p, p = p->parent;
    return p;
}


static BinaryNode *minimum(const BinaryNode *node)
{
    if (node == NULL)
        return NULL;
    while (node->left)
        node = node->left;
    return (BinaryNode *) node;
}


static BinaryNode *maximum(const BinaryNode *node)
{
    if (node == NULL)
        return NULL;
    while (node->right)
        node = node->right;
    return (BinaryNode *) node;
}


static void make_empty(BinaryNode *node)
{
    if (node == NULL)
        return;
    make_empty(node->left);
    make_empty(node->right);
    free(node);
}

/*
 * left_rotate --
 *   Do left rotation operation.
 *   See page 278, "Introduction to Algorithms", 2/e for the
 *   algorithm.
 * Precondition
 *   x ! = NULL and x must have a right child
 */
static BinaryNode *left_rotate(BinaryNode *x)
{
    assert(x && x->right);

    /* turn y's left subtree to x's right subtree */
    BinaryNode *y = x->right;
    x->right = y->left;
    y->left->parent = x;

    /* link x's parent to y */
    y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    /* put x on y's left */
    y->left = x;
    x->parent = y;
    return y;
}


/*
 * right_rotate --
 *   Do right rotation operation.
 *   The code for right rotate is symmetric to that for left rotate.
 * Precondition
 *   y != NULL and y must have a left child
 */
static BinaryNode *right_rotate(BinaryNode *y)
{
    assert(y && y->left);

    /* turn x's right subtree to y's left subtree */
    BinaryNode *x = y->left;
    y->left = x->right;
    x->right->parent = y;

    /* link y's parent to x */
    x->parent = y->parent;
    if (y->parent) {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }

    /* put y on x's right */
    x->right = y;
    y->parent = x;

    return x;
}


static void display(const BinaryNode *node, int depth)
{
    if (node) {
        printf("%*s%d\n", depth, " ", node->item);
        display(node->left, depth+3);
        display(node->right, depth+3);
    } else
        printf("%*s%s\n", depth, " ", "nil");
}


/**********************************
 *  Draw an ascii tree.
 **********************************/

#include <string.h>

typedef struct info {
    struct info *left, *right, *p;
    int col;
    int sz;
    char info[10];
} info_node;

static info_node *build_node_info(const BinaryNode *node)
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
    sprintf(r->info, "%d", node->item);
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
        r->col = 20*j/n + 4;
        colno(r->right, n);
    }
}

void tree_draw(const T tree)
{
    info_node *root = build_node_info(tree->root);
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
