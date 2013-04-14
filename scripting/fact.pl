#!/usr/bin/perl -w
# 
# Usage: fact.pl number

use warnings;
use strict;

sub fact()
{
    my $result = 1;
    for (; $_[0] > 1; $_[0]--) {
        $result *= $_[0];
    }
    return $result;
}

print &fact($ARGV[0]), "\n";
