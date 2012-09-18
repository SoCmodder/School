// Section 7.3.4
// $ CC putval3.cpp main3_4.cpp

/*
  ( 1 )< 23 >
  ( 2 )< 15, 5 >
*/

#include <vector>
using std::vector;

// defined in putval3.C
void putValues( const vector<int> & );

int main() {
	int i = 23, j[ 2 ] = { 15, 5 };
	// assign to i and j some values

	vector<int> vec1(1); // create a vector of 1 element
	vec1[0] = i;
	putValues( vec1 );

	vector<int> vec2;    // create an empty vector
	// add elements to vec2
	for ( int ix = 0;
	      ix < sizeof( j ) / sizeof( j[0] );
	      ++ix )
		// vec2[ix] == j[ix]
		vec2.push_back( j[ix] );
	putValues( vec2 );

	return 0;
}
