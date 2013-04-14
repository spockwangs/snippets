#!/usr/bin/awk -f
#
# reverse.awk -- reverse a file

{ lines[NR] = $0 }
END { 
    for (i = NR; i > 0; i--)
        print lines[i]
}
