/*
 * markov
 *   C++ version.
 *
 * Usage
 *   ./markov < file
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <deque>
#include <vector>

using namespace std;

typedef deque<string> Prefix;
map<Prefix, vector<string> > statetab;  // prefix --> suffixes

enum {
    NPREF   = 2,        // # of prefix words
    MAXGEN  = 1000      // max # words generated
};
const string NONWORD = "\n";


void add(Prefix& prefix, const string& s);

/*
 * build --
 *   Read input words, build state table.
 */
void build(Prefix& prefix, istream& in)
{
    string buf;

    while (in >> buf) {
        add(prefix, buf);
    }
}


/*
 * add --
 *   Add word to suffix list, update prefix.
 */
void add(Prefix& prefix, const string& s)
{
    if (prefix.size() == NPREF) {
        statetab[prefix].push_back(s);
        prefix.pop_front();
    }
    prefix.push_back(s);
}


/*
 * generate --
 *   Produce output, one word per line
 */
void generate(int nwords)
{
    Prefix prefix;
    int i;

    for (i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    for (i = 0; i < nwords; i++) {
        vector<string>& suf = statetab[prefix];
        const string& w = suf[rand() % suf.size()];
        if (w == NONWORD)
            break;
        cout << w << "\n";
        prefix.pop_front();
        prefix.push_back(w);
    }
}

int main(void)
{
    int nwords = MAXGEN;
    Prefix prefix;

    for (int i = 0; i < NPREF; i++)
        add(prefix, NONWORD);
    build(prefix, cin);
    add(prefix, NONWORD);
    generate(nwords);
    return 0;
}
