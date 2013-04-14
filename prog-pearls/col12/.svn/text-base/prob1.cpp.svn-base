/*
 * prob1.cpp -- Problem 1 of column 12
 */

#include <iostream>
#include <cstdlib>

using namespace std;


int bigrand()
{
    return (rand() << 15) | rand();
}


int randint(int l, int u)
{
    return (rand() % (u-l+1)) + l;
}


int main()
{
    srand(time(0));
    for (int i = 0; i < 10; i++)
        cout << bigrand() << endl;

    return 0;
}
