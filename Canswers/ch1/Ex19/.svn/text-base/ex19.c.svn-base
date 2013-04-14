/* K&R Exercise 1-19
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXLINE     1000

void reverse(char s[]);
int getline(char s[], int lim);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

/* getline: read a line into s (if too long truncated),  return its
 * actual length. Return 0 if encounter the EOF. */
int getline(char s[], int lim)
{
    int c, i, j;

    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < lim-1) {
            s[j++] = c;
        }
    }
    if (c == '\n') {
        if (i < lim-1) {
            s[j++] = c;
        }
        ++i;
    }
    s[j] = '\0';
    return i;
}

/**
 * reverse - reverse the character string in 's'
 *
 * Requires:
 *     s is a null terminated string.
 * Modifies:
 *     s
 */
void reverse(char s[])
{
    int len;
    int i;
    char tmp;

    len = strlen(s);
    assert(s[len] == '\0');
    for (i = 0; i < len/2; i++) {
        tmp = s[i];
        s[i] = s[len-1-i];
        s[len-1-i] = tmp;
    }
}
