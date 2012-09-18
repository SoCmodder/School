#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
   original element sequence:
   0 1 1 2 3 5 8 13 21 34 
   sequence after applying remove_if < 10:
   13 21 34 
   sequence after applying remove_copy_if even:
   1 1 3 5 13 21 
*/

class EvenValue {
public:
	bool operator()( int value ) {
		return value % 2 ? false : true; }
};
	
int main()
{
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };

	vector< int, allocator >::iterator iter;
	vector< int, allocator >           vec( ia, ia+10 );
        ostream_iterator< int >            ofile( cout, " " );

        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	iter = remove_if( vec.begin(), vec.end(),
			   bind2nd(less<int>(),10) );
	vec.erase( iter, vec.end() );
		
        cout << "sequence after applying remove_if < 10:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	vector< int, allocator > vec_res( 10 );
	iter = remove_copy_if( ia, ia+10, vec_res.begin(), EvenValue() );

        cout << "sequence after applying remove_copy_if even:\n";
        copy( vec_res.begin(), iter, ofile ); cout << '\n';
}
