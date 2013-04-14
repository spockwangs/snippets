/*
 * Copyright (c) 2011 wbb.
 *
 * Write codes to test if a variable or type is signed or unsigned.
 *
 * Date: 2011-02-16
 */

#include <iostream>

/*
 * issigned --
 *   Test if a type is an signed type or unsigned type.
 */
template <typename T>
bool issigned()
{
    return T(~0) < 0;
}

/*
 * issigned --
 *   Test if a variable is signed or unsigned.
 */
template <typename T>
bool issigned(T v)
{
    return T(~0) < 0;
}

int main()
{
    using namespace std;

    unsigned char c;
    cout << "c is " << (issigned(c) ? "signed.\n" : "unsigned.\n");
    cout << "char is an "
         << (issigned<char>() ? "signed type.\n" : "unsigned type.\n");
    return 0;
}
