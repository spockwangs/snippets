/*
 * prob9.cpp -- Problem 9 of column 15
 *
 * Print LCS (Longest Common Substring) of two strings.
 */

#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const bool debug = false;
const int MAXLEN = 100;

bool less_suffix(const char *s1, const char *s2)
{
    if (strcmp(s1, s2) < 0)
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
    char str1[MAXLEN], str2[MAXLEN];
    cin >> str1 >> str2;

    /*
     * Construct a suffix array for str1 and str2.
     */
    int n1 = strlen(str1), n2 = strlen(str2);
    char *s = new char[n1+n2+2]; // +2 for 2 '\0'
    strcpy(s, str1);
    strcpy(s+n1+1, str2);

    char **suffix_array = new char*[n1+n2];
    char *transition_point = s+n1;
    int i = 0;
    for (char *p = s; *p; p++)
        suffix_array[i++] = p;
    for (char *p = transition_point+1; *p; p++)
        suffix_array[i++] = p;
    sort(suffix_array, suffix_array+n1+n2, less_suffix);
    if (debug) {
        cout << "Suffix array: \n";
        for (int i = 0; i < n1+n2; i++)
            cout << suffix_array[i] << endl;
    }

    /*
     * Find the common longest substring.
     */
    int maxlen = 0, maxi = -1;
    for (i = 0; i < n1+n2-1; i++) {
        if ((suffix_array[i] < transition_point && suffix_array[i+1] > transition_point) ||
            (suffix_array[i] > transition_point && suffix_array[i+1] < transition_point)) {
            int len = comlen(suffix_array[i], suffix_array[i+1]);
            if (len > maxlen) {
                maxlen = len;
                maxi = i;
            }
        }
    }
    if (maxi >= 0)
        printf("LCS: %.*s\n", maxlen, suffix_array[maxi]);
    else
        printf("No common substring!\n");
    delete[] suffix_array;
    delete[] s;
    return 0;
}
