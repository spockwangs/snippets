
#include "driver.h"
#include <sstream>

int main(int argc, char *argv[])
{
    using namespace Driver;
    using namespace std;

    istream* input;

    switch (argc) {
    case 1:
        input = &cin;
        break;
    case 2:
        input = new istringstream(argv[1]);
        break;
    default:
        cerr << "too many arguments\n";
        return 1;
    }

    set_input(input);

    driver();

    if (input != &cin)
        delete input;

    return no_of_errors;
}
