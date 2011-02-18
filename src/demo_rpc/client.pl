use strict;
use warnings;

use RPC::XML;
use RPC::XML::Client;

print "* Initialiseren client\n";
my $client = RPC::XML::Client->new('https://127.0.0.1:8080/RPC');

print "* Methode aanroepen\n";
my $resp = $client->send_request('testFunc');

use Data::Dumper;
print Dumper($resp);

