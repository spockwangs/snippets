/*
 * csize.c -- Print size of various primitive types in C.
 *
 * Time-stamp: <2010-08-04 21:30:35 wbb>
 */
 
#include <stdio.h>
#include <limits.h>

#define prssize(type, max, min)                                 \
     printf("%15s: size = %d, max = %12ld, min = %12ld\n",      \
            #type, sizeof(type), (long) max, (long) min)

#define prusize(type, max, min)                                         \
     printf("%15s: size = %d, max = %12lu, min = %12lu\n",              \
            #type, sizeof(type), (unsigned long) max, (unsigned long)min)

int main()
{
     prssize(char, CHAR_MAX, CHAR_MIN);
     prusize(unsigned char, UCHAR_MAX, 0);
     prssize(signed char, SCHAR_MAX, SCHAR_MIN);
     prssize(short, SHRT_MAX, SHRT_MIN);
     prusize(unsigned short, USHRT_MAX, SHRT_MIN);
     prssize(signed short, SHRT_MAX, SHRT_MIN);
     prssize(int, INT_MAX, INT_MIN);
     prusize(unsigned int, UINT_MAX, 0);
     prssize(signed int, INT_MAX, INT_MIN);
     prssize(long, LONG_MAX, LONG_MIN);
     prusize(unsigned long, ULONG_MAX, 0);
     prssize(signed long, LONG_MAX, LONG_MIN);
     
     return 0;
}
