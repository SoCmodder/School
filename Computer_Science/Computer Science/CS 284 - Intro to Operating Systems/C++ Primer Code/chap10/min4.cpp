// Section 10.3
// $ CC min4.cpp

/*
  minimum value is: 3
*/

#include "Array.h"
#include "ArrayRC.h"
#include "Array.cpp"
#include "ArrayRC.cpp"

template <class Type>
        Type min4( Array<Type>& array )
{
        Type min_val = array[0];
        for ( int i = 1; i < array.size(); ++i )
                if ( array[i] < min_val )
                        min_val = array[i];

        return min_val;
}

int main() {

	static int ia[] = { 12,7,14,9,128,17,6,3,27,5 };
        ArrayRC<int> ia_rc( ia, sizeof(ia)/sizeof(int) );
	
        cout << "minimum value is: " << min4( ia_rc ) << '\n';
}

