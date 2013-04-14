/*
 * Copyright (c) 2010. Wang Bingbing.
 *
 * div.cc -- Calculate divisions of two integers.
 *
 * Do divisions of two integers and print the quotations.  If the dividend
 * is not divisible by the divider print its repetend.
 *
 * who: 王兵兵 (wbbtiger@gmail.com)
 * when: 2010-10-01 17:26:08
 */
 
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Divide b by a and print its quotation and repetend if any.
 */
void divide(int b, int a)
{
    vector<int> residues, quotes;
    vector<int>::const_iterator ci;
    int r, q;

    q = b/a;
    r = b%a;
    cout << q << ".";
    while (r != 0) {
        ci = find(residues.begin(), residues.end(), r);
        if (ci != residues.end()) {
            // Found the repetend.
            break;
        }
        residues.push_back(r);
        q = r*10/a;
        quotes.push_back(q);
        r = r*10 - a*q;
    }
    if (r == 0)
        ci = residues.end();

    vector<int>::const_iterator ri, qi;
    for (ri = residues.begin(),  qi = quotes.begin(); 
         ri != ci; ++ri, ++qi) {
        cout << *qi;
    }

    // Print the repetend.
    if (ci != residues.end()) {
        cout << "<";
        for (; qi != quotes.end(); ++qi) {
            cout << *qi;
        }
        cout << ">";
    }
    cout << endl;
}

int main()
{
    int a, b;
    while (cin >> a >> b) 
        divide(a, b);
    return 0;
}
