#! /usr/bin/awk -f
#
# Copyright 2010. wbb
#
# Find #paths between all 2 nodes in a directed graph.  Graph may have
# cycles.
#
# See paths.awk for details on the format of input files.

NF == 2 {
    graph[$1, $2] = 1
}

{
    if ($1 == "n")
        n = $3
    if ($1 == "path") {
        a = $2
        b = $3
    }
}

END {
    paths(graph)
    print a, "->", b, ":", D[a, b]
}

# Find #paths between all 2 nodes.  The algorithm is like Floyd-Warshall
# algorithm.  The results are in matrix D.
function paths(g,   k, i, j)
{
    for (i in g)
        D[i] = g[i]

    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                D[i, j] += D[i, k] * D[k, j]
            }
        }
    }
}