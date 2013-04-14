#include <stdio.h>

#define IN      1
#define OUT     0

int main(void)
{
    int c;
    int state;

    state = IN;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t') {
            if (state == IN) {
                putchar('\n');
            }
            state = OUT;
        } else if (state == OUT) {
            state = IN;
        }
        if (state == IN) {
            putchar(c);
        }
    }
    return 0;
}

