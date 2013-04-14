/*
 * assert.c -- Show how to define a assert macro.
 *
 * This code utilize a new feature of C99: the predefined identifier
 * "__func__" so it can only be compiled by a C99 compiler.
 *
 * Time-stamp: <2010-07-24 13:34:55 wbb>
 *
 * gcc -W -Wall -std=c99 -pedantic assert.c
 */

#include <stdio.h>
#include <stdlib.h>

#define assert(predicate)                                               \
    ((predicate)                                                        \
     ? (void) 0                                                         \
     : ((void) fprintf(stderr, "%s:%u: %s: Assertion `%s' failed.\n",   \
                       __FILE__, __LINE__, __func__, #predicate), abort()))

int main()
{
    assert(1);

    if (assert(0), 2) {
        printf("blabla\n");
    }

    return 0;
}
