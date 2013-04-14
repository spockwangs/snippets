#include <stdio.h>
#define MAXLINE     1000

int getline(char line[], int maxline);
void trim(char s[], int len);

int main(void)
{
    int len;
    int max;
    char line[MAXLINE];

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        trim(line, len);
        printf("%s", line);
    }

    return 0;
}

/* getline: read a line into s (if too long truncated),  return its
 * actual length */
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

/* trim: remove all trailing blanks and tabs in 's' */
void trim(char s[], int len)
{
    int i; 
    int hasnl;  /* if 's' end with a newline */

    hasnl = 0;
    if (s[len-1] == '\n')
        hasnl = 1;
    for (i = len-1; i >= 0 && (s[i]==' ' || s[i]=='\t' || s[i]=='\n'); 
            i--);
    ++i;
    if (i == 0) {   /* blank line */
        s[0] = '\0';
    } else {
        if (hasnl == 1) {
            s[i++] = '\n';
        }
        s[i] = '\0';
    }
}
