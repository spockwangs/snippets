#ifndef __BIT_H
#define __BIT_H

#define T Bit_T
typedef struct T *T;

T Bit_new(int length);
void Bit_free(T *set);
int Bit_length(T set);
int Bit_get(T set, int n);
int Bit_put(T set, int n, int bit);

#endif
