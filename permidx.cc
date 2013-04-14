/*
 * Copyright (c) 2010. wbb
 *
 * Date: 2010-12-27
 *
 * Generate a permutated index from standard input.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

using namespace std;

bool next_rotation(string& s);
bool string_cmp(const string& s1, const string& s2);
void unrotate(const string& s, string::size_type maxlen);

int main()
{
    vector<string> idx;
    string str;
    string::size_type maxlen = 0;
    while (getline(cin, str)) {
        // Trim trailing spaces.
        int i;
        i = str.size();
        while (i > 0 && isspace(str[i-1]))
            --i;
        str = str.substr(0, i);
        maxlen = max(maxlen, str.size());
        str += "$";

        // Add rotations of a input line.
        string s = str;
        idx.push_back(s);
        while (next_rotation(s))
            idx.push_back(s);
    }
    sort(idx.begin(), idx.end(), string_cmp);
    for (vector<string>::const_iterator ci = idx.begin();
            ci != idx.end(); ++ci) {
        unrotate(*ci, maxlen);
    }
    return 0;
}

bool next_rotation(string& s)
{
    string::size_type i, j, k, size;
    size = s.size();
    i = 0;
    while (i < size && isspace(s[i]))
        ++i;
    j = i;
    while (j < size && isalpha(s[j]))
        ++j;
    if (s[j] == '$')
        return false;

    k = j;
    while (k < size && isspace(s[k]))
        ++k;
    s = s.substr(k, size-k) + " " + s.substr(i, j-i);
    return true;
}

bool string_cmp(const string& s1, const string& s2)
{
    string::size_type i, size1, size2;
    i = 0;
    size1 = s1.size();
    size2 = s2.size();
    while (i < size1 && i < size2) {
        if (isupper(s1[i]) && islower(s2[i]))
            return false;
        if (islower(s1[i]) && isupper(s2[i]))
            return true;
        if (s1[i] != s2[i])
            return s1[i] < s2[i];
        ++i;
        ++i;
    }
    return size1 < size2;
}

void unrotate(const string& s, string::size_type maxlen)
{
    string::size_type i, j, size;
    string::const_iterator ci = find(s.begin(), s.end(), '$');
    if (ci == s.end())
        throw logic_error("Should not happen!");
    i = ci-s.begin();
    j = i+1;
    size = s.size();
    while (j < size && isspace(s[j]))
        ++j;

    streamsize save_width = cout.width(maxlen);
    cout << s.substr(j, size-j) << "   "
        << setw(save_width) << s.substr(0, i) << endl;
}
