// Section 7.9.5
// $ CC compare.cpp sort.cpp main9_5.cpp

/*
	a
        drizzle
        falling
        left
        light
        museum
        the
        they
        was
        when
*/

#include <iostream>
using std::cout;

#include <string>
using std::string;

// defined in compare.C 
int lexicoCompare( const string &, const string & );
int sizeCompare( const string &, const string & );

typedef int (*PFI)( const string &, const string & );
// defined in sort.C
void sort( string *, string *, PFI=lexicoCompare );

string as[10] = { "a", "light", "drizzle", "was", "falling",
                  "when", "they", "left", "the", "museum" };

int main() {
	// call sort() which uses the default argument for compare
	sort( as, as + sizeof(as)/sizeof(as[0]) - 1 );

	// display the result of the sorted array
	for ( int i = 0; i < sizeof(as)/sizeof(as[0]); ++i )
		cout << "\t" << as[ i ].c_str() << "\n";
}
