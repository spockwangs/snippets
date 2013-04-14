#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include "item.h"

#define T SkipList
typedef struct T *T;

T SkipList_new(void);
void SkipList_free(T *skiplist);
Item SkipList_search(T skiplist, Key key);
void SkipList_insert(T skiplist, Item item);
void SkipList_delete(T skiplist, Key key);
void SkipList_show(const T skiplist);
T SkipList_join(T list1, T list2);
void SkipList_draw(const T list);

#undef T
#endif
