#include "big-integer.h"
#include <iostream>
#include <iterator>

using namespace std;

int main()
{
    BigInteger i1, i2, i3;
    cin >> i1 >> i2;
    i3 = i1 % i2;
    cout << i3 << endl;
    return 0;
}
