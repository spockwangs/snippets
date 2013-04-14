/*
 * Suffix tree
 *   Use Ukkonen's algorithm to construct a suffix tree.
 *   * The node in this tree is stored using left-child,
 *     right-sibling representation.
 *   * The suffix link is by default the root of this tree.
 *   * Each edge is represented in its ending node.
 * 
 * Bug
 *   There is some bug lurking in this code.
 */

#include "../inc/suffix_tree.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <err.h>

#define T ST

typedef struct node *Link;
struct node {
    Link child, prev_sibling, next_sibling, p;
    Link suffix_link;   // by default the suffix link is the root
    int i, j;   // indices of incoming edge
    int index;  // index of beginning of the suffix represented by this node
};

struct T {
    char *text; // the string from which the suffix is constructed
    Link root;
    int e;      // virtual end of all leaves; to simplify the extension rule 1
};

typedef struct pos {
    int edge_idx;
    Link node;
} POS;


        /* function protypes */

static int do_phase(T st, int phase, int j, POS *pos);
static Link do_rule2(T st, POS *pos, int idx);
static Link find_char_child(T st, Link x, int idx);
static int edge_len(T st, Link x);
static int is_last_char(T st, Link node, int idx);
static void make_empty(Link x);
static void print_node(T st, Link x, int depth);
static int edge_end(T st, Link x);
static POS trace_edge(T st, Link r, int i, int j, int skip);
static POS follow_suffix_link(T st, POS pos);
static Link find_char_in_child(T st, Link x, int c);
static void print_node_index(Link x);

/*
 * st_new --
 *   Create a new suffix tree.
 */
T st_new(const char *str)
{
    T st = malloc(sizeof *st);
    assert(st != NULL);

    st->text = malloc(strlen(str)+2);   // +2 for '$' + '\0'
    assert(st->text != NULL);
    strcpy(st->text, str);
    strcat(st->text, "$");
    st->e = -1;
    st->root = malloc(sizeof *(st->root));
    assert(st->root != NULL);

    // Initialize the root.
    st->root->child = st->root->prev_sibling = st->root->next_sibling = st->root->p = NULL;
    st->root->suffix_link = st->root;
    st->root->i = 0;
    st->root->j = -1;
    st->root->index = -1;

    POS pos = { .node = st->root, .edge_idx = -1 };
    int len = strlen(st->text);
    for (int i = 0, j = 0; i < len; i++) {
        j = do_phase(st, i, j, &pos);
    }
    return st;
}


/*
 * st_free --
 *   Destroy the suffix tree and free all its memory.
 */
void st_free(T *st)
{
    assert(st != NULL);

    make_empty((*st)->root);
    free((*st)->text);
    free(*st);
    *st = NULL;
}


/*
 * do_phase --
 *   Do a phase according to Ukkonen's algorithm.  'phase' is the
 *   phase number.  The first phase is phase 0.  'pos' is the position
 *   of last extension of last phase and is where we start from this
 *   phase.
 */
static int do_phase(T st, int phase, int j, POS *pos)
{
    /* indicate if last extension belongs to rule 3 */
    static int after_rule3;
    static Link oldr;

    // do extension rule 1
    st->e = phase;

    if (phase == 0) {
        after_rule3 = 0;
        oldr = st->root;
    }

    /* 
     * Do extension rule 2 and rule 3.
     */
    while (j <= phase) {
        // If not after extension rule 3 follow the suffix link.
        if (after_rule3 == 0) {
            *pos = follow_suffix_link(st, *pos);
        }

        Link x;
        if (is_last_char(st, pos->node, pos->edge_idx)) {
            if ((x = find_char_child(st, pos->node, phase)) != NULL) {
                // ==> extension rule 3
                pos->node = x;
                pos->edge_idx = 0;
                after_rule3 = 1;
                break;
            }
        } else if (st->text[pos->node->i+pos->edge_idx+1] == st->text[phase]) {
            // ==> extension rule 3
            pos->edge_idx++;
            after_rule3 = 1;
            break;
        }

        // ==> do extension rule 2
        x = do_rule2(st, pos, phase);
        x->index = j;
        if (oldr != st->root)
            oldr->suffix_link = x;
        oldr = x;

        after_rule3 = 0;
        j++;
    }
    return j;
}


/*
 * do_rule2 --
 *   Do extension according to rule 2.
 *   If 'pos.edge_idx' is in the range [0, len-1), where 'len' is the
 *   length of the incoming edge of 'pos.node' split the edge (case 1), 
 *   else create a new child of 'pos.node' (case 2).
 *
 */
static Link do_rule2(T st, POS *pos, int idx)
{
    int len = edge_len(st, pos->node);

    if (pos->edge_idx >= 0 && pos->edge_idx < len-1) {
        /*
         *   Case 1:
         *        p                 p
         *        |                 |
         *        |                 x <-- pos
         *       node     ==>      / \
         *      /               node   y
         */
        Link x, y;
        x = malloc(sizeof *x);

        // Make 'x' the parent of 'pos->node'.
        x->child = pos->node;
        x->next_sibling = pos->node->next_sibling;
        x->prev_sibling = pos->node->prev_sibling;
        if (pos->node->next_sibling != NULL)
            pos->node->next_sibling->prev_sibling = x;
        if (pos->node->prev_sibling != NULL)
            pos->node->prev_sibling->next_sibling = x;

        x->p = pos->node->p;
        x->suffix_link = st->root;
        x->i = pos->node->i;
        x->j = pos->edge_idx + pos->node->i;
        x->index = pos->node->index;
        if (pos->node->p->child == pos->node)
            pos->node->p->child = x;
        pos->node->p = x;
        pos->node->prev_sibling = NULL;
        pos->node->next_sibling = NULL;
        pos->node->i += pos->edge_idx+1;

        y = malloc(sizeof *y);
        assert(y != NULL);
        y->child = NULL;
        y->p = x;
        y->prev_sibling = pos->node;
        y->next_sibling = NULL;
        y->i = y->j = idx;
        y->suffix_link = st->root;

        pos->node->next_sibling = y;
        pos->node = x;
        pos->edge_idx = x->j - x->i;
        return y;
    } else {
        /* Case 2:
         *        |                 |
         *       node     ==>     node  
         *       /                 / \
         *                            y
         */
        Link y = malloc(sizeof *y);
        assert(y != NULL);
        y->p = pos->node;
        y->prev_sibling = NULL;
        y->next_sibling = pos->node->child;
        if (pos->node->child != NULL)
            pos->node->child->prev_sibling = y;
        pos->node->child = y;
        y->suffix_link = st->root;
        y->child = NULL;
        y->i = y->j = idx;
        return y;
    }
}


static int edge_len(T st, Link x)
{
    if (x->child == NULL)
        return st->e - x->i + 1;
    else
        return x->j - x->i + 1;
}

static int edge_end(T st, Link x)
{
    if (x->child == NULL)
        return st->e;
    else
        return x->j;
}


/*
 * find_char_child --
 *   Search for 'c' in one of child nodes of 'x' where 'c' =
 *   text[idx].  Return the matched node, or NULL.
 */
static Link find_char_child(T st, Link x, int idx)
{
    assert(x != NULL);

    for (Link y = x->child; y != NULL; y = y->next_sibling)
        if (st->text[idx] == st->text[y->i])
            return y;
    return NULL;
}


/*
 * is_last_char --
 *   Check if 'idx' is the index of last char of incoming edge of
 *   'node'.
 */
static int is_last_char(T st, Link node, int idx)
{
    if (node == st->root)
        return 1;
    else
        return (idx == edge_len(st, node)-1);
}


void st_draw(T st)
{
    printf("root\n");
    print_node(st, st->root, 0);
}


static void print_node(T st, Link x, int depth)
{

    if (depth > 0) {
        int d = depth;
        while (d > 1) {
            printf("|");
            d--;
        }
        printf("+");

        for (int i = x->i; i <= edge_end(st, x); i++)
            printf("%c", st->text[i]);
        if (x->child == NULL)
            printf("(%d)", x->index);
        printf("\n");
    }
    for (Link y = x->child; y != NULL; y = y->next_sibling) {
        print_node(st, y, depth+1);
    }
}


static void make_empty(Link x)
{
    if (x == NULL)
        return;
    Link y = x->child;
    while (y != NULL) {
        Link z = y->next_sibling;
        make_empty(y);
        y = z;
    }
    free(x);
}


/*
 * trace_edge --
 *   Trace the string 'text[i..j]' from the node 'r' in the suffix
 *   tree 'st' and return the ending position.  If the string is not
 *   found return { NULL, -1 }.  If the string is empty (i.e. i > j)
 *   return { root, -1 }.  The 'skip' indicates if using skip trick or
 *   not according to Ukkonen's algorithm.
 */
static POS trace_edge(T st, Link r, int i, int j, int skip)
{
    assert(st != NULL && r != NULL);

    POS pos;

    if (i > j) {
        pos.node = st->root;
        pos.edge_idx = -1;
        return pos;
    }

    r = find_char_child(st, r, i);
    if (r == NULL) {
        pos.node = NULL;
        pos.edge_idx = -1;
        return pos;
    }
    
    if (skip) {
        int len = edge_len(st, r);
        while (j-i+1 > len) {
            i += len;
            r = find_char_child(st, r, i);
            if (r == NULL) {
                pos.node = NULL;
                pos.edge_idx = -1;
                return pos;
            }
            len = edge_len(st, r);
        }

        pos.node = r; 
        pos.edge_idx = j-i;
        return pos;
    } else {
        while (1) {
            int k, len;
            len = edge_len(st, r);
            for (k = 0; k < len && i <= j; k++) {
                if (st->text[i++] != st->text[r->i+k]) {
                    pos.node = NULL;
                    pos.edge_idx = -1;
                    return pos;
                }
            }
            if (i > j) {
                pos.node = r;
                pos.edge_idx = k-1;
                return pos;
            }
            r = find_char_child(st, r, i);
            if (r == NULL) {
                pos.node = NULL;
                pos.edge_idx = -1;
                return pos;
            }
        }
    }

    return pos;
}


static POS follow_suffix_link(T st, POS pos)
{
    if (pos.node == st->root)
        return pos;

    if (is_last_char(st, pos.node, pos.edge_idx) &&
        (pos.node->suffix_link != st->root)) {
            pos.node = pos.node->suffix_link;
            pos.edge_idx = edge_end(st, pos.node);
            return pos;
    } else {
        Link r = pos.node->p;
        if (r == st->root) {
            pos = trace_edge(st, r, pos.node->i+1, pos.node->i+pos.edge_idx, 0);
            assert(pos.node != NULL);
            return pos;
        } else {
            r = r->suffix_link;
            pos = trace_edge(st, r, pos.node->i, pos.node->i+pos.edge_idx, 1);
            assert(pos.node != NULL);
            return pos;
        }
    }
    return pos;
}


/*
 * st_ms --
 *   Compute matching statistics of 'str' and store the results in
 *   'ms[]'.
 */
void st_ms(T st, const char *str, int ms[])
{
    assert(st != NULL && str != NULL && ms != NULL);

    POS pos;
    int i;      // index for ms[]
    int k;      // index for str[]

    pos.node = st->root;
    pos.edge_idx = -1;
    for (i = 0; (size_t) i < strlen(str); i++) {
        if (pos.node == st->root) {
            /*
             * match string str[k..] from the root and compute the
             * ending pos.
             */
            k = i;
        } else {
            /*
             * match string from last matched point and compute the
             * ending pos.
             */
            k = i + ms[i-1] - 1;
        }

        while (1) {
            Link x = pos.node;
            if (x == st->root || is_last_char(st, x, pos.edge_idx)) {
                x = find_char_in_child(st, x, str[k]);
                if (x == NULL)
                    break;
                else {
                    pos.node = x;
                    pos.edge_idx = -1;
                }
            }

            int j;
            for (j = pos.edge_idx+1; j < edge_len(st, pos.node) && str[k] != '\0'; j++, k++) {
                if (str[k] != st->text[pos.node->i+j]) {
                    break;
                }
            }
            pos.edge_idx = j-1;
            if (j < edge_len(st, pos.node)) {
                break;
            }
        }
        ms[i] = k-i;
        pos = follow_suffix_link(st, pos);
    }
}

    
static Link find_char_in_child(T st, Link x, int c)
{
    assert(x != NULL);

    for (Link y = x->child; y != NULL; y = y->next_sibling) {
        if (st->text[y->i] == c)
            return y;
    }
    return NULL;
}


/*
 * st_substr --
 *   Find each occurence of 'str' in the suffix tree 'st' and print
 *   each index.
 */
void st_substr(T st, const char *str)
{
    assert(st != NULL && str != NULL);

    Link x = st->root;
    int i = 0;
    while (1) {
        x = find_char_in_child(st, x, str[i]);
        if (x == NULL) {
            printf("No match!\n");
            return;
        }
        for (int j = 0; j < edge_len(st, x) && str[i] != '\0'; j++) {
            if (str[i++] != st->text[x->i+j]) {
                printf("No match!\n");
                return;
            }
        }
        if (str[i] == '\0')
            break;
    }
    print_node_index(x);
    printf("\n");
}


static void print_node_index(Link x)
{
    if(x == NULL)
        return;

    if (x->child == NULL)
        printf("%d, ", x->index);
    else {
        for (Link y = x->child; y != NULL; y = y->next_sibling)
            print_node_index(y);
    }
}


/*
 * self_test --
 *   Test if the constructed suffix tree is correct, i.e. if each
 *   suffix occurs in this tree.
 */
void self_test(T st)
{
    if (st == NULL) {
        warnx("self_test: this tree is empty!");
        return;
    }
    if (st->text == NULL || st->text[0] == '\0') {
        warnx("self_test: the text is empty!");
        return;
    }

    int len = strlen(st->text);
    int i;
    for (i = 0; i < len; i++) {
        POS pos = trace_edge(st, st->root, i, len-1, 0);
        if (pos.node == NULL) {
            warnx("self_test: the suffix '%s' is not found!", &(st->text[i]));
            break;
        }
        if (pos.node->index != i) {
            warnx("self_test: the index corresponding to suffix '%s' is wrong;"
                  "expect %d but it is %d", &(st->text[i]), i, pos.node->index);
            break;
        }
    }

    if (i < len) {      // something is wrong; this info may help
        printf("Text: %s\n", st->text);
        printf("Suffix tree for this string:\n");
        st_draw(st);
        printf("\n");
    }
}
