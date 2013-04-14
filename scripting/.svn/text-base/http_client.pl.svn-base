#! /usr/bin/perl

use warnings;
use strict;
use IO::Socket::INET;

if (scalar(@ARGV) != 1) {
    die "Usage: $0 URI";
}

my ($host, $port, $path) = ('', '', '');
if ($ARGV[0] =~ m@(http://)?([^/:]+)(:([0-9]+))?(.*)@) {
    $host = $2;
    if ($4) {
        $port = $4;
    } else {
        $port = 80;
    }
    if ($5) {
        $path = $5;
    } else {
        $path = '/';
    }
} else {
    die "URI is invalid";
}
print "host: $host\n";
print "port: $port\n";
my $sock = new IO::Socket::INET(
    PeerAddr => $host,
    PeerPort => $port,
    Proto => "tcp") or die $!;
my $request = "GET $path HTTP/1.1\n"
    . "Host: $host\n"
    . "Connection: close\n"
    . "\r\n";
print "============================================================\n";
print "HTTP request sent: \n$request";
print "============================================================\n";
print $sock $request;
$| = 1;
$sock->autoflush();
while (<$sock>) {
    print;
}
print "\n";
close($sock);
