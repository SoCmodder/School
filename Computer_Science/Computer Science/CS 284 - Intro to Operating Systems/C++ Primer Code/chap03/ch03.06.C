// #include <iostream>

#include <iostream.h>

const int array_size = 7;
int ia1[ array_size ] = { 0, 1, 1, 2, 3, 5, 8 };

/**
 ** 
ia2[ 0 ] : 0
ia2[ 1 ] : 1
ia2[ 2 ] : 1
ia2[ 3 ] : 2
ia2[ 4 ] : 3
ia2[ 5 ] : 5
ia2[ 6 ] : 8
 **
 **/

int main()
{
    int ia2[ array_size ];
    for ( int ix = 0; ix < array_size; ++ix ) {
          ia2[ ix ] = ia1[ ix ];
	  cout << "ia2[ " << ix << " ] : " 
	       << ia2[ ix ] << '\n';
    }

    return 0;
}
