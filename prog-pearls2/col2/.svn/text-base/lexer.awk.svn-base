#! /usr/bin/awk -f
#
# Copyright (c) 2010 wbb.
#
# A lexical analyzer for C.  FSM is in "clexer.txt".
#
# Usage: ./lexer.awk file

BEGIN {
    if (ARGC != 2) {
        print "Usage: lexer.awk file"
        exit 1
    }
    
    # Init FSM from a file.
    while (getline <"./clexer.txt") {
        if ($0 ~ /^#/)
            continue
        # Start state.
        if (NF == 2 && $1 == "start")
            s = $2
        if (NF >= 4) {
            if ($1 SUBSEP $2 in trans || $1 SUBSEP $2 in out) {
                print "error in fsm.txt:", $0
                exit 1
            }
            trans[$1, $2] = $3
            out[$1, $2] = $4
        }
        if (NF == 5)
            how[$1, $2] = $5
    }

    # start state
    s = "NORMAL"
 
    # Treat each character as a single field.
    FS = ""
    RS = "\0"
}

{
    for (i = 1; i < NF; i++) {
        if (s SUBSEP $i in trans) {
            input = $i
        } else if (s SUBSEP "d" in trans && isdigit($i)) {
            input = "d"
        } else if (s SUBSEP "a" in trans && isalnum($i)) {
            input = "a"
        } else {
            input = "o"
        }
        o = out[s, input]
        if (s SUBSEP input in how)
            h = how[s, input]
        else
            h = 0
        s = trans[s, input]
        
        if (o == ".") {
            str = str $i
        } else if (o == "p") {
            if (str != "") {
                print str
                str = ""
            } else
                print $i
        } else if (o == "a") {
            print str $i
            str = ""
        } else if (o == 0) {
            # do nothing
        } else if (o == "SPACE") {
            print "\" \""
        } else {
            print o
        }

        if (h == "u")
            --i
    }
}

function isdigit(c) {
    if (index("0123456789", c))
        return 1
    else
        return 0
}

function isalnum(c) {
    return match(c, "[a-zA-Z0-9]");
}