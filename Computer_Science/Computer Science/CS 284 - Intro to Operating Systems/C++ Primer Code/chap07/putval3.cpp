#include <iostream>
using std::cout;

#include <vector>
using std::vector;

const lineLength = 12; // elements to a line

void putValues( const vector<int>& vec )
{
	cout << "( " << vec.size() << " )< ";
	for ( int i = 0; i < vec.size(); ++i ) {

		if ( i % lineLength == 0 && i )
			cout << "\n\t"; // line filled

		cout << vec[ i ];

		// separate all but last element
		if ( i % lineLength != lineLength-1 &&
	        i != vec.size()-1 )
			cout << ", ";
	}
	cout << " >\n";
}
