// Section 7.3.3
// $ CC main3_3c.cpp

/*
  ( 1 )< 23 >
  ( 2 )< 15, 5 >
*/

#include <iostream>
using std::cout;

const lineLength = 12; // elements to a line

template <class Type>
	void putValues( Type *ia, int sz )
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

int main() {
	int i = 23, j[ 2 ] = { 15, 5 };
	putValues( &i, 1 );
	putValues( j, 2 );
	return 0;
}
