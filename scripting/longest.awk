#!/usr/bin/awk -f
#
# longest.awk -- print longest line and its length

length($0) > max { max = length($0); line = $0 }
END { print max, line }
