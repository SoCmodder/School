// Section 7.1
// $ CC gcd.C main1.C

#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// definition in gcd.C
int gcd( int, int );

inline int abs( int iobj ) {
	return( iobj < 0 ? -iobj : iobj );
}

inline int min( int v1,int v2 ) {
	return( v1 < v2 ? v1 : v2 );
}

int main()
{
	// get values from standard input
	cout << "Enter first value: ";
	int i;
	cin >> i;
	if ( !cin ) {
		cerr << "!? Oops: input error - Bailing out!\n";
		return -1;
	}

	cout << "Enter second value: ";
	int j;
	cin >> j;
	if ( !cin ) {
		cerr << "!? Oops: input error - Bailing out!\n";
		return -2;
	}

	cout << "\nmin: " << min( i, j ) << endl;
	i = abs( i );
	j = abs( j );
	cout << "gcd: " << gcd( i, j ) << endl;
	return 0;
}

