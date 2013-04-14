/*
 * prob7.cpp -- Problem 7 of column 12
 */


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <error.h>

using namespace std;


int bigrand()
{
    return ((rand()&0x7FFF) << 15) | rand();
}

void randselect(int m, int n)
{
    assert(0 <= m && m <= n);

    if (m > 0) {
        if (bigrand()%n < m) {
            randselect(m-1, n-1);
            cout << n-1 << endl;
        } else {
            randselect(m, n-1);
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc != 3)
        error(1, 0, "2 arguments required");

    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    randselect(m, n);
}
