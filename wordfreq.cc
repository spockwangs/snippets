/*
 * Copyright (c) 2010. Wang Bingbing.
 *
 * Author: wbbtiger@gmail.com
 * Date: 2010-10-09
 *
 * Count words from standard input and print them in decreasing frequency order.
 */

#include <iostream>
#include <map>
#include <string>
#include <list>
#include <iterator>

using namespace std;

int main()
{	
    map<string, int> M;
    map<string, int>::iterator j;
    string t;
    while (cin >> t)
        M[t]++;

    map<int, list<string> > F;
    map<int, list<string> >::const_reverse_iterator i;
    list<string>::const_iterator k;
    for (j = M.begin(); j != M.end(); ++j)
        F[j->second].push_front(j->first);
    for (i = F.rbegin(); i != F.rend(); ++i)
        for (k = (i->second).begin(); k != (i->second).end(); ++k)
            cout << *k << "  " << i->first << endl;
    return 0;
}
