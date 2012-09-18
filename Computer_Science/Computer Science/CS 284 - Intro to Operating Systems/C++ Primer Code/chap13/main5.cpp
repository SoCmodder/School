// Section 13.5
// $ CC account.cpp main5.cpp

/*
  Asterix is poorer than Obelix
*/

#include <iostream>
using std::cout;

#include "account.h"

bool limitTest( double limit )
{
        // no Account class objects defined yet
        // ok: call static member function
        return limit <= Account::interest() ;
}

int main() {
        double limit = 0.05;

        if ( limitTest( limit ) )
        {
                // pointer to static class member is
                // declared as ordinary pointer
                void (*psf)(double) = &Account::raiseInterest;
                psf( 0.0025 );
        }

        Account ac1( 5000, "Asterix" );
        Account ac2( 10000, "Obelix" );
        if ( compareRevenue( ac1, &ac2 ) > 0 )
                cout << ac1.owner()
                     << " is richer than "
                     << ac2.owner() << "\n";
        else
                cout << ac1.owner()
                     << " is poorer than "
                     << ac2.owner() << "\n";
        return 0;
}

