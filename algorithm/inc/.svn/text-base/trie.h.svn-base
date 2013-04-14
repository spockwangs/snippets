#ifndef __TRIE_H
#define __TRIE_H

#define T Trie
typedef struct T* T;

#include "item.h"


T trie_new(void);
Item trie_search(T trie, Key key);
void trie_insert(T trie, Item item);
void trie_free(T* trie);
void trie_draw(T trie);

#undef T
#endif
