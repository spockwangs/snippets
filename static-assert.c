/*
 * static-assert.c -- Show to how to implement static assertion which can
 *   assert something statically, i.e. can be checked at compile time.
 *
 */

#include <stdio.h>

/*
 * If 'x' is true then all is well. Otherwise,
 * the compiler will signal an error, i.e.
 * a static assertion.
 */
#define static_assert(x) switch (0) case 0: case(x):

int main(void)
{
    static_assert(0);

    return 0;
}

