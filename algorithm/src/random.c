/*
 * random - Generate a uniformly distributed random integer.
 *
 * Author: wbb
 * Date 2010-03-07
 */

#include <stdlib.h>     /* for rand() */
#include <assert.h>
#include "../inc/algorithm.h"

/*
 * random --
 *   Generate a uniformly distributed random integer in [a, b].
 */
int random(int a, int b)
{
    assert(a <= b);
    return rand()%(b-a+1) + a;
}
