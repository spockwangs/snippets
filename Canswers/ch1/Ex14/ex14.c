#include <stdio.h>

int main(void)
{
    int freq[26], thisval, maxfreq;
    int maxfreqWidth;
    int i, j;
    int c;
    char str[10];

    for (i = 0; i < 26; i++) {
        freq[i] = 0;
    }

    maxfreq = 0;
    thisval = 0;
    while ((c = getchar()) != EOF) {
        if ((c >= 'A') && (c <= 'Z')) {
            freq[c-'A']++;
            thisval = freq[c-'A'];
        }
        if ((c >= 'a') && (c <= 'z')) {
            freq[c-'a']++;
            thisval = freq[c-'a'];
        }
        if (thisval > maxfreq) {
            maxfreq = thisval;
        }
    }

    maxfreqWidth = sprintf(str, "%d", maxfreq);
    for (i = maxfreq; i > 0; i--) {
        printf("%*d |", maxfreqWidth, i);
        for (j = 0; j < 26; j++) {
            if (freq[j] >= i) {
                printf("%*s*", 1, " ");
            } else {
                printf("%*s ", 1, " ");
            }
        }
        printf("\n");
    }
    printf("%*s +", maxfreqWidth, " ");
    for (i = 0; i < 2; i++) {
        str[i] = '-';
    }
    str[i] = '\0';
    for (i = 0; i < 26; i++) {
        printf(str);
    }
    printf("-\n");
    printf("%*s", maxfreqWidth+2, " "); 
    for (i = 0; i < 26; i++) {
        printf("%*c", 2, i+'a');
    }
    return 0;
}

