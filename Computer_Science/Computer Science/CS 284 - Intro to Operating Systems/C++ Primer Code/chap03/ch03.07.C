// #include <iostream>
#include <iostream.h>

/**
 **
[ 0 ] 0 1 2 
[ 1 ] 1 2 3 
[ 2 ] 2 3 4 
[ 3 ] 3 4 5 
 **
 **/

int main()
{
    const int rowSize = 4;
    const int colSize = 3;

    int ia[ rowSize ][ colSize ];

    for ( int i = 0; i < rowSize; ++i )
	{
		cout << "[ " << i << " ] ";
                for ( int j = 0; j < colSize; ++j )
		{
                      ia[ i ][ j ] = i + j;
		      cout << ia[ i ][ j ] << ' ';
		}
		cout << endl;
	}
}
