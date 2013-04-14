#include "parser.h"
#include "error.h"
#include "lexer.h"
#include <map>
#include <string>

namespace Parser {
    extern std::map<std::string, double> table;

    double prim(bool get);
    double term(bool get);
    double expr(bool get);

    using Lexer::get_token;
    using Lexer::curr_tok;
    using Lexer::number_value;
    using Lexer::string_value;
}
