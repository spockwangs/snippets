#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[])
{
    int state;
    enum { NORMAL, BEGIN, DASH };
    int c, begin;
    int i, j, k;

    i = 0, j = 0;
    state = NORMAL;
    while ((c = s1[i++]) != '\0') {
        switch (state) {
            case NORMAL:
                if (isalnum(c)) {
                    state = BEGIN;
                    begin = c;
                }
                s2[j++] = c;
                break;
            case BEGIN:
                if (c == '-') {
                    state = DASH;
                } else {
                    if (isalnum(c)) {
                        begin = c;
                    } else {
                        state = NORMAL;
                    }
                    s2[j++] = c;
                }
                break;
            case DASH:
                if (isalnum(c)) {
                    if ((isdigit(begin) && isdigit(c)) || 
                         (isalpha(begin) && isalpha(c))) {
                        if (c > begin) {
                            for (k = begin+1; k < c; k++) {
                                s2[j++] = k;
                            }
                        } else {
                            for (k = begin-1; k > c; k--) {
                                s2[j++] = k;
                            }
                        }
                        s2[j++] = c;
                        state = BEGIN;
                        begin = c;
                    } else {
                        s2[j++] = '-';
                        s2[j++] = c;
                        state = BEGIN;
                        begin = c;
                    }
                } else {
                    s2[j++] = '-';
                    s2[j++] = c;
                    state = NORMAL;
                }
                break;
            }
    }
    if (state == DASH)
        s2[j++] = '-';
    s2[j] = '\0';
}
                            
int main()
{
    char s1[100];
    char s2[500];

    printf("Input s1: ");
    scanf("%s", s1);
    expand(s1, s2);
    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);

    return 0;
}
