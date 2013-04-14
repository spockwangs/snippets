/*
 * prob6.cpp -- Problem 6 of column 15
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

const int debug = false;

int cmplen(const char *s1, const char *s2)
{
    int count = 0;
    while ((*s1++ == *s2++) && *(s1-1) != '\0')
        count++;
    return count;
}

bool less_str(const char *s1, const char *s2)
{
   if (strcmp(s1, s2) < 0)
       return true;
   else
       return false;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "2 arguments required!\n";
        exit(1);
    }

    /*
     * Put input texts into an array of chars.
     */
    vector<char> texts;
    char c;
    fstream in(argv[1]);
    while (in.get(c))
        texts.push_back(c);
    int sz = texts.size();
    char *ptexts = new char[sz+1];    // +1 for NULL
    copy(texts.begin(), texts.end(), ptexts);
    ptexts[sz] = '\0';

    /*
     * Construct a suffix array of the input texts.
     */
    char **suffix = new char*[sz];
    for (int i = 0; i < sz; i++)
        suffix[i] = ptexts+i;
    sort(suffix, suffix+sz, less_str);

    if (debug) 
        for (int i = 0; i < sz; i++)
            cout << "suffix[" << i << "]: " << suffix[i] << endl;

    /*
     * Search for longest match with input string in the input texts.
     */
    string str;
    cout << "Search for string: ";
    while (cin >> str) {
        int l, u, m;
        l = -1, u = sz;
        while (l+1 != u) {
            m = (l+u)/2;
            if (strcmp(str.c_str(), suffix[m]) > 0)
                l = m;
            else
                u = m;
        }
        int maxlen = 0;
        for ( ; u < sz; u++) {
            int len = cmplen(suffix[u], str.c_str());
            if (len > maxlen)
                maxlen = len;
        }
        cout << "Longest match: maxlen = " << maxlen << endl;
        cout << "Search for string: ";
    }
    cout << endl;

    return 0;
}


