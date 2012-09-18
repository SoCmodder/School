// Section 10.1
// $ CC template.cpp

/*

minimum of 10 and 20 is: 10
minimum of 10.3 and 20.6 is: 10.3

*/

#include <iostream>
using std::cout;
using std::endl;

template <class Type>
        Type min( Type a, Type b ) {
                return a < b ? a : b;
}

int main() {
        // ok: int min( int, int );
	cout << "minimum of 10 and 20 is: " << min( 10, 20 ) << endl;

        // ok: double min( double, double );
	cout << "minimum of 10.3 and 20.6 is: " << min( 10.3, 20.6 ) << endl;

        return 0;
}
