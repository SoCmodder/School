#include <iostream>
using std::cout;

const lineLength = 12; // elements to a line

void putValues( int *ia, int sz )
{
	cout << "( " << sz << " )< ";
	for ( int i = 0; i < sz; ++i )
	{
		if ( i % lineLength == 0 && i )
			cout << "\n\t"; // line filled

		cout << ia[ i ];

		// separate all but last element
		if ( i % lineLength != lineLength-1 && 
		     i != sz-1 )
			cout << ", ";
	}
	cout << " >\n";
}
