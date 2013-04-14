#ifndef __PAT_H
#define __PAT_H

#define T PAT
typedef struct T *T;

#include "item.h"

T pat_new(void);
void pat_insert(T t, Item item);
Item pat_search(T t, Key key);
void pat_free(T* t);
void pat_draw(T t);

#undef T
#endif
