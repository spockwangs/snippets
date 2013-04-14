#! /usr/bin/awk -f
#
# Select, column 3 of "More Programming Pearls".

function select(l, u, k,   i, m)
{
    if (l < u) {
        print l, u
        swap(l, l+int((u-l+1)*rand()))
        m = l
        comps = comps + u-l
        for (i = l+1; i <= u; i++)
            if (x[i] < x[l])
                swap(++m, i)
        swap(l, m)
        if (m < k)
            select(m+1, u, k)
        else if (m > k)
            select(l, m-1, k)
    }
}

# NOTE: Bug in this funciton.
function select2(k,   l, u, i, m)
{
    l = 1
    u = n
    while (l < u) {
        print l, u
        swap(l, l+int((u-l+1)*rand()))
        m = l
        for (i = l+1; i <=u; i++)
            if (x[i] < x[l])
                swap(++m, i)
        swap(l, m)
        if (m < k)
            l = m+1
        else if (m > k)
            u = m-1
    }
}

function swap(i, j,   t)
{
    t = x[i]
    x[i] = x[j]
    x[j] = t
}

$1 == "fill"  { n = $2; for (i = 1; i <= n; i++) x[i] = rand() }
$1 == "n"     { n = $2 }
$1 == "x"     { x[$2] = $3 }
$1 == "print" { for (i = 1; i <= n; i++) print "   ", x[i] }
$1 == "sel"   {
    comps = 0
    select2($2)
    print "  compares:", comps
    print "  compares/n:", comps/n
    for (i = 1; i < k; i++)
        if (x[i] > x[k])
            print i
    for (i = k+1; i <= n; i++)
        if (x[i] < x[k])
            print i
}
