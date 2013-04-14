#! /usr/bin/perl
#
# http_proxy.pl -- A simple HTTP proxy
#
# It can be used to snoop the contents of HTTP requests and responses.
# Also it can be used to do testing.
#
# Usage: http_proxy.pl -p local_port host:port

use warnings;
use strict;
use IO::Socket::INET;

my $server_host = "google.com";
my $server_port = 80;
my $sock = new IO::Socket::INET(
    LocalHost => "0.0.0.0",
    LocalPort => 8080,
    Proto => "tcp",
    Reuse => 1,
    Listen => 10) or die "$!";

for (;;) {
    my $client = $sock->accept();
    my $server = new IO::Socket::INET(
        PeerAddr => $server_host,
        PeerPort => $server_port,
        Proto => "tcp") or die "$!";
    my $r = fork();
    if ($r < 0) {
        die $!;
    } elsif ($r == 0) {
        # child: client -> server
        my $buf;
        for (;;) {
            my $err = $client->recv($buf, 10, 0);
            if (!defined($err)) {
                last;
            }
            if ($buf eq '') {
                print "Connection closed by the client\n";
                last;
            }
            print "from client: \n$buf";            

            # try to send $buf
            my $nleft = length($buf);
            while ($nleft > 0) {
                my $nsent = $server->send($buf, 0) || exit(1);
                $nleft -= $nsent;
                $buf = substr($buf, $nsent);
            }
        }
        exit(0);
    } else {
        # parent: server -> client
        my $buf;
        for (;;) {
            my $err = $server->recv($buf, 8096, 0);
            if (!defined($err)) {
                last;
            }
            if ($buf eq '') {
                # closed by the server
                print "Connection closed by the server\n";
                last;
            }
            print "from server: \n$buf";
            
            # try to send $buf to client
            my $nleft = length($buf);
            while ($nleft > 0) {
                my $nsent = $client->send($buf, 0) || last;
                $nleft -= $nsent;
                $buf = substr($buf, $nsent);
            }
        }
    }
    shutdown($client, 2);
    shutdown($server, 2);
}    
