#! /usr/bin/awk -f
#
# P6 of column 1 in "More Programming Pearls".

BEGIN {
    n = 1000
    x[0] = 2; xc = 1
    print 2
    for (i = 3; i <= n; i++) {
        if (prime(i)) {
            print i
        }
    }
    exit
}

# Test if n is prime.
# Note: i is a local variable.
function prime(n, i) {
    for (i = 0; x[i]*x[i] <= n; i++) {
        if (n % x[i] == 0) {
            return 0
        }
    }
    x[xc++] = n
    return 1
}