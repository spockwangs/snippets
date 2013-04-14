/*
 * rbtree.h
 *
 * Red-black tree
 */

#ifndef __RBTREE_H
#define __RBTREE_H

#include "item.h"

#define T RBtree
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
Item tree_select(const T tree, int i);
T tree_join(T tree1, Item item, T tree2);
int tree_size(const T tree);
void tree_draw(const T tree);

#undef T

#endif /* ! __BST_H */
