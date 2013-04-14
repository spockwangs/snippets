/*************************************************************************
 * K&R Exercise 4-1
 *     Write the function strrindex(s, t), which returns the position of
 *     the rightmost occurence of t in s, or -1 if there is none.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

int strrindex(char s[], char t[])
{
    int i, j, k;

    assert(s != NULL && t != NULL);

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return j-1;
    }
    return -1;
}

int test(char s[], char t[])
{
    char *p;
    int index;

    index = strrindex(s, t);
    p = strstr(s, t);
    if ((index == -1 && p == NULL) ||
        (index == p+strlen(t)-1-s))
        return 0;
    else
        return -1;
}

int main()
{
    char s[] = "Hello, world!";
    char t[] = "world";

    if (!test(s, t))
        printf("Success!\n");
    return 0;
}
