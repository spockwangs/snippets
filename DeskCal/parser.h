#include <iostream>
#include <map>
#include <string>

namespace Parser {
    extern std::map<std::string, double> table;

    double expr(bool get);
}
