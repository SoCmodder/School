// in Section 7.9.3
// $ CC min.cpp

/*
  Direct call: min: 2
  Indirect call: min: 2
*/

#include <iostream>
using std::cout;
using std::endl;

int min( int*, int );
int (*pf)( int*, int ) = min;

const int iaSize = 5;
int ia[ iaSize ] = { 7, 4, 9, 2, 5 };

int main() {
	cout << "Direct call: min: "
	     << min( ia, iaSize ) << endl;

	cout << "Indirect call: min: " 
	     << pf( ia, iaSize ) << endl;

	return 0;
}

int min( int* ia, int sz ) {
	int minVal = ia[ 0 ];
	for ( int ix = 1; ix < sz; ++ix )
		if ( minVal > ia[ ix ] )
			minVal = ia[ ix ];
	return minVal;
}
