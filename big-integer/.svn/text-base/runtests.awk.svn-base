#! /usr/bin/awk -f
#
# Run tests against big-integer.
#
# Usage: ./runtests.awk test.txt

BEGIN {
    if (ARGC != 2) {
        print "Usage: ./runtests.awk test.txt"
        exit 1
    }
}

/ *#/ { next }

NF > 3 {
    left = $1
    op = $2
    right = $3
    result = $4
    if (op == "+") {
        cmd = "echo " left " " right " | ./testadd"
    } else if (op == "-") {
        cmd = "echo " left " " right " | ./testsub"
    } else if (op == "*") {
        cmd = "echo " left " " right " | ./testmul"
    } else if (op == "/") {
        cmd = "echo " left " " right " | ./testdiv"
    } else {
        next
    }
    cmd | getline r
    close(cmd)
    if (r != result) {
        print "error:", $0
        exit 1
    }
}