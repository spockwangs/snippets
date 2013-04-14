#!/bin/bash
#
# Count lines of all text files in a directory.
#
# Usage: lines [ dir ]
#
# Bug
#   It is a litten slower for a directory with huge text files.

DIR=${1:-$(pwd)}
sum=0

for each in $(find "$DIR" -type f | xargs file | grep "text" | awk 'BEGIN {
    FS=":" } { print $1 }'); do
    # echo -n $each
    lines=$(cat "$each" | wc -l)
    (( sum += lines ))
    # echo ": $lines"
done

echo Total lines: $sum

