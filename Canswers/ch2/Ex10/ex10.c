/************************************************************************
 * K&R Exercise 2-10
 *     Rewrite the function lower, which converts upper case letters to
 *     lower case, with a conditional expression instead of if-else.
 */

#include <stdio.h>
#include <string.h>

#define PORTABLE_SOLUTION 0

/* lower - Return lower case of c if c is an upper case letter.
 *         Otherwise return c unchanged.
 * Note: this program only work on ASCII characters.
 */
int lower(int c)
{
    return c >= 'A' && c <= 'Z' ? c+'a'-'A' : c;
}

#if PORTABLE_SOLUTION
/* lower: convert c to lower case */
int lower(int c)
{
    char *Uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *Lowercase = "abcdefghijklmnopqrstuvwxyz";
    char *p = NULL;

    return (NULL == (p = strchr(Uppercase, c))) ? 
        c : *(Lowercase + (p - Uppercase));
}
#endif


int main()
{
    char str[100];
    int i;

    printf("Input an string(without spaces): ");
    scanf("%s", str);
    printf("Lower case: ");
    for (i = 0; str[i] != '\0'; i++) {
        printf("%c", lower(str[i]));
    }
    putchar('\n');
    return 0;
}

