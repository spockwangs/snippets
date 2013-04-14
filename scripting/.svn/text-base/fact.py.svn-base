#! /usr/bin/python
# 
# Usage: fact.py n

import sys
import string

def fact(n) :
    r = 1
    if n < 0 :
        print "n should be non-negative"
    else :
        while n > 1 :
            r *= n
            n -= 1
    return r

if len(sys.argv) != 2 :
    print "Usage: %s n" % (sys.argv[0])
    exit(1)
print fact(string.atoi(sys.argv[1]))
