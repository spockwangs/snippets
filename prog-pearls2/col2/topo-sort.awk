#! /usr/bin/awk -f
#
# Topological sort, Column 2 of "More Programming Pearls".
#
# Assume that the graph is presented as a sequence of (predecessor,
# successor) pairs, one pair per line.

{
    if (NF != 2) {
        print "error:", $0
        exit 1
    }
    
    ++predct[$2]
    predct[$1] = predct[$1]
    succlist[$1, ++succcnt[$1]] = $2
}

END {
    qlo = 1
    for (i in predct) {
        n++
        if (predct[i] == 0)
            q[++qhi] = i
    }
    while (qlo <= qhi) {
        t = q[qlo++]
        print t
        for (i = 1; i <= succcnt[t]; i++) {
            s = succlist[t, i]
            if (--predct[s] == 0)
                q[++qhi] = s;
        }
    }
    if (qhi != n) {
        print "topological sort error: cycle in input"
        printf("The cycle is: ")
        print_cycle()
    }
}

# Use DFS to find cycles.
function dfs(s, i, t)
{
    cycle[++cnt] = s
    idx[s] = cnt
    color[s] = "GRAY"
    for (i = 1; i <= succcnt[s]; i++) {
        t = succlist[s, i]
        if (! (t in color)) {
            if (dfs(t))
                return 1
        } else if (t in color && color[t] == "GRAY") {
            for (i = idx[t]; i <= length(cycle); i++)
                printf("%s ", cycle[i])
            print ""
            return 1
        }
    }
    color[s] = "BLACK"
    return 0
}
            
function print_cycle(i)
{
    for (i in predct) {
        if (predct[i] != 0 && ! (i in color)) {
            delete cycle
            cnt = 0
            if (dfs(i))
                return
        }
    }
}