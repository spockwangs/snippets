/******************************************************************************
 * K&R Exercise 4-14
 *      Define a macro swap(t, x, y) that interchanges two arguments of type t.
 *
 * Author: wbb
 * Date: 2009-08-12
 */


#include <stdio.h>

#define swap(t, x, y) \
   do { t tmp##x##y; tmp##x##y = x, x = y, y = tmp##x##y; } while (0)


int main(void)
{

    int ix, iy;
    double dx, dy;
    char cx, cy;

    ix = 10, iy = 20;
    printf("before swap: ix = %d, iy = %d\n", ix, iy);
    swap(int, ix, iy);
    printf("after swap: ix = %d, iy = %d\n", ix, iy);

    dx = .2, dy = .4;
    printf("before swap: dx = %f, dy = %f\n", dx, dy);
    swap(double, dx, dy);
    printf("after swap: dx = %f, dy = %f\n", dx, dy);

    cx = 'a', cy = 'z';
    printf("before swap: cx = %c, dy = %c\n", cx, cy);
    swap(char, cx, cy);
    printf("after swap: cx = %c, cy = %c\n", cx, cy);

    return 0;
}
