#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
   original element sequence:
   29 23 20 22 12 17 15 26 51 19 12 23 35 40 
   stable sort -- default ascending order:
   12 12 15 17 19 20 22 23 23 26 29 35 40 51 
   stable sort: descending order:
   51 40 35 29 26 23 23 22 20 19 17 15 12 12 
*/
	
int main()
{
	int ia[] = { 29,23,20,22,12,17,15,26,51,19,12,23,35,40 }; 
	vector< int, allocator > vec( ia, ia+14 );
        ostream_iterator< int >  ofile( cout, " " );

        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	stable_sort( &ia[0], &ia[14] );

        cout << "stable sort -- default ascending order:\n";
        copy( ia, ia+14, ofile ); cout << '\n';
		
	stable_sort( vec.begin(), vec.end(), greater<int>() );

	cout << "stable sort: descending order:\n";
	copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}
