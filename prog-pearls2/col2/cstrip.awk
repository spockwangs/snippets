#! /usr/bin/awk -f
#
# Copyright (c) 2010 wbb.
#
# Strip C-style comments in a C source file.
#
# FSM
#   state input next output
#   NORMAL ' SINGLE '
#   NORMAL " DOUBLE "
#   NORMAL / BEGIN
#   NORMAL . NORMAL .
#   SINGLE ' NORMAL '
#   SIGNLE \ ESCAPE1 \
#   SINGLE . SINGLE .
#   DOUBLE " NORMAL "
#   DOUBLE \ ESCAPE2 \
#   DOUBLE . DOUBLE .
#   BEGIN * COMMENT
#   BEGIN . NORMAL /.
#   ESCAPE1 . SINGLE .
#   ESCAPE2 . DOUBLE .
#   COMMENT * END
#   COMMENT . COMMENT
#   END / NORMAL SPACE
#   END . COMMENT
# . represents any character not matched.

BEGIN {
    trans["NORMAL", "'"] = "SINGLE"
    out["NORMAL", "'"] = "'"
    trans["NORMAL", "\""] = "DOUBLE"
    out["NORMAL", "\""] = "\""
    trans["NORMAL", "/"] = "BEGIN"
    out["NORMAL", "/"] = 0
    trans["NORMAL", "."] = "NORMAL"
    out["NORMAL", "."] = "."
    trans["SINGLE", "'"] = "NORMAL"
    out["SINGLE", "'"] = "'"
    trans["SINGLE", "\\"] = "ESCAPE1"
    out["SINGLE", "\\"] = "\\"
    trans["SINGLE", "."] = "SINGLE"
    out["SINGLE", "."] = "."
    trans["DOUBLE", "\""] = "NORMAL"
    out["DOUBLE", "\""] = "\""
    trans["DOUBLE", "\\"] = "ESCAPE2"
    out["DOUBLE", "\\"] = "\\"
    trans["DOUBLE", "."] = "DOUBLE"
    out["DOUBLE", "."] = "."
    trans["BEGIN", "*"] = "COMMENT"
    out["BEGIN", "*"] = 0
    trans["BEGIN", "."] = "NORMAL"
    out["BEGIN", "."] = "/."
    trans["ESCAPE1", "."] = "SINGLE"
    out["ESCAPE1", "."] = "."
    trans["ESCAPE2", "."] = "DOUBLE"
    out["ESCAPE2", "."] = "."
    trans["COMMENT", "*"] = "END"
    out["COMMENT", "*"] = 0
    trans["COMMENT", "."] = "COMMENT"
    out["COMMENT", "."] = 0
    trans["END", "/"] = "NORMAL"
    out["END", "/"] = " "
    trans["END", "."] = "COMMENT"
    out["END", "."] = 0
    s = "NORMAL"
    FS = ""                     # treat each character as a field
    RS = "\0"                   # treat the file as a single record
}

{
    for (i = 1; i <= NF; i++) {
        if (s SUBSEP $i in trans) {
            o = out[s, $i]
            s = trans[s, $i]
        } else {
            o = out[s, "."]
            s = trans[s, "."]
        }
        if (o == ".") {
            printf("%s", $i)
        } else if (o == "/.") {
            printf("/%s", $i)
        } else if (o == 0) {
            # print nothing
        } else {
            printf("%s", o)
        }
    }
}

END {
    if (s != "NORMAL") {
        print "error: syntax error"
    }
}
            