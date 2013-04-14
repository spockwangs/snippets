#! /usr/bin/awk -f
#
# FSM simulator, adapted from column 2 of "More Programming Pearls".

run == 0 {
    if ($1 == "trans") {
        run = 1
        s = $2
    } else {
        trans[$1, $2] = $3
        out[$1, $2] = $4
    }
}

run == 1 {
    if ($1 != 0 || $1 != 1) {
        print NR, ": bad input:", $1
        exit 1
    }
    print out[s, $1]
    s = trans[s, $1]
}
