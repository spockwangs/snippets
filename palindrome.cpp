/*
 * palindrome.cpp -- Print the longnest palindrome in a string.
 *
 * Compile
 *   g++ -W -Wall -std=c++98 -pedantic palindrome.cpp
 */

#include <iostream>
#include <cassert>
#include <iterator>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

#undef DEBUG

#ifdef DEBUG
#define dprintf(s) printf s     // s shoud be surrounded by double parentheses
#else
#define dprintf(s)
#endif

struct suffix_struct {
    char *str;
    char *id;     // which string this suffix belongs to
};

bool less_suffix(const suffix_struct& s1, const suffix_struct& s2)
{
    if (strcmp(s1.str, s2.str) < 0)
        return true;
    else
        return false;
}

int comlen(const char *s1, const char *s2)
{
    int l = 0;
    while ((*s1++ == *s2++) && *(s1-1) != 0)
        l++;
    return l;
}

int main()
{
    const int MAXLEN = 100;
    char str1[MAXLEN], str2[MAXLEN];
    int sz, ch;

    sz = 0;
    while ((sz < MAXLEN-1) && (ch = cin.get()) != '\n' && ch != EOF)
        str1[sz++] = ch;
    str1[sz] = 0;
    reverse_copy(str1, str1+sz, str2);
    str2[sz] = 0;

    dprintf( ("original string: %s\n", str1) );
    dprintf( ("reverse string: %s\n", str2) );
    
    /*
     * Construct a suffix array for str1 and str2.
     */
    int n = 2*sz;
    suffix_struct *suffix = new suffix_struct[n];
    int i = 0;
    for (char *p = str1; *p; p++) {
        suffix[i].str = p;
        suffix[i].id = str1;
        i++;
    }
    for (char *p = str2; *p; p++) {
        suffix[i].str = p;
        suffix[i].id = str2;
        i++;
    }
    sort(suffix, suffix+n, less_suffix);

    dprintf( ("\nSuffix array: \n") );
#ifdef DEBUG
    for (int i = 0; i < n; i++)
        dprintf( ("%2d: %p %s\n", i, (void *) suffix[i].id, suffix[i].str) );
#endif

    /*
     * Find the longgest palindrome in the string.
     */
    int maxlen = 0, maxi = -1;
    for (i = 0; i < n-1; i++) {
        if (suffix[i].id != suffix[i+1].id) {
            int len = comlen(suffix[i].str, suffix[i+1].str);
            int p = suffix[i].str - suffix[i].id;
            int q = suffix[i+1].str - suffix[i+1].id;
            if (((sz-p-q) > 0) && (len >= (sz-p-q)/2) && (len > maxlen)) {   // A palindrom
                maxlen = len;
                if (suffix[i].id == str1)
                    maxi = i;
                else
                    maxi = i+1;
            }
        }
    }

    dprintf( ("\nmaxi = %d, maxlen = %d\n", maxi, maxlen) );
    printf("Panlindrom: %.*s\n", maxlen, suffix[maxi].str);
    return 0;
}
