#include <stdio.h>
#include <string.h>

#define IN      1
#define OUT     0
#define MAXLEN  20 

int main(void)
{
    int count[1+MAXLEN];  /* numbers of words of distinct lengths */
    int i, j;
    int length;     /* count length of a word */
    int state;
    int c;
    int maxcount;
    int maxcountWidth;
    int maxlenWidth;
    char str[10];

    /* Intialize count[] to 0 */
    for (i = 0; i < 1+MAXLEN; i++) {
        count[i] = 0;
    }
    maxcount = 0;
    length = 0;
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (state == IN) {
                state = OUT;
                if (length > MAXLEN) {  /* word with length >10 */
                    count[MAXLEN]++;
                    if (count[MAXLEN] > maxcount) {
                        maxcount = count[MAXLEN];
                    }
                } else {
                    count[length-1]++;  /* a word with length `length' */
                    if (count[length-1] > maxcount) {
                        maxcount = count[length-1];
                    }
                }
                length = 0; /* clear it and count next word */
            }
        } else {
            state = IN;
        }
        if (state == IN) {
            length++;
        }
    }

    /* print a histogram of lengths of words */
    maxcountWidth = sprintf(str, "%d", maxcount);
    maxlenWidth = sprintf(str, "%d", MAXLEN);
    for (i = maxcount; i > 0; i--) {
        printf("%*d |", maxcountWidth, i);
        for (j = 0; j < 1+MAXLEN; j++) {
            if (count[j] >= i) {
                printf("%*s*", maxlenWidth, " ");
            } else {
                printf("%*s ", maxlenWidth, " ");
            }
        }
        printf("\n");
    }
    printf("%*s +", maxcountWidth, " ");
    for (i = 0; i < maxlenWidth+1; i++) {
        str[i] = '-';
    }
    str[i] = '\0';
    for (i = 0; i < 1+MAXLEN; i++) {
        printf(str);
    }
    printf("--\n");
    printf("%*s", maxcountWidth+2, " "); 
    for (i = 0; i < MAXLEN; i++) {
        printf("%*d", maxlenWidth+1, i+1);
    }
    printf(" >%d\n", MAXLEN);

    return 0;
}

