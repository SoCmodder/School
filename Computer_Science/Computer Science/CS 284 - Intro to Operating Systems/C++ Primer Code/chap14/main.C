#include "Account.h"
#include <utility>
#include <iostream.h>
#include <iomanip.h>

/**
 **
 [ 0 ] { Acct# 1000001 -- Mr. Happy       Balance: $7000.49 }
 [ 1 ] { Acct# 1000002 -- Mr. Grumpy      Balance: $1000.55 }
 [ 2 ] { Acct# 1000003 -- Mr. Doc         Balance: $3000.72 }
 [ 3 ] { Acct# 1000004 -- Mr. Sleepy      Balance: $1999.99 }
 [ 4 ] { Acct# 1000005 -- Mr. Sneezy      Balance: $4100.54 }
 [ 5 ] { Acct# 1000006 -- Mr. Bashful     Balance: $8500.08 }
 [ 6 ] { Acct# 1000007 -- Mr. Dopey       Balance: $1000.01 }
 **
 **/

int main()
{
    vector< value_pair > init_values;

    init_values.push_back( make_pair( string( "Mr. Happy" ),   7000.49 ));
    init_values.push_back( make_pair( string( "Mr. Grumpy" ),  1000.55 ));
    init_values.push_back( make_pair( string( "Mr. Doc" ),     3000.72 ));
    init_values.push_back( make_pair( string( "Mr. Sleepy" ),  1999.99 ));
    init_values.push_back( make_pair( string( "Mr. Sneezy" ),  4100.54 ));
    init_values.push_back( make_pair( string( "Mr. Bashful" ), 8500.08 ));
    init_values.push_back( make_pair( string( "Mr. Dopey" ),   1000.01 ));

    Account *pact = Account::init_heap_array( init_values );

    for ( int ix = 0; ix < 7; ++ix )
    {
	  cout << "[ " << ix << " ] { Acct# "
	       << pact[ ix ].account() << " -- "
	       << pact[ ix ].name() << "\t Balance: $"
	       << setprecision( 7 )
	       << pact[ ix ].balance() << " }\n";
    }

    Account::dealloc_heap_array( pact, init_values.size() );
}
