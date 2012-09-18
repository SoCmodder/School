#include <string>
using std::string;

typedef int (*PFI2S)( const string &, const string & );

int lexicoCompare( const string &, const string & );

void sort( string *s1, string *s2,
           PFI2S compare = lexicoCompare )
{
    // stopping condition for recursion
    if ( s1 < s2 ) {
        string elem = *s1;
        string *low = s1;
        string *high = s2 + 1;

        for (;;) {
            while ( compare( *++low, elem ) < 0 && low < s2) ;
            while ( compare( elem, *--high ) < 0  && high > s1) ;

            if ( low < high )
                low->swap(*high);
            else break;
        }  // end, for(;;)

        s1->swap(*high);
        sort( s1, high - 1 );
        sort( high + 1, s2 );
    } // end, if ( s1 < s2 )
}
