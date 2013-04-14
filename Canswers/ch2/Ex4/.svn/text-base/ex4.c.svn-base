/**********************************************************************
 * K&R Exercise 3-4
 *      Write an alternate version of squeeze(s1, s2) that deletes each
 *      character in s1 that matches any character in the string s2.
 */

#include <stdio.h>
#include <assert.h>

void squeeze(char s1[], char s2[])
{
    int i, j, k;

    assert(s1 != NULL && s2 != NULL);

    i = 0, j = 0;
    while (s1[j] != '\0') {
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[j] == s2[k])
                break;
        }
        if (s2[k] != '\0')
            j++;
        else 
            s1[i++] = s1[j++];
    }
    s1[i] = '\0';
}

int main()
{
    char s1[100], s2[100];

    printf("Input s1: ");
    scanf("%s", s1);
    printf("Input s2: ");
    scanf("%s", s2);
    printf("Before squeezing: s1 = %s, s2 = %s\n", s1, s2);
    squeeze(s1, s2);
    printf("After squeezing: s1 = %s\n", s1);

    return 0;
}
