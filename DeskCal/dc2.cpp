/*
 * dc.cpp -- A simple desktop calculator rewritten using c-style
 *
 * Grammar -
 *   program:
 *      END
 *      expr_list END
 *
 *   expr_list:
 *      PRINT
 *      expression PRINT
 *      expression PRINT expr_list
 *
 *   expression:
 *      assignment-expression
 *      expression, assignment-expression
 *
 *   assignment-expression:
 *      additive-expression
 *      NAME = assignment-expression
 *
 *   additive-expression:
 *      multiplicative-expression
 *      additive-expression + multiplicative-expression
 *      additive-expression - multiplicative-expression
 *
 *   multiplicative-expression:
 *      unary-expression
 *      multiplicative-expression * multiplicative-expression
 *      multiplicative-expression / multiplicative-expression
 *
 *   unary-expression:
 *      primary-expression
 *      - unary-expression
 *      + unary-expression
 *
 *   primary-expression:
 *      NAME
 *      NUMBER
 *      ( expression )
 *
 */

#include <iostream>
#include <string>
#include <map>
#include <cctype>   // for isalpha(), isalnum() */

using namespace std;

enum Token_value {
    NAME,       NUMBER,     END,
    PLUS='+',   MINUS='-',  MUL='*',    DIV='/',
    PRINT=';',  ASSIGN='=', LP='(',     RP=')',
    COMMA=','
};

struct symbol {
    Token_value type;
    double num_value;
    string str_value;
};

            /* global variables */
symbol curr_sym;
map<string, double> table;
int no_of_errors;

            /* function prototypes */
double expr(bool);
double assign_exp(bool);
double add_exp(bool);
double mul_exp(bool);
double unary_exp(bool);
double prim_exp(bool);
Token_value get_token();
void unget_token(const symbol *);
double error(const string s);

double expr(bool get)
{
    double left;

    left = assign_exp(get);
    for (;;) {
        switch(curr_sym.type) {
        case COMMA:
            left = assign_exp(true);
            break;
        default:
            return left;
        }
    }
}

double assign_exp(bool get)
{
    double left;

    if (get)
        get_token();

    switch (curr_sym.type) {
    case NAME:
    {
        symbol sym = curr_sym;
        if (get_token() != ASSIGN) {
            unget_token(&sym);
            return add_exp(false);
        }
        table[curr_sym.str_value] = left = assign_exp(true);
        return left;
    }
    default:
        return add_exp(false);
    }
}

double add_exp(bool get)
{
    double left;

    left = mul_exp(get);

    for (;;) {
        switch (curr_sym.type) {
        case PLUS:
            left += mul_exp(true);
            break;
        case MINUS:
            left -= mul_exp(true);
            break;
        default:
            return left;
        }
    }
}

double mul_exp(bool get)
{
    double left;

    left = unary_exp(get);

    for (;;) {
        switch (curr_sym.type) {
        case MUL:
            left *= unary_exp(true);
            break;
        case DIV:
            left /= unary_exp(true);
            break;
        default:
            return left;
        }
    }
}

double unary_exp(bool get)
{
    if (get)
        get_token();

    for (;;) {
        switch (curr_sym.type) {
        case PLUS:
            return unary_exp(true);
        case MINUS:
            return -unary_exp(true);
        default:
            return prim_exp(false);
        }
    }
}

double prim_exp(bool get)
{
    if (get)
        get_token();

    switch (curr_sym.type) {
    case NAME:
    {
        double& v = table[curr_sym.str_value];
        get_token();
        return v;
    }
    case NUMBER:
    {
        double v = curr_sym.num_value;
        get_token();
        return v;
    }
    case LP:
    {
        double e;
        e = expr(true);
        if (curr_sym.type != RP)
            return error("')' expected");
        get_token();
        return e;
    }
    default:
        return error("primary-expression expected");
    }
}

static symbol last;
static bool islast = false; // get token from last if true, otherwise from cin

Token_value get_token()
{
    char ch = 0;

    if (islast) {
        islast = false;
        curr_sym = last;
        return curr_sym.type;
    }

    do {    // skip white space except '\n'
        if (!cin.get(ch)) {
            return curr_sym.type = END;
        }
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
    case 0:
        return curr_sym.type = END;
    case '\n':
        return curr_sym.type = PRINT;
    case ';': case '*': case '/': case '+':
    case '-': case '(': case ')': case '=':
    case ',':
        return curr_sym.type = Token_value(ch);
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9': 
    case '.':
        cin.putback(ch);
        cin >> curr_sym.num_value;
        return curr_sym.type = NUMBER;
    default:
        if (isalpha(ch)) {
            curr_sym.str_value = ch;
            while (cin.get(ch) && isalnum(ch))
                curr_sym.str_value.push_back(ch);
            cin.putback(ch);
            return curr_sym.type = NAME;
        }
        error("bad token");
        return curr_sym.type = PRINT;
    }
}

void unget_token(const symbol *sym)
{
    islast = true;
    last = curr_sym;
    curr_sym = *sym;
}


double error(const string s)
{
    no_of_errors++;
    cerr << "error: " << s << '\n';
    return 1;
}

int main()
{
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    cout << "Desktop calculator, version 1.\n";
    while (cin) {
        cout << "> ";
        get_token();
        if (curr_sym.type == END) {
            cout << "Byebye!\n";
            break;
        }
        if (curr_sym.type == PRINT)
            continue;
        cout << "value: " << expr(false) << '\n';
    }

    return no_of_errors;
}
