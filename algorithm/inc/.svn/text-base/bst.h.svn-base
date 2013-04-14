/* bst.h */
/*
 * A binary search tree
 */

#ifndef __BST_H
#define __BST_H

#include "item.h"

#define T BSTree
typedef struct T *T;

T tree_new(void);
void tree_free(T *tree);
void tree_walk(const T tree, void (*fun)(Item));
Item tree_search(const T tree, Key key);
Item tree_min(const T tree);
Item tree_max(const T tree);
void tree_insert(const T tree, Item item);
void tree_delete(const T tree, Key key);
void tree_show(const T tree);
void tree_draw(const T tree);

#undef T

#endif /* ! __BST_H */
