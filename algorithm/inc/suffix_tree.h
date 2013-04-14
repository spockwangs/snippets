#ifndef __SUFFIX_TREE_H
#define __SUFFIX_TREE_H

#define T ST
typedef struct T *T;

T st_new(const char *str);
void st_substr(T st, const char *str);
void st_free(T *t);
void st_draw(T st);
void st_ms(T st, const char *str, int ms[]);
void self_test(T st);

#undef T
#endif
