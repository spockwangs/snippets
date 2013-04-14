/*
 * bit.c
 *   Impelements a bit vector data structure.
 */

#include "bit.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

#define T Bit_T
struct T {
	int length;     /* # bits */
	unsigned char *bytes;
	unsigned long *words;
};

#define BPW (8 * sizeof(unsigned long))

/* Round up len to nearest multiple integers of BPW */
#define nwords(len) ((((len)+BPW-1) & (~(BPW-1))) / BPW)

/* Round up len to nearest multiple integers of 8 */
#define nbytes(len) ((((len)+8-1) & (~(8-1))) / 8)
#define setop(sequal, snull, tnull, op) \
	if (s == t) { assert(s); return sequal; } \
	else if (s == NULL) { assert(t); return snull; } \
	else if (t == NULL) return tnull; \
	else { \
		int i; T set; \
		assert(s->length == t->length); \
		set = Bit_new(s->length); \
		for (i = nwords(s->length); --i >= 0; ) \
			set->words[i] = s->words[i] op t->words[i]; \
		return set; \
    }

        /* global variables */

unsigned char msbmask[] = {
	0xFF, 0xFE, 0xFC, 0xF8,
	0xF0, 0xE0, 0xC0, 0x80
};
unsigned char lsbmask[] = {
	0x01, 0x03, 0x07, 0x0F,
	0x1F, 0x3F, 0x7F, 0xFF
};


T Bit_new(int length) 
{
	T set;

	assert(length >= 0);
    set = malloc(sizeof *set);
    if (set == NULL)
        return NULL;
	if (length > 0)
		set->words = calloc((long) nwords(length), (long) sizeof(unsigned long));
	else
		set->words = NULL;
	set->bytes = (unsigned char *)set->words;
	set->length = length;
	return set;
}


void Bit_free(T *set) 
{
	assert(set && *set);
	free((*set)->words);
	free(*set);
}


/* 
 * Bit_length --
 *   Return the size of the bit vector.
 */
int Bit_length(T set) 
{
	assert(set);
	return set->length;
}


/*
 * Bit_get --
 *   Access bits[n].
 */
int Bit_get(T set, int n) 
{
	assert(set);
	assert(0 <= n && n < set->length);
	return ((set->bytes[n/8]>>(n%8))&1);
}


/*
 * Bit_put --
 *   Set bits[n] to 'bit'.
 */
int Bit_put(T set, int n, int bit) 
{
	int prev;

	assert(set);
	assert(bit == 0 || bit == 1);
	assert(0 <= n && n < set->length);
	prev = ((set->bytes[n/8]>>(n%8))&1);
	if (bit == 1)
		set->bytes[n/8] |=   1<<(n%8);
	else
		set->bytes[n/8] &= ~(1<<(n%8));
	return prev;
}

