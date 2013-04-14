/*
 * micro -- A Microsoft 2010 internship test problem 
 *
 * Time-stamp: <2010-07-24 13:37:34 wbb>
 *
 * PROBLEM DESCRIPTION
 *   Given some relations of symbols read from a file, determine if
 *   the info is sufficient to determine the sequence of the symbols.
 *
 *   The input file consists of multiple lines.  Each line is like
 *   this:
 *      <key> [<symbol1> <symbol2> ... ]
 *   The first symbol is the key and the subsequent symbols are all
 *   greater than the key.  So given this line:
 *      A B C
 *   we can see A < B and A < C but we cannot determine the sequence
 *   of B and C.
 *
 *   The words after "//" are comments which will not appear in the
 *   input file.
 *   Sample input1:
 *      A B C       // A < B, A < C
 *      B C         // B < C
 *      C
 *   So we can see A < B < C and the sequence can be determined.
 *
 *   Sample input2:
 *      A B     // A < B
 *      B A     // B < A, contradict with the first line
 *   The input file has a contradiction and the sequence cannot be
 *   determined.
 *
 * PROGRAM DESCRIPTION
 *   In this program, the info we get from the input file is
 *   represented in a directed graph which is stored in a matrix.  If
 *   A < B then there is an edge from node A to node B.  To determine
 *   the relations of any 2 symbols is equivalent to compute the
 *   transitive closure of the graph.  The contradiction in the input
 *   file is equivalent to a cycle in the graph, which can be checked
 *   by DFS or transitive closure.  We can compute the transitive
 *   closure using DFS or Floyd-Warshall algorithm.
 *
 * COMPILE
 *   g++ -W -Wall -pedantic -std=c++98 micro.cpp
 */

#include <iostream>
#include <cctype>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

const bool debug = false;

typedef char Symbol;
typedef vector<vector<int> > Relation;

const char *CLAIM_FAILURE = "Sorted sequence cannot be determined.\n";
const char *CLAIM_SUCCESS = "Sorted sequence determined.\n";


void print_relations(const Relation& relations);

/*
 * next_symbol --
 *   Read next symbol from 'in'.  If any in the same line return true,
 *   otherwise return false.
 */
bool next_symbol(istream& in, Symbol *p)
{
    Symbol c;
    while (in.get(c)) {
        if (isalpha(c)) {
            *p = c;
            return true;
        } else if (c == '\n')
            return false;
    }
    return false;
}


enum Color { WHITE, GRAY, BLACK };


/*
 * dfs_visit --
 *   Compute which nodes can be reached from 's' using DFS and by the
 *   way check if a cycle exists.
 */
bool dfs_visit(Relation& relations, vector<Color>& colors, int s, int u)
{
    colors[u] = GRAY;
    for (int v = 0; (size_t) v < relations[u].size(); v++) {
        if (relations[u][v]) {
            if (colors[v] == WHITE) {
                relations[s][v] = 1;    // there is a path from 's' to 'v'
                if (!dfs_visit(relations, colors, s, v))
                    return false;
            } else if (colors[v] == GRAY)   // A cycle ?
                return false;
        }
    }
    colors[u] = BLACK;
    return true;
}

void dfs_check(Relation& relations)
{
    vector<Color> colors(relations.size());

    /*
     * Compute the transitive closure and check if a cycle exists at
     * the same time.
     */
    for (int u = 0; (size_t) u < relations.size(); u++) {
        fill(colors.begin(), colors.end(), WHITE);
        if (!dfs_visit(relations, colors, u, u)) {
            cout << CLAIM_FAILURE;
            return;
        }
    }

    if (debug) {
        cout << "--------------------\n";
        print_relations(relations);
    }

    /*
     * Given the transitive closure check if we can determine the
     * relaiton of any 2 symbols.
     */
    for (int i = 0; (size_t) i < relations.size(); i++) {
        for (int j = i+1; (size_t) j < relations.size(); j++) {
            if ((relations[i][j] == 0) && (relations[j][i] == 0)) {
                // sequence symbols i and j cannot be determined
                cout << CLAIM_FAILURE;
                return;
            }
        }
    }
    cout << CLAIM_SUCCESS;
}


/*
 * transitive_closure --
 *   Compute the transitive closure of 'relations' using
 *   Floyd-Warshall algorithm.
 *   See p.633 of "Introduction to Algorithms", Second Edition.
 */
void transitive_closure(Relation& relations)
{
    int n = relations.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                relations[i][j] = relations[i][j] || 
                    (relations[i][k] && relations[k][j]);
            }
        }
    }
}


void transitive_closure_check(Relation& relations)
{
    transitive_closure(relations);
    if (debug) {
        cout << "--------------------\n";
        print_relations(relations);
    }

    for (int i = 0; (size_t)i < relations.size(); i++) {
        for (int j = i+1; (size_t) j < relations.size(); j++) {
            if (relations[i][j] == relations[j][i]) {
                // Either a cycle exists between i and j or
                // relations of i and j cannot be determined
                cout << CLAIM_FAILURE;
                return;
            }
        }
    }
    cout << CLAIM_SUCCESS;
}


int main()
{
    Symbol key, c;
    Relation relations;
    map<Symbol, int> sym_idx;

    /*
     * Process the input file.
     */
    while (cin) {
        if (!next_symbol(cin, &key))
            continue;

        sym_idx.insert(pair<Symbol, int>(key, sym_idx.size()));
        relations.resize(max(relations.size(), sym_idx.size()));
        while (next_symbol(cin, &c)) {
            sym_idx.insert(pair<Symbol, int>(c, sym_idx.size()));
            relations[sym_idx[key]].resize(max(relations[sym_idx[key]].size(), sym_idx.size()));
            relations[sym_idx[key]][sym_idx[c]] = 1;
        }
    }
    for (int i = 0; (size_t) i < relations.size(); i++)
        relations[i].resize(relations.size());

    if (debug) {
        for (map<Symbol, int>::const_iterator sym_iter = sym_idx.begin();
                sym_iter != sym_idx.end(); sym_iter++)
            cout << sym_iter->first << " -> " << sym_iter->second << endl;
        print_relations(relations);
    }
    
    transitive_closure_check(relations);    // or dfs_check(relations);

    return 0;
}


void print_relations(const Relation& relations)
{
    for (Relation::const_iterator rela_iter = relations.begin();
            rela_iter != relations.end(); rela_iter++) {
        copy(rela_iter->begin(), rela_iter->end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }
}
