#! /usr/bin/awk -f
#
# Exercise 5a of column 2.
#
# Write a program to build and traverse a tree.
# Assume the tree is presented as a sequence (node, left child, right
# child) triples, one tripe per line.

NF == 3 {
    bin_tree[$1, "left"] = $2
    bin_tree[$1, "right"] = $3
}

NF == 2 {
    if ($1 == "root") {
        root = $2
        valid = 1
    } else {
        print "error:", $0
        exit 1
    }
}

END {
    # Print the tree.
    if (valid)
        print_tree(root, 0)
    else {
        print "error: no root"
        exit 1
    }
}

# Print a binary tree rooted at node.
# Assume that node exists but its children may not exist.
function print_tree(node, depth)
{
    printf("%*s\n", depth+1, node)
    if (node SUBSEP "left" in bin_tree)
        print_tree(bin_tree[node, "left"], depth+2)
    if (node SUBSEP "right" in bin_tree)
        print_tree(bin_tree[node, "right"], depth+2)
}