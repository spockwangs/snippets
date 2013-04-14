/*
 * Write a macro to test if a variable is signed or unsigned.
 *
 * Date: 2009-05-16
 * Author: wbb
 *
 * Bug
 *   'isSigned()' doesn't work for unsigned char variable and unsigned
 *   short variable due to integer promotion.
 */

#include <stdio.h>

/* test if a variable is signed */
#define isSigned(var) ((var < 0) || (~var < 0))

/* test if a type is signed */
#define isSigned2(type) (((type)~0) < 0)

#define test1(type)                                             \
    do {                                                        \
        type v;                                                 \
        if (isSigned(v)) printf("%s var -> signed\n", #type);   \
        else printf("%s var -> unsigned\n", #type);             \
    } while (0)

#define test2(type)                                             \
    do {                                                        \
        if (isSigned2(type)) printf("%s is signed\n", #type);   \
        else printf("%s is unsigned\n", #type);                 \
    } while (0)

int main()
{
    /*
     * In gcc, for enumerated type, if it contains some negative
     * enumeration constant it is implemented using some signed integer
     * type.  Otherwise it is implemented using some unsigned integer type.
     * In standard C, each enumerated type is represented by an
     * implementation-defined integer type.  It does not specify the its
     * sign.  See Section 5.5 of "C: A Reference Manual".
     */
    enum SIGN { A = -1 };
    enum UNSIGN { B };
    
    test1(unsigned char);
    test1(char);
    test1(short);
    test1(unsigned short);
    test1(int);
    test1(unsigned int);
    test1(long);
    test1(unsigned long);
    test1(enum SIGN);
    test1(enum UNSIGN);

    printf("\n");
    
    test2(unsigned char);
    test2(char);
    test2(short);
    test2(unsigned short);
    test2(int);
    test2(unsigned int);
    test2(long);
    test2(unsigned long);
    test2(enum SIGN);
    test2(enum UNSIGN);

    return 0;
}
