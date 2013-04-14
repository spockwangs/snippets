/*
 * Implement the bucket sort algorithm.
 *
 * Author: wbb
 * Date: 2010-03-07
 */

#include "../inc/sort.h"
#include <assert.h>
#include <stdlib.h>     // for malloc()
#include <errno.h>      // for errno
#include <error.h>      // for error()

struct node {
    struct node *next;
    double value;
};

static void list_insert(struct node **head, double value);
static void list_destroy(struct node **head);

/*
 * bucket_sort --
 *   Sort A[0..n-1] in ascending order using bucket sort algorithm
 *   assuming all elements of A is in range [0, 1).
 *   See Section 8.4 of "Introduction to Algorithms", second edition
 *   for more details on the algorithm.
 */
void bucket_sort(double A[], int n)
{
    assert(A && n > 0);

    struct node **B = (struct node **) calloc((size_t) n, sizeof(struct node *));
    if (B == NULL)
        error(1, errno, "malloc failure");

    for (int i = 0; i < n; i++)
        list_insert(&B[(int)(n*A[i])], A[i]);

    for (int j = 0, i = 0; j < n; j++) {
        struct node *p = B[j];
        while (p != NULL) {
            A[i++] = p->value;
            p = p->next;
        }
    }

    /* free alloced memory */
    for (int j = 0; j < n; j++)
        list_destroy(&B[j]);
    free(B);
}

static void list_insert(struct node **head, double value)
{
    assert(head);
    
    struct node *elem = (struct node *) malloc(sizeof(struct node));
    assert(elem);
    elem->value = value;
    elem->next = NULL;

    if (*head == NULL) {
        *head = elem;
        return;
    }

    struct node *p;
    p = *head;
    if (value <= p->value) {
        elem->next = p;
        *head = elem;
        return;
    }
    while (p->next && (value > p->next->value)) {
        p = p->next;
    }
    elem->next = p->next;
    p->next = elem;
}

static void list_destroy(struct node **head)
{
    assert(head);

    struct node *p, *q;

    q = *head;
    while (q) {
        p = q->next;
        free(q);
        q = p;
    }
}

