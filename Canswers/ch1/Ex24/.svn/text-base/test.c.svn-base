#include <stdio.h>

#define MAXTOKENS   1000
#define NORMAL      0   /* outside quotes and comments */
#define IN_SINGLE_QUOTE     1   /* in single quote */
#define IN_DOUBLE_QUOTE     2   /* in double quotes */
#define INCOMMENT   3   /* in comments */

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
                break;
            case '"':
                begin_esc = 0;
                if (state == NORMAL) {
                    state = IN_DOUBLE_QUOTE;
                } else if (state == IN_DOUBLE_QUOTE) {
                    state = NORMAL;
                }
                break;
            case '\'':
                if (begin_esc == 0) {
                    if (state == NORMAL) {
                        state = IN_SINGLE_QUOTE;
                    } else if (state == IN_SINGLE_QUOTE) {
                        state = NORMAL;
                    }
                }
                begin_esc = 0;
                break;
            case '\n':
                line++;
                begin_esc = 0;
                break;
            default:
                begin_esc = 0;
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
    } else {
        printf("error: %c don't have a match.\n", top());
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
    stack[sp] = c;
    sp++;
}

int pop()
{
    sp--;
    return stack[sp];
}

int top()
{
    return stack[sp-1];
}
