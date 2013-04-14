#!/usr/bin/perl 

use strict;

my (%suffixes, $w1, $w2, %nsuffix, $i);
$w1 = $w2 = "\n";
while (<>) {
    split;
    for ($i = 0; $i < $#_; $i++) {
        $suffixes{$w1, $w2, ++$nsuffix{$w1, $w2}} = $_[$i];
        $w1 = $w2;
        $w2 = $_[$i];
    }
}

$suffixes{$w1, $w2, ++$suffixes{$w1, $w2}} = "\n";
$w1 = $w2 = "\n";
for ($i = 0; $i < 1000; $i++) {
    my $n = int(rand() * $nsuffix{$w1, $w2})+1;
    my $w = $suffixes{$w1, $w2, $n};
    if ($w eq "\n") {
        exit;
    }
    print $w . "\n";
    $w1 = $w2;
    $w2 = $w;
}
