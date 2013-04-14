/***********************************************************************
 * K&R Exercise 3-2
 *     Write a function escape(s, t) that converts characters like newline
 *     and tab into visible escape sequences like \n and \t as it copies
 *     the string t to s. Use a switch. Write a function for the other
 *     direction as well, converting escape sequences into the real
 *     characters.
 */

#include <stdio.h>

void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            default:
                s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

void deescape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\\':
                switch (t[i+1]) {
                    case 't':
                        s[j++] = '\t';
                        break;
                    case 'n':
                        s[j++] = '\n';
                        break;
                }
                i++;
                break;
            default:
                s[j++] = t[i];
        }
    }
    s[j] = '\0';
}

int main(void)
{
    char s[100];
    char t[] = "lsdkf\tslkdf\nsldfsdf sdlkf";

    printf("t = %s\n", t);
    escape(s, t);
    printf("s = %s\n", s);
    deescape(t, s);
    printf("t = %s\n", t);

    return 0;
}
