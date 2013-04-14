#! /usr/bin/awk -f
#
# Exercise 5d of column 2.

NR == 1 {
    # start symbol
    start = $1
}

NF > 2 {
    ++nalt[$1]
    for (i = 3; i <= NF; i++) {
        if ($i != "|") {
            syntax[$1, nalt[$1], ++nitem[$1, nalt[$1]]] = $i
        } else {
            ++nalt[$1]
        }
    }
}

END {
    srand(systime())
    generate(start)
    print ""
}

function generate(s, n, m, i)
{
    if (! (s in nalt)) {
        # Terminals.
        printf("%s ", s)
        return
    }
    
    n = randint(nalt[s])
    m = nitem[s, n]
    for (i = 1; i <= m; i++) {
        generate(syntax[s, n, i])
    }
}

function randint(n)
{
    return int(n*rand()) + 1
}