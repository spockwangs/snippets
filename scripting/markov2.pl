#! /usr/bin/perl
#
# markov.pl

use strict;
use warnings;
use constant NONWORD => "";
use Getopt::Std;

my %map;        # map prefix to suffix
my @prefix;
my $N;          # number of prefixes
my %options;

getopts("n:", \%options) or die "Usage: $0 [-n nprefix] [ files ... ]\n";
$N = $options{n} || 2;

foreach (1..$N) {
    push @prefix, NONWORD;
}
while (<>) {
    my @words = split;
    foreach (@words) {
        $map{"@prefix"} = [] if (!exists($map{"@prefix"}));
        push @{$map{"@prefix"}}, $_;
        shift @prefix;
        push @prefix, $_;
    }
}
$map{"@prefix"} = [] if (!exists($map{"@prefix"}));
push @{$map{"@prefix"}}, NONWORD;

my $w;
@prefix = ();
foreach (1..$N) {
    push @prefix, NONWORD;
}
for (;;) {
    my $array_r = $map{"@prefix"};
    die "Can't happen!\n" if (!defined($array_r));
    $w = $$array_r[int(rand(@$array_r))];
    last if ($w eq NONWORD);
    print $w, " ";
    shift @prefix;
    push @prefix, $w;
}
print "\n";
