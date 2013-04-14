/*
 * Red-black tree
 *   The algorithm here is from Chapter 13, "Introduction to
 *   Algorithms" (abbreviated as CLRS), Second Edition.  The "size"
 *   field of each node is added to facilitate the select operation
 *   (see chapter 14 of CLRS).  The "bh" field in the tree is added to
 *   facilitate the join operation (see problem 13-2 of CLRS).
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../inc/rbtree.h"

#define T RBtree

typedef struct node {
    struct node *left, *right, *parent;
    enum { RED, BLACK } color;
    int size;                   // # of (internal) nodes in the subtree rooted at this node (including)
    Item item;
} Node;

struct T {
    Node *root;
    int bh;                     // black height of this tree
};

Node nil = { NULL, NULL, NULL, BLACK, 0, 0 };

#define NIL(T)  ((void *) &nil)
#define null(t) ((t) == NIL(t))

static void make_empty(T tree, Node * node);
static void insert_fixup(T tree, Node * z);
static void delete_fixup(T tree, Node * x);
static void inorder_walk(T tree, const Node * node, void (*fun) (Item));
static Node *search(const T tree, Key key);
static Node *successor(const T tree, Node * t);
static Node *predecessor(const T tree, Node * t);
static Node *minimum(const T tree, const Node * node);
static Node *maximum(const T tree, const Node * node);
static Node *left_rotate(T tree, Node * x);
static Node *right_rotate(T tree, Node * y);
static void display(const T tree, const Node * node, int depth);


/*
 * tree_new --
 *   Create a new binary search tree.
 */
T tree_new(void)
{
    T tree = (T) malloc(sizeof *tree);

    if (tree == NULL)
        return NULL;
    tree->root = NIL(tree);
    tree->bh = 0;
    return tree;
}


/*
 * tree_free --
 *   Free all the nodes of the tree.
 */
void tree_free(T * tree)
{
    assert(tree);

    if (*tree == NULL)
        return;
    make_empty(*tree, (*tree)->root);
    free(*tree);
    *tree = NULL;
}


/*
 * tree_search --
 *   Search for the item whose key is equal to 'k'.
 */
Item tree_search(const T tree, Key k)
{
    assert(tree);

    Node *node = tree->root;

    while (node != NIL(tree) && !EQ(k, KEY(node->item)))
        if (LESS(k, KEY(node->item)))
            node = node->left;
        else
            node = node->right;
    if (node != NIL(tree))
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

    Node *node = minimum(tree, tree->root);

    if (node != NIL(tree))
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

    Node *node = maximum(tree, tree->root);

    if (node != NIL(tree))
        return node->item;
    return NULLitem;
}


/*
 * tree_select --
 *   Return the item with the ith key.
 */
Item tree_select(const T tree, int i)
{
    assert(tree);
    assert(i >= 0 && i < tree->root->size);

    Node *x = tree->root;

    while (1) {
        int r = x->left->size;

        if (i == r) {
            return x->item;
        } else if (i < r) {
            x = x->left;
        } else {
            x = x->right;
            i -= r + 1;
        }
    }

    /* should not reach here */
    assert(0);
}


int tree_size(const T tree)
{
    assert(tree);

    return tree->root->size;
}


void tree_walk(const T tree, void (*fun) (Item))
{
    assert(tree != NULL);
    assert(fun != NULL);

    inorder_walk(tree, tree->root, fun);
}


void tree_show(const T tree)
{
    assert(tree);

    display(tree, tree->root, 1);
}


/*
 * tree_insert --
 *   Insert the item into the tree.
 *   See section 13.3, "Introduction to Algorithms", 2/e for details
 *   on the algorithm.
 */
void tree_insert(const T tree, Item item)
{
    assert(tree);

    Node *x, *y, *z;

    /*
     * z is the inserted node
     */
    z = malloc(sizeof *z);
    assert(z);
    z->item = item;

    /*
     * Traverse the tree from the root down to find a place for the
     * new node.
     */
    y = NIL(tree);
    x = tree->root;
    while (x != NIL(tree)) {
        x->size++;              // maintain the size field of each node
        y = x;
        if (LESS(KEY(item), KEY(x->item)))
            x = x->left;
        else
            x = x->right;
    }

    /*
     * now y is the parent of new inserted node z
     */
    z->parent = y;
    if (y == NIL(tree))
        tree->root = z;
    else if (LESS(KEY(z->item), KEY(y->item)))
        y->left = z;
    else
        y->right = z;
    z->left = z->right = NIL(tree);
    z->color = RED;
    z->size = 1;
    insert_fixup(tree, z);
}


/*
 * tree_delete --
 *   Delete the item whose key is equal to 'key' from the tree.
 *   See section 13.4, "Introduction to Algorithms", 2/e for the
 *   algorithm.
 */
void tree_delete(T tree, Key key)
{
    assert(tree);

    Node *x, *y, *z;

    /*
     * find the to-be-deleted node z
     */
    z = search(tree, key);
    if (z == NIL(tree))
        return;

    /*
     * y is the spliced out node
     */
    if ((z->left == NIL(tree)) || (z->right == NIL(tree)))
        y = z;
    else
        y = successor(tree, z);

    /* 
     * Maintain the size field of each node on the path from y to the
     * root.
     */
    Node *p = y->parent;

    while (p != NIL(tree)) {
        p->size--;
        p = p->parent;
    }

    /*
     * link y's only child to y's parent
     */
    if (y->left != NIL(tree))
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == NIL(tree)) // we are deleting the root
        tree->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    /* if y is not z copy satellite data */
    if (y != z)
        z->item = y->item;

    /* maintain red-black property if necessary */
    if (y->color == BLACK)
        delete_fixup(tree, x);

    free(y);
}


/*
 * tree_join --
 *   Return a new tree with items from tree1, item and tree2 assuming
 *   that 
 *   key[any item in tree1] <= key[item] <= key[any item in tree2].
 */
T tree_join(T tree1, Item item, T tree2)
{
    assert(tree1 != NULL && tree2 != NULL);

    Node *y;
    int cur_bh;

    if (tree1->bh >= tree2->bh) {

        /*
         * Find a black node y in tree1 with the largest key and whose
         * black-height is tree2->bh.
         */
        cur_bh = tree1->bh;
        y = tree1->root;
        while (y != NIL(tree1)) {
            if (cur_bh == tree2->bh && y->color == BLACK)
                break;
            y->size += tree2->root->size;
            y = y->right;
            if (y->color == BLACK)
                cur_bh--;
        }

        /*
         * Create a new node x to replace y.  y becomes the left
         * child of x and tree2 becomes the right child of x.
         */
        Node *x = malloc(sizeof(*x));

        assert(x);
        x->color = RED;
        x->item = item;
        x->size = y->size + tree2->root->size + 1;
        x->left = y;
        x->right = tree2->root;
        y->parent->right = x;
        x->parent = y->parent;
        if (y->parent == NIL(tree1)) {
            tree1->root = x;
            x->color = BLACK;
            tree1->bh++;
        }
        y->parent = x;
        tree2->root->parent = x;
        free(tree2);
        insert_fixup(tree1, x);

        return tree1;
    } else {

        /*
         * Find a black node y in tree2 with the smallest key and whose
         * black-height is tree1->bh.
         */
        cur_bh = tree2->bh;
        y = tree2->root;
        while (y != NIL(tree2)) {
            if (cur_bh == tree1->bh && y->color == BLACK)
                break;
            y->size += tree1->root->size;
            y = y->left;
            if (y->color == BLACK)
                cur_bh--;
        }

        /*
         * Create a new node x to replace y.  y becomes the right;
         * child of x and tree1 becomes the left child of x.
         */
        Node *x = malloc(sizeof(*x));

        assert(x);
        x->color = RED;
        x->item = item;
        x->size = y->size + tree1->root->size + 1;
        x->left = tree1->root;
        x->right = y;
        y->parent->left = x;
        x->parent = y->parent;
        if (y->parent == NIL(tree2)) {
            tree2->root = x;
            x->color = BLACK;
            tree2->bh++;
        }
        y->parent = x;
        tree1->root->parent = x;
        free(tree1);
        insert_fixup(tree2, x);

        return tree2;
    }
}


static void make_empty(T tree, Node * node)
{
    if (node == NIL(tree))
        return;
    make_empty(tree, node->left);
    make_empty(tree, node->right);
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
static Node *left_rotate(T tree, Node * x)
{
    assert(tree && x && x->right);

    /* turn y's left subtree to x's right subtree */
    Node *y = x->right;

    x->right = y->left;
    if (y->left != NIL(tree))
        y->left->parent = x;

    /* link x's parent to y */
    y->parent = x->parent;
    if (x->parent == NIL(tree))
        tree->root = y;
    else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    /* put x on y's left */
    y->left = x;
    x->parent = y;

    /* fix the size field of x and y */
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;

    return y;
}


/*
 * right_rotate --
 *   Do right rotation operation.
 *   The code for right rotate is symmetric to that for left rotate.
 * Precondition
 *   y != NULL and y must have a left child
 */
static Node *right_rotate(T tree, Node * y)
{
    assert(y && y->left);

    /* turn x's right subtree to y's left subtree */
    Node *x = y->left;

    y->left = x->right;
    if (x->right != NIL(tree))
        x->right->parent = y;

    /* link y's parent to x */
    x->parent = y->parent;
    if (y->parent == NIL(tree))
        tree->root = x;
    else {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }

    /* put y on x's right */
    x->right = y;
    y->parent = x;

    /* fix the size field of x and y */
    x->size = y->size;
    y->size = y->left->size + y->right->size + 1;
    return x;
}


/*
 * insert_fixup --
 *   Fixup the tree to make it satisfy the red-black property.
 *   See section 13.3, "Introduction to Algorithms", 2/e.
 */
static void insert_fixup(T tree, Node * z)
{
    assert(tree && z);

    Node *y;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(tree, z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(tree, z->parent->parent);
            }
        }
    }
    if (z == tree->root)
        tree->bh++;
    tree->root->color = BLACK;
}


static void delete_fixup(T tree, Node * x)
{
    assert(tree && x);

    Node *w;

    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    /*
     * Maintain the bh field of the tree.
     * See problem 13-2(a) of "Introduction to Algorithms", 2/e.
     */
    if (x == tree->root)
        tree->bh--;

    x->color = BLACK;
}


static void inorder_walk(T tree, const Node * node, void (*fun) (Item))
{
    if (node != NIL(tree)) {
        inorder_walk(tree, node->left, fun);
        if (fun != NULL)
            fun(node->item);
        inorder_walk(tree, node->right, fun);
    }
}

static Node *search(const T tree, Key key)
{
    assert(tree);

    Node *node = tree->root;

    while (node != NIL(tree) && !EQ(key, KEY(node->item)))
        if (LESS(key, KEY(node->item)))
            node = node->left;
        else
            node = node->right;
    return node;
}


static Node *successor(const T tree, Node * t)
{
    assert(t);

    if (t->right != NIL(tree))
        return minimum(tree, t->right);
    Node *p = t->parent;

    while (p != NIL(tree) && t == p->right)
        t = p, p = p->parent;
    return p;
}


static Node *predecessor(const T tree, Node * t)
{
    assert(t);

    if (t->left != NIL(tree))
        return maximum(tree, t->left);
    Node *p = t->parent;

    while (p != NIL(tree) && t == p->left)
        t = p, p = p->parent;
    return p;
}


static Node *minimum(const T tree, const Node * node)
{
    assert(tree && node);

    if (node == NIL(tree))
        return (Node *) node;
    while (node->left != NIL(tree))
        node = node->left;
    return (Node *) node;
}


static Node *maximum(const T tree, const Node * node)
{
    assert(tree && node);

    if (node == NIL(tree))
        return (Node *) node;
    while (node->right != NIL(tree))
        node = node->right;
    return (Node *) node;
}


static void display(const T tree, const Node * node, int depth)
{
    if (node != NIL(tree)) {
        printf("%*s%d(%c)\n", depth, " ", node->item,
               node->color == RED ? 'R' : 'B');
        display(tree, node->left, depth + 3);
        display(tree, node->right, depth + 3);
    } else
        printf("%*s%s\n", depth, " ", "nil");
}


/* Draws ascii picture of a tree.  Allows the user to splay */
/* any node, and then redraws the tree.                     */
/* written by Daniel Sleator <sleator@cs.cmu.edu>           */
/* The following program is in the public domain.           */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#define INFINITY (1<<20)
#define LABLEN 20

int min(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int max(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

typedef struct pnode_struct Pnode;

struct pnode_struct {
    Pnode *left, *right;
    /* 
     * length of the edge from this node to its children number of "\"
     * or "/".  so it's at least 1 unless both children are null.
     * Then it's 0.
     */
    int edge_length;            
    int height;                 /* The number of rows required to print this tree */
    int lablen;
    int parent_dir;     /* -1=I am left, 0=I am root, 1=right
                           this is used to decide how to break ties 
                           when the label is of even length         */
    char label[LABLEN + 1];
};

int allocs_in_use;
void my_free(void *p)
{
    allocs_in_use--;
    free(p);
}

void *my_alloc(int size)
{
    void *p = malloc((size_t) size);

    allocs_in_use++;
    if (p == NULL) {
        fprintf(stderr, "Ran out of space.  Requested size=%d.\n", size);
        exit(1);
    }
    return p;
}

/* Free all the nodes of the given tree */
void free_ptree(Pnode * pn)
{
    if (pn == NULL)
        return;
    free_ptree(pn->left);
    free_ptree(pn->right);
    my_free(pn);
}

Pnode *build_ptree_rec(Node * t)
{
    Pnode *pn;

    if (null(t))
        return NULL;
    pn = my_alloc(sizeof(Pnode));
    pn->left = build_ptree_rec(t->left);
    pn->right = build_ptree_rec(t->right);
    if (pn->left != NULL)
        pn->left->parent_dir = -1;
    if (pn->right != NULL)
        pn->right->parent_dir = 1;

    sprintf(pn->label, "%d(%c)", KEY(t->item),
            t->color == RED ? 'R' : 'B');
    pn->lablen = strlen(pn->label);
    return pn;
}

/*
 * Copy the tree from the original structure into the Pnode structure
 * fill in the parent_dir, label, and labelen fields, but not the    
 * edge_length or height fields.                                     
 */
Pnode *build_ptree(Node * t)
{
    Pnode *pn;

    if (null(t))
        return NULL;
    pn = build_ptree_rec(t);
    pn->parent_dir = 0;
    return pn;
}

/* 
 * The lprofile array is description of the left profile of a tree.
 * Assuming the root is located at (0,0), lprofile[i] is the leftmost
 * point used on row i of the tree.  rprofile is similarly defined.
 */
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];

/*
 * The following function fills in the lprofile array for the given tree.
 * It assumes that the center of the label of the root of this tree
 * is located at a position (x,y).  It assumes that the edge_length
 * fields have been computed for this tree.
 */
void compute_lprofile(Pnode * pn, int x, int y)
{
    int i, isleft;

    if (pn == NULL)
        return;
    isleft = (pn->parent_dir == -1);
    lprofile[y] = min(lprofile[y], x - ((pn->lablen - isleft) / 2));
    if (pn->left != NULL) {
        for (i = 1; i <= pn->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = min(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(pn->left, x - pn->edge_length - 1,
                     y + pn->edge_length + 1);
    compute_lprofile(pn->right, x + pn->edge_length + 1,
                     y + pn->edge_length + 1);
}

void compute_rprofile(Pnode * pn, int x, int y)
{
    int i, notleft;

    if (pn == NULL)
        return;
    notleft = (pn->parent_dir != -1);
    rprofile[y] = max(rprofile[y], x + ((pn->lablen - notleft) / 2));
    if (pn->right != NULL) {
        for (i = 1; i <= pn->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = max(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(pn->left, x - pn->edge_length - 1,
                     y + pn->edge_length + 1);
    compute_rprofile(pn->right, x + pn->edge_length + 1,
                     y + pn->edge_length + 1);
}

/* 
 * This function fills in the edge_length and height fields of the
 * specified tree.
 */
void compute_edge_lengths(Pnode * pn)
{
    int h, hmin, i, delta;

    if (pn == NULL)
        return;
    compute_edge_lengths(pn->left);
    compute_edge_lengths(pn->right);

    /* first fill in the edge_length of pn */
    if (pn->right == NULL && pn->left == NULL) {
        pn->edge_length = 0;
    } else {
        if (pn->left != NULL) {
            for (i = 0; i < pn->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(pn->left, 0, 0);
            hmin = pn->left->height;
        } else {
            hmin = 0;
        }
        if (pn->right != NULL) {
            for (i = 0; i < pn->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(pn->right, 0, 0);
            hmin = min(pn->right->height, hmin);
        } else {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = max(delta, 2 + 1 + rprofile[i] - lprofile[i]);
            /* the "2" guarantees a gap of 2 between different parts of the tree */
        }
        /* If the node has two children of height 1, then we allow the
           two leaves to be within 1, instead of 2 */
        if (((pn->left != NULL && pn->left->height == 1) ||
             (pn->right != NULL && pn->right->height == 1)) && delta > 4)
            delta--;
        pn->edge_length = ((delta + 1) / 2) - 1;
    }

    /* now fill in the height of pn */
    h = 1;
    if (pn->left != NULL) {
        h = max(pn->left->height + pn->edge_length + 1, h);
    }
    if (pn->right != NULL) {
        h = max(pn->right->height + pn->edge_length + 1, h);
    }
    pn->height = h;
}

int print_next;                 /* used by print_level.  If you call "printf()" at   */

                 /* any point, this is the x coordinate of the next   */
                 /* char printed.                                     */

/*
 * This function prints the given level of the given tree, assuming
 * that the node pn has the given x cordinate.
 */
void print_level(Pnode * pn, int x, int level)
{
    int i, isleft;

    if (pn == NULL)
        return;
    isleft = (pn->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((pn->lablen - isleft) / 2));
             i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", pn->label);
        print_next += pn->lablen;
    } else if (pn->edge_length >= level) {
        if (pn->left != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (pn->right != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(pn->left, x - pn->edge_length - 1,
                    level - pn->edge_length - 1);
        print_level(pn->right, x + pn->edge_length + 1,
                    level - pn->edge_length - 1);
    }
}

/* 
 * This pretty-prints the given tree, left-justified.
 * The tree is drawn in such a way that both of the edges down from
 * a node are the same length.  This length is the minimum such that
 * the two subtrees are separated by at least two blanks.
 */
void tree_draw(const T t)
{
    Pnode *proot;
    int xmin, i;

    if (t == NULL)
        return;
    proot = build_ptree(t->root);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = min(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n",
             MAX_HEIGHT);
    }
    free_ptree(proot);
}
