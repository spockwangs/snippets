/**************************************************************************
 * K&R Exercise 2-1
 *      Write a program to determine the ranges of char, short, int and
 *      long variables, both signed and unsigned, by printing appropriate
 *      values from standard headers and by direct computation. Harder if
 *      you compute them: determine the ranges of the various floating-
 *      point types.
 *
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

void RangesByHeader();
void RangesByComputation();

int main()
{

    printf("*-------------------Ranges by header -----------------------*\n");
    RangesByHeader();
    printf("\n\n*----------------------Ranges by computation------------------------*\n");
    RangesByComputation();

    return 0;
}

void RangesByHeader()
{
    printf("Unsigned char: MAX = %6u, MIN = %6u\n",
            UCHAR_MAX, 0);
    printf("Signed char: MAX = %6d, MIN = %6d\n",
            SCHAR_MAX, SCHAR_MIN);
    printf("char: MAX = %6d, MIN = %6d\n",
            CHAR_MAX, CHAR_MIN);
    printf("unsigned short: MAX = %6u, MIN = %6u\n",
            USHRT_MAX, 0);
    printf("short: MAX = %6d, MIN = %6d\n",
            SHRT_MAX, SHRT_MIN);
    printf("unsigned int: MAX = %6u, MIN = %6u\n",
            UINT_MAX, 0);
    printf("int: MAX = %6d, MIN = %6d\n",
            INT_MAX, INT_MIN);
    printf("unsigned long: MAX = %6lu, MIN = %6lu\n",
            ULONG_MAX, 0UL);
    printf("long: MAX = %6ld, MIN = %6ld\n",
            LONG_MAX, LONG_MIN);
}

void RangesByComputation()
{
    unsigned char uch;
    signed char sch;
    char ch;
    unsigned int uint;
    int i;
    signed int sint;
    unsigned long ulong;
    long l;

    /* compute ranges of unsigned char */
    uch = 0;
    while ((unsigned char)(uch+1) > (unsigned char)0)
       uch++;
    printf("Unsigned char: MAX = %6u, MIN = %6u\n",
            uch, 0);

    /* compute ranges of signed char */
    sch = 0;
    while ((sch+1) > 0)
       sch++;
    printf("Signed char: MAX = %6d, ",
           sch);
    sch = 0;
    while ((sch-1) < 0)
       sch--;
    printf("MIN = %6d\n", sch);

    /* compute ranges of char */
    ch = 0;
    while ((ch+1) > 0)
       ch++;
    printf("Char: MAX = %6d, ",
           ch);
    ch = 0;
    while ((ch-1) < 0)
       ch--;
    printf("MIN = %6d\n", ch);

    /* compute ranges of unsigned int */
    while ((uint+1) > 0)
        uint++;
    printf("Unsigned int: MAX = %6u, MIN = %6u\n",
            uint, 0u);

    /* compute ranges of signed int */
    sint = 0x7fffffff;
    while ((sint+1) > 0)
        sint++;
    printf("Singed int: MAX = %6d, ",
            sint);
    sint = 0x80000000;
    while ((sint-1) < 0)
        sint--;
    printf("MIN = %6d\n", sint);

    /* compute ranges of int */
    i = 0;
    while ((i+1) > 0)
        i++;
    printf("Int: MAX = %6d, ", i);
    i = 0;
    while ((i-1) < 0)
        i--;
    printf("MIN = %6d\n", i);

    /* compute ranges of unsigned long */
    ulong = 0;
    while ((ulong+1) > 0)
        ulong++;
    printf("Unsigned long: MAX = %6lu, MIN = %6lu\n", ulong, 0UL);

    /* compute ranges of long */
    l = 0;
    while ((l+1) > 0)
        l++;
    printf("Long: MAX = %6ld, ", l);
    l = 0;
    while ((l-1) < 0)
        l--;
    printf("MIN = %6ld\n", l);
}
