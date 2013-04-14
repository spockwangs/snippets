/******************************************************************
 * K&R Exercise 1-24
 *      Write a program to check a C program for rudimentary 
 *      syntax errors linke unbalanced parentheses, brackets and 
 *      braces. Don't forget about quotes, both single and double,
 *      escape sequences, and comments.
 * 
 *      This program checks a C program for unbalanced parentheses,
 *      brackets, braces single and double quotes. If there is 
 *      some mismatch the first error will be identifed and the
 *      subsequent errors, if any, will be ignored.
 */

#include <stdio.h>
#include <assert.h>

#define MAX_TOKENS  1000

typedef struct {
    char c;
    int line;
} MATCH;

void push(char c, int l);
MATCH pop();
int isEmpty();
MATCH top();
void initStack();

MATCH stack[MAX_TOKENS];
int sp;

int main()
{
    char p[] = "0/!1"
               "0'P4"
               "0\"P5"
               "0(P0"
               "0{P0"
               "0[P0"
               "0)(0"
               "0}{0"
               "0][0"
               "0.!0"
               "1/!8"
               "1*!2"
               "1'!4"
               "1\"!5"
               "1(P0"
               "1{P0"
               "1[P0"
               "1)(0"
               "1}{0"
               "1][0"
               "1.!0"
               "2*!3"
               "2.!2"
               "3/!0"
               "3*!3"
               "3.!2"
               "4''0"
               "4\\!6"
               "4.!4"
               "5\"\"0"
               "5\\!7"
               "5.!5"
               "6.!4"
               "7.!5"
               "8\n!0"
               "8\\!9"
               "8.!8"
               "9.!8";
    int i, d;
    int c;
    char s, n;
    int line;

    initStack();
    s = '0';
    line = 1;
    while ((c = getchar()) != EOF) {
        d = 0;
        if (c == '\n')
            line++;
        for (i = 0; p[i] != '\0' && d == 0; i += 4) {
            if (p[i] == s && (p[i+1] == c || p[i+1] == '.')) {
                if (p[i+2] == '!') {

                } else if (p[i+2] == 'P') {
                    push(c, line);
                } else if (!isEmpty() && p[i+2] == top().c) {
                    pop();
                } else {
                    if (isEmpty()) {
                        printf("error: "
                               "'%c'(#%d) doesn't match anything.\n",
                                c, line);
                        return 1;
                    } else {
                        printf("error: '%c'(#%d) doesn't have a match.\n",
                            top().c, top().line);
                        return 1;
                    }
                }
                n = p[i+3];
                d = 1;
            }
        }
        s = n;
    }
    if (!isEmpty()) {
        printf("error: '%c'(#%d) doesn't have a match.\n",
                top().c, top().line);
        return 1;
    } else {
        printf("Congratulations! All match well!\n");
        return 0;
    }
}

void initStack()
{
    sp = 0;
}

void push(char c, int line)
{
    assert(sp < MAX_TOKENS);
    stack[sp].c = c;
    stack[sp].line = line;
    ++sp;
}

MATCH pop()
{
    assert(!isEmpty());

    sp--;
    return stack[sp];
}

MATCH top()
{
    assert(!isEmpty());
    return stack[sp-1];
}

int isEmpty()
{
    return sp == 0;
}
