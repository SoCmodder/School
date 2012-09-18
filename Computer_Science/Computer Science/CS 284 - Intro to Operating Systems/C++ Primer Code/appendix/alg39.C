#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
   original element sequence:
   3 4 5 0 1 2 
   sequence applying swap() to support bubble sort:
   0 1 2 3 4 5 
*/
	
int main()
{
	int ia[]  = { 3, 4, 5, 0, 1, 2 };
	vector< int, allocator > vec( ia, ia+6 );
		
	for ( int ix = 0; ix < 6; ++ix )
		for ( int iy = ix; iy < 6; ++iy ) {
			if ( vec[iy] < vec[ ix ] ) 
			     swap( vec[iy], vec[ix] );
		}

	ostream_iterator< int >  ofile( cout, " " );

        cout << "original element sequence:\n";
        copy( ia, ia+6, ofile ); cout << '\n';

        cout << "sequence applying swap() to support bubble sort:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}
