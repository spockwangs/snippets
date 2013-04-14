#include <stdio.h>

int main(void)
{
    int c;
    int currCol, padd;
    int n = 8;
    int i;

    currCol = 1;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            putchar(c);
            currCol = 1;
        } else if (c != '\t') {
            putchar(c);
            currCol++;
        } else {
            padd = n - (currCol-1) % n;
            for (i = 0; i < padd; i++)
                putchar(' ');
            currCol += padd;
        }
    }

    return 0;
}
