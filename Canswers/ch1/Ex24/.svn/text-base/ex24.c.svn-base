/****************************************************************
 * K&R Exercise 1-24
 *     Write a program to check a C program for rudimentary 
 *     syntax errors like unbalanced parenthese, brackets and
 *     braces. Don't forget about quotes, both single and double,
 *     escape sequences, and comments.
 *
 */

#include <stdio.h>

#define MAXTOKENS   1000
#define NORMAL      0   /* outside quotes and comments */
#define IN_SINGLE_QUOTE     1   /* in single quote */
#define IN_DOUBLE_QUOTE     2   /* in double quotes */
#define IN_COMMENT   3   /* in comments */
#define BEGIN_COMMENT   4
#define END_COMMENT     5

void initStack();
void push(int c);
int pop();
int top();
int isempty();

/* Globals */
int stack[MAXTOKENS];
int sp;     /* point to top of stack */

int main()
{
    int c;
    int state;
    int line;
    int begin_esc;

    begin_esc = 0;
    state = NORMAL;
    initStack();
    line = 1;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '\\':
                begin_esc = 1-begin_esc;
                if (state == BEGIN_COMMENT) {
                    state = NORMAL;
                } else if (state == END_COMMENT) {
                    state = IN_COMMENT;
                } 
                break;
            case '"':
                if (begin_esc == 0) {
                    if (state == NORMAL) {
                        state = IN_DOUBLE_QUOTE;
                    } else if (state == IN_DOUBLE_QUOTE) {
                        state = NORMAL;
                    }
                }
                if (state == BEGIN_COMMENT) {
                    state = NORMAL;
                } else if (state == END_COMMENT) {
                    state = IN_COMMENT;
                }
                begin_esc = 0;
                break;
            case '\'':
                if (begin_esc == 0) {
                    if (state == NORMAL) {
                        state = IN_SINGLE_QUOTE;
                    } else if (state == IN_SINGLE_QUOTE) {
                        state = NORMAL;
                    }
                }
                if (state == BEGIN_COMMENT) {
                    state = NORMAL;
                } else if (state == END_COMMENT) {
                    state = IN_COMMENT;
                }
                begin_esc = 0;
                break;
            case '\n':
                line++;
                begin_esc = 0;
                if (state == BEGIN_COMMENT) {
                    state = NORMAL;
                } else if (state == END_COMMENT) {
                    state = IN_COMMENT;
                }
                break;
            case '/':
                if (state == NORMAL) {
                    state = BEGIN_COMMENT;
                } else if (state == END_COMMENT) {
                    state = NORMAL;
                }
                begin_esc = 0;
                break;
            case '*':
                if (state == BEGIN_COMMENT) {
                    state = IN_COMMENT;
                } else if (state == IN_COMMENT) {
                    state = END_COMMENT;
                }
                begin_esc = 0;
                break;
            default:
                begin_esc = 0;
                if (state == BEGIN_COMMENT) {
                    state = NORMAL;
                } else if (state == END_COMMENT) {
                    state = IN_COMMENT;
                }
                break;
        }
        if (state == NORMAL) {
            switch (c) {
                case '(':
                case '[':
                case '{':
                case '<':
                    push(c);
                    break;
                case ')':
                    if (top() != '(') {
                        printf("error: (#line %d) %c don't have a match.\n",
                                line, c);
                    } else {
                        pop();
                    }
                    break;
                case ']':
                    if (top() != '[') {
                        printf("error: (#line %d) %c don't have a match.\n",
                                line, c);
                    } else {
                        pop();
                    }
                    break;
                case '}':
                    if (top() != '{') {
                        printf("error: (#line %d) %c don't have a match.\n",
                                line, c);
                    } else {
                        pop();
                    }
                    break;
                case '>':
                    if (top() != '<') {
                        printf("error: (#line %d) %c don't have a match.\n",
                                line, c);
                        return 1;
                    } else {
                        pop();
                    }
                    break;
            }
        }
    }
    if (isempty()) {
        printf("All match well.\n");
    }
    return 0;
}

void initStack()
{
    sp = 0;
}

int isempty()
{
    return sp == 0;
}

void push(int c)
{
    assert(sp < MAXTOKENS);
    stack[sp] = c;
    sp++;
}

int pop()
{
    assert(!isempty());
    sp--;
    return stack[sp];
}

int top()
{
    assert(!isempty());
    return stack[sp-1];
}
