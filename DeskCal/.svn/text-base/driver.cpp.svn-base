
#include "driver.h"
#include "lexer.h"
#include "error.h"
#include "parser.h"
#include <iostream>

int Driver::no_of_errors;
std::istream* Driver::input = &std::cin;

void Driver::skip()
{
    no_of_errors++;

    while (*input) {
        char ch;
        input->get(ch);

        switch (ch) {
        case '\n':
        case ';':
            return;
        }
    }
}

using namespace Lexer;
using namespace Parser;
using namespace std;

void Driver::driver()
{
    table["pi"] = 3.1415926535897932385;
    table["e"] = 2.7182818284590452354;

    while (*input) {
        try {
            get_token();
            if (curr_tok == END)
                break;
            if (curr_tok == PRINT)
                continue;
            cout << expr(false) << '\n';
        }
        catch (Error::Zero_divide) {
            cerr << "attempt to divide by zero\n";
            if (curr_tok != PRINT)
                skip();
            ++Driver::no_of_errors;
        }
        catch (Error::Syntax_error e) {
            cerr << "syntax error: " << e.p << "\n";
            if (curr_tok != PRINT)
                skip();
            ++Driver::no_of_errors;
        }
    }
}

void Driver::set_input(std::istream* input)
{
    Driver::input = input;
}


