// Section 10.3
// $ CC min2.cpp

/*
  minimum of ai is: 8
*/

#include <iostream>
using std::cout;
using std::endl;

template <class Type>
        // the first parameter is a Type*
        Type min2( Type* array, int size )
{
        Type min_val = array[0];
        for ( int i = 1; i < size; ++i )
                if ( array[i] < min_val )
                        min_val = array[i];

        return min_val;
}

int ai[4] = { 12, 8, 73, 45 };

int main() {
        int size = sizeof (ai) / sizeof (ai[0]);

        // ok: array-to-pointer conversion
	cout << "minimum of ai is: " << min2( ai, size ) << endl;
}
