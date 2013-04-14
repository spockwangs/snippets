#!/usr/bin/awk -f
#
# cproto.awk -- generate function prototype declarations automatically
#
# Bug
#   This program assumes the souce file is valid and can only deal with
#   the following forms of function definition:
#
#   /* the return-type and function argument list are at the same line, and
#      the left brace follows at next line */ 
#   return-type fun-name(args, ... )
#   { ...  }
#
#   or
#
#   /* the return-type and function name and left paren is at the same
#      line, the argument list strap multiple lines and the left brace follows
#      at next line */
#   return-type fun-name(
#       args,
#       ...  )
#   {
#       ...
#   }

# print the name of souce file
BEGIN {
    printf("/* %s */\n", ARGV[1])
}

# skip preprocessor directive
/ *#/ {
    next
}

# skip function declaration
/\(.*\) *; *$/ {
    next
}

/^[^ \t].*\(/, /^{/ {
    if ($0 !~ /^{/)
        fun_dec = fun_dec $0
    next
}

/./ {
    if (fun_dec !~ /^$/) {
        printf("%s;\n", fun_dec)
        fun_dec = ""
    }
}
