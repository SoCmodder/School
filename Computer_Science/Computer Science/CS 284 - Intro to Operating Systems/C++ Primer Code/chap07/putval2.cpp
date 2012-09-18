#include <iostream>
using std::cout;

void putValues( int (&ia)[10] )
{
	cout << "( 10 )< ";
	for ( int i = 0; i < 10; ++i ) {
		cout << ia[ i ];

		// separate all but last element
		if ( i != 9 )
			cout << ", ";
	}
	cout << " >\n";
}
