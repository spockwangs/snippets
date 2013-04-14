/*
 * self.c -- Print itself.
 *
 * Time-stamp: <2010-06-03 14:46:41 wbb>
 *
 * Compile
 *   gcc -W -Wall -pedantic -std=c99 self.c
 */

#include <stdio.h>
int main()
{
    char *s="#include <stdio.h>%cint main()%c{%c    char *s=%c%s%c;%c    printf(%c%s%c, 10, 10, 10, 34, s, 34, 10, 34, s, 34, 10, 10, 10);%c    return 0;%c}%c";
    printf("#include <stdio.h>%cint main()%c{%c    char *s=%c%s%c;%c    printf(%c%s%c, 10, 10, 10, 34, s, 34, 10, 34, s, 34, 10, 10, 10);%c    return 0;%c}%c", 10, 10, 10, 34, s, 34, 10, 34, s, 34, 10, 10, 10);
    return 0;
}
