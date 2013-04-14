#! /usr/bin/awk -f
#
# Copyright 2010. wbb
#
# Find number of paths between 2 nodes in a directed graph.
# NOTE: a cycle may exist in the graph.  If a path is wholly contained
# in another path they will count as one, not two.
#
# Input file is like this:
#       1 2     # an edge (1, 2)
#       2 3     # an edge (2, 3)
#       n = 3   # number of nodes
#       path 1 2        # find #paths from 1 to 2

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
    print a, "->", b, ":", paths(a, b)
}

function paths(i, j,   s, k)
{
    if (i == j)
        return 1

    # Memoization:  If the answer is already known just return it.
    if ((i, j) in npath)
        return npath[i, j]
    
    s = 0
    for (k = 1; k <= n; k++) {
        if ((i, k) in graph) {
            # Delete the accessed edge in case there is a cycle.
            # I don't want to recount the same path.
            delete graph[i, k]
            s += paths(k, j)
        }
    }
    npath[i, j] = s
    return s
}