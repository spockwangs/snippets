#!/bin/sh
#
# Count lines of all text files in a directory.
#
# Usage: lines [ dir ]

lines()
{
    local sum=0

    for each in `find "$1" -maxdepth 1`; do
        if [ -d "$each" -a "$each" != "$1" ]; then
            lines "$each"
            sum=$((sum + $?))
        elif [ -f "$each" ]; then
            if file "$each" | grep text >/dev/null; then
                # echo -n "$each: "
                nlines=$(cat "$each" | wc -l)
                # echo "$nlines"
                : $((sum += nlines))
            fi
        fi
    done
    return $sum
}

DIR=${1:-$(pwd)}

lines "$DIR"; echo Total lines: $?
