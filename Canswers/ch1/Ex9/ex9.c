#include <stdio.h>

int main(void)
{
    int c;
    int inblank;    /* encounter blanks */        

    inblank = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            inblank = 0;
            putchar(c);
        } else if (inblank == 0) {
            inblank = 1;
            putchar(c);
        }
    }

    return 0;
}

