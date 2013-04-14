#include <stdio.h>

#define CPPSTYLE

#define INCOMMENT       0       /* in C-style comments */
#define INCOMMENT2      1       /* in C++-style comments */
#define NORMAL          2       /* not in comments or quotes */
#define IN_SINGLE_QUOTE 3       /* in single quotes */
#define IN_DOUBLE_QUOTE 4       /* in double quotes */
#define BEGINCOMMENT    5       /* after encounter '/' */
#define ENDCOMMENT      6       /* encounter '*' in comment */
#define OUT_ESC         0
#define BEGIN_ESC       1
#define IN_ESC          2

int main()
{
    int c;
    int state;      /* are we in comments or not? */
    int flag;       /* are we beginning a escape sequence */
    
    state = NORMAL;
    flag = OUT_ESC;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '/':
                if (state == IN_SINGLE_QUOTE ||
                        state == IN_DOUBLE_QUOTE) {
                    if (flag == BEGIN_ESC) {
                        flag = OUT_ESC;
                    }
                    putchar(c);
                } else if (state == NORMAL) {
                    state = BEGINCOMMENT;
                } else if (state == ENDCOMMENT) {
                    state = NORMAL;
                } else if (state == BEGINCOMMENT) {
#ifdef CPPSTYLE
                    state = INCOMMENT2;
#else
                    putchar('/');
#endif
                } 
                break;
            case '\\':
                if (state == IN_SINGLE_QUOTE || state == IN_DOUBLE_QUOTE) {
                    if (flag == BEGIN_ESC) {
                        flag = OUT_ESC;
                    } else 
                        flag = BEGIN_ESC;
                } else if (state == BEGINCOMMENT) {
                    putchar('/');
                    state = NORMAL;
                } else if (state == ENDCOMMENT) {
                    state = INCOMMENT;
                }
                if (state != INCOMMENT 
#ifdef CPPSTYLE
                        && state != INCOMMENT2
#endif
                        ) {
                    putchar(c);
                }
                break;
            case '*':
                if (state == IN_SINGLE_QUOTE || 
                        state == IN_DOUBLE_QUOTE) {
                    flag = OUT_ESC;
                    putchar(c);
                } else if (state == BEGINCOMMENT) {
                    state = INCOMMENT;
                } else if (state == INCOMMENT) {
                    state = ENDCOMMENT;
                } else if (state == NORMAL) {
                    putchar(c);
                }
                break;
            case '"':
                if (flag == OUT_ESC) {
                    if (state == IN_DOUBLE_QUOTE) {
                        state = NORMAL;
                        putchar(c);
                    } else if (state == BEGINCOMMENT) {
                        state = IN_DOUBLE_QUOTE;
                        putchar('/');
                        putchar(c);
                    } else if (state == ENDCOMMENT) {
                        state = INCOMMENT;
                    } else if (state != INCOMMENT 
#ifdef CPPSTYLE
                            && state != INCOMMENT2
#endif
                            ) {
                        state = IN_DOUBLE_QUOTE;
                        putchar(c);
                    }
                } else if (flag == BEGIN_ESC) {
                    flag = OUT_ESC;
                    putchar(c);
                }
                break;
            case '\'':
                if (flag == OUT_ESC) {
                    if (state == IN_SINGLE_QUOTE) {
                        state = NORMAL;
                        putchar(c);
                    } else if (state == BEGINCOMMENT) {
                        state = IN_SINGLE_QUOTE;
                        putchar('/');
                        putchar(c);
                    } else if (state == ENDCOMMENT) {
                        state = INCOMMENT;
                    } else if (state != INCOMMENT 
#ifdef CPPSTYLE
                            && state != INCOMMENT2
#endif
                            ) {
                        state = IN_SINGLE_QUOTE;
                        putchar(c);
                    }
                } else if (flag == BEGIN_ESC) {
                    flag = OUT_ESC;
                    putchar(c);
                }
                break;
#ifdef CPPSTYLE
            case '\n':
                if (state == INCOMMENT2) {
                    state = NORMAL;
                } else if (state == BEGINCOMMENT) {
                    state = NORMAL;
                } else if (state == ENDCOMMENT) {
                    state = INCOMMENT;
                } else if (state == IN_SINGLE_QUOTE ||
                        state == IN_DOUBLE_QUOTE) {
                    flag = OUT_ESC;
                }
                if (state != INCOMMENT) {
                    putchar('\n');
                }
                break;
#endif
            default:
                if (state == BEGINCOMMENT) {
                    state = NORMAL;
                    putchar('/');
                    putchar(c);
                } else if (state == ENDCOMMENT) {
                    state = INCOMMENT;
                } else if (state != INCOMMENT 
#ifdef CPPSTYLE
                        && state != INCOMMENT2
#endif
                ) {
                    putchar(c);
                }
                if (state == IN_SINGLE_QUOTE ||
                        state == IN_DOUBLE_QUOTE) {
                    flag = OUT_ESC;
                }
                break;
        }
    }

    return 0;
}

