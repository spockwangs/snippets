#!/usr/bin/awk -f
#
# fmt.awk -- format text into 60-char lines
#

/./ { 
    for (i = 1; i <= NF; i++)
        addword($i)
}

/^$/ { printline(); print "" }
END { printline() }

function addword(w) {
    if (length(line) + length(w) + 1> 60)   # +1 for a space
        printline()
    line = line space w
    space = " "
}

function printline() {
    if (length(line) > 0)
        print line
    line = space = ""
}
