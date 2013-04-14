
#include "parser_impl.h"

std::map<std::string, double> Parser::table;

double Parser::expr(bool get)
{
    double left = term(get);

    for (;;) {
        switch(curr_tok) {
        case Lexer::PLUS:
            left += term(true);
            break;
        case Lexer::MINUS:
            left -= term(true);
            break;
        default:
            return left;
        }
    }
}

double Parser::term(bool get)
{
    double left = prim(get);

    for (;;) {
        switch (curr_tok) {
        case Lexer::MUL:
            left *= prim(true);
            break;
        case Lexer::DIV:
            if (double d = prim(true)) {
                left /= d;
                break;
            }
            throw Error::Zero_divide();
        default:
            return left;
        }
    }
}


double Parser::prim(bool get)
{
    if (get) get_token();

    switch (curr_tok) {
    case Lexer::NUMBER:
    {
        double v = number_value;
        get_token();
        return v;
    }
    case Lexer::NAME:
    {
        double &v = table[string_value];
        if (get_token() == Lexer::ASSIGN)
            v = expr(true);
        return v;
    }
    case Lexer::MINUS:
        return -prim(true);
    case Lexer::LP:
    {
        double e = expr(true);
        if (curr_tok != Lexer::RP)
            throw Error::Syntax_error("')' expected");
        get_token();
        return e;
    }
    default:
        throw Error::Syntax_error("primary expected");
    }
}
