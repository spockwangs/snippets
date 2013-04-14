#! /usr/bin/awk -f
#
# Binary search, column 3 of "More Programming Pearls".
# NOTE: There is a bug in following code.

function bsearch(t, l, u, m)
{
    # l, u and m are local variables.

    l = 1; u = n
    while (l <= u) {
        m = int((l+u)/2)
        print "  ", l, m, u
        if (x[m] < t) l = m
        else if (x[m] > t) u = m
        else return m
    }
    return 0
}

$1 == "fill"   { n = $2; for (i = 1; i <= n; i++) x[i] = 10*i }
$1 == "n"      { n = $2; }
$1 == "x"      { x[$2] = $3 }
$1 == "print"  { for (i = 1; i <= n; i++) print i ":\t" x[i] }
$1 == "search" { t = bsearch($2); print "result:", t }