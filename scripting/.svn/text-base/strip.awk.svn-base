#!/usr/bin/awk -f
#
# strip.awk -- strip c-style comments
#
# Bug
#   It cannot strip the comments surrouned by codes.  And it may strip the
#   beginning comments or ending comments and other codes at the same line.

/^ *\/\*.*\*\/ *$/ {
    # a single line of comment
    next
}

/^ *\/\*/, /\*\/ *$/ {
    next
}

{ print $0 }

