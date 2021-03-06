/******************************************************************************
 * K&R Ex4-11
 *      Modify getop so that it doesn't need to use ungetch. Hint: use an
 *      internal static variable.
 *
 * Author: wbb
 * Date: 2009-08-12 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXOP           100
#define NUMBER          '0'
#define IDENTIFIER      101


/* function declarations */
int getop(char []);
void push(double);
double pop(void);
double top(void);
int isempty(void);
int num_of_stack(void);
void list(void);
void clear(void);
void do_cmd(char s[]);
void do_var(char var[]);
void do_help(void);


/* Global variables */
double g_var[26];
int g_last;


/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    printf("Type 'help' to get a list of available commands.\n");
    printf("Type 'Ctrl-D' to quit!\n");
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case IDENTIFIER:
                do_cmd(s);
                break;
            case '+':
                if (num_of_stack() < 2) {
                    printf("Error: stack has less than 2 elements!\n");
                    break;
                }
                push(pop() + pop());
                break;
            case '*':
                if (num_of_stack() < 2) {
                    printf("Error: stack has less than 2 elements!\n");
                    break;
                }
                push(pop() * pop());
                break;
            case '-':
                if (num_of_stack() < 1) {
                    printf("Error: stack has less than 1 element!\n");
                    break;
                }
                op2 = pop();
                if (isempty())
                    push(-op2);
                else
                    push(pop() - op2);
                break;
            case '/':
                if (num_of_stack() < 2) {
                    printf("Error: stack has less than 2 elements!\n");
                    break;
                }
                op2 = pop();
                if (op2 != 0.0)
                    push (pop() / op2);
                else
                    printf("error: zero division\n");
                break;
            case '%':
                if (num_of_stack() < 2) {
                    printf("Error: stack has less than 2 elements!\n");
                    break;
                }
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);
                else 
                    printf("error: zero division\n");
                break;
            case '=':
                if (isempty()) {
                    printf("Error: stack is empty!\n");
                    break;
                }
                g_var[g_last] = pop();
                break;
            case '\n':  /* List all the elements in the stack. */
                do_cmd("list");
                break;
            default:
                printf("error: unkown command \'%s\'\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL  100

int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* top: return the top element of stack. */
double top(void)
{
    if (sp > 0)
        return val[sp-1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* isempty: test if the stack is empty */
int isempty(void)
{
    return sp == 0;
}

/* num_of_stack: return how many elements in the stack */
int num_of_stack(void)
{
    return sp - 0;
}

/* list: list all the elements in the stack, from top to bottom. */
void list(void)
{
    int i;

    if (isempty()) {
        printf("Stack is empty!\n");
        return;
    } else {
        printf("Stack: ");
        for (i = sp-1; i >= 0; i--) {
            printf("%.8g%s ", val[i], (i == sp-1) ? "(top)" : "");
        }
        printf("\n");
    }
}

/* clear: clear the stack. */
void clear(void)
{
    int i;

    sp = 0;
    for (i = 0; i < 26; i++)
        g_var[i] = 0.0;
}

#include <ctype.h>


/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, t;
    static int lastchar = EOF;

    /* ignore beginning spaces */
    c = lastchar == EOF ? getchar() : lastchar;
    lastchar = EOF;
    while (c == ' ' || c == '\t')
        c = getchar();
    s[0] = c;
    s[1] = '\0';

    /* Maybe a command. */
    i = 0;
    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getchar()))
            ;
        s[i] = '\0';
        if (c != EOF)
            lastchar = c;
        return IDENTIFIER;
    }

    /* Maybe an operator, also maybe a minus number. */
    if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-' && c != '+')
        return c;

    if (c == '-' || c == '+') {
        t = c;
        c = getchar();
        if (!isdigit(c) && c != '.') {  /* Not a negative number, a '-' operator. */
            lastchar = c;
            return t;
        }
        s[++i] = c;
    }
        
    /* Maybe an operand. */
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastchar = c;
    return NUMBER;
}


void do_cmd(char s[])
{
    double t1, t2;

    if (strcmp(s, "top") == 0) {
        printf("Top element: %.8g\n", top());
    } else if (strcmp(s, "dup") == 0) {
        if (isempty()) {
            printf("Error: stack is empty!\n");
            return;
        }
        t1 = top();
        push(t1);
    } else if (strcmp(s, "swap") == 0) {
        if (num_of_stack() < 2) {
            printf("Error: stack has less than 2 elements!\n");
            return;
        }
        t1 = pop(), t2 = pop();
        push(t1), push(t2);
    } else if (strcmp(s, "list") == 0) {
        list();
    } else if (strcmp(s, "clear") == 0) {
        clear();
    } else if (strcmp(s, "help") == 0) {
        do_help();
    } else if (strcmp(s, "sin") == 0) {
        if (isempty()) {
            printf("Error: stack is empty!\n");
            return;
        }
        t1 = pop();
        push(sin(t1));
    } else if (strcmp(s, "exp") == 0) {
        if (isempty()) {
            printf("Error: stack is empty!\n");
            return;
        }
        t1 = pop();
        push(exp(t1));
    } else if (strcmp(s, "pow") == 0) {
        if (num_of_stack() < 2) {
            printf("Error: pow needs at least 2 elements.\n");
            return;
        }
        t1 = pop();
        t2 = pop();
        push(pow(t1, t2));
    } else {
        do_var(s);
    }

}


void do_var(char var[])
{
    int len;

    len = strlen(var);
    if (len > 1) {
        printf("Error: only support signle-letter(lowercase) variable!\n");
        return;
    }
    if (var[0] > 'z' || var[0] < 'a') {
        printf("Error: variable name is lowercase!\n");
        return;
    }
    push(g_var[var[0] - 'a']);
    g_last = var[0] - 'a';
}


void do_help(void)
{
    printf("-----------------------------------------\n");
    printf("Operators: + -(unary or binary) * / %%\n");
    printf("Commands: \n"
           "    top\n"
           "    dup\n"
           "    swap\n"
           "    list\n"
           "    clear\n");
    printf("-----------------------------------------\n");
}

