#! /usr/bin/perl
#
# installjar.pl -- Install jar files in your system.
# 
# Usage: installjar.pl [-d dest-dir] [-vt] jar-files ...
#     -d dest-dir   where to install the files
#     -v            print verbose info
#     -t            dry run to test

use strict;
use warnings;
use Getopt::Std;
use Cwd;
use Cwd 'abs_path';

my (%options, $dir, $cwd, $jaroptions);

getopts("d:tv", \%options) && @ARGV > 0
    || die "Usage: $0 [-d dest-dir] [-vt] jar-files ...\n";
$dir = $options{'d'} || ".";
if ($options{t}) {
    $jaroptions = "t";
} else {
    $jaroptions = "x";
}
if ($options{v}) {
    $jaroptions .= "v";
}
$jaroptions .= "f";
die "error: $dir: No such directory!\n" unless -d $dir;

die "The program 'jar' is required and installed in your PATH.\n" unless `which jar`;
foreach (@ARGV) {
    $_ = abs_path($_);
}
foreach (@ARGV) {
    if (!/\.jar$/) {
        print "warning: `$_' is not a .jar file\n";
        next;
    }
    if (! -f) {
        print "warning: `$_' does not exist\n";
        next;
    }
    chdir $dir || die $!;
    system "jar", $jaroptions, "$_";
}
