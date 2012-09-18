#include <algorithm>
#include <vector>
#include <iostream.h>

/*
   original element sequence:
   0 1 1 2 3 5 8 13 21 34 
   sequence after applying replace_if < 10 with 0:
   0 0 0 0 0 0 0 13 21 34 
   sequence after applying replace_if even with 0:
   0 1 1 0 3 5 0 13 21 0 
*/
	
class EvenValue {
public:
	bool operator()( int value ) {
		return value % 2 ? false : true; }
};
	
int main()
{
	int new_value = 0;
		
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	vector< int, allocator > vec( ia, ia+10 );
        ostream_iterator< int >  ofile( cout, " " );

        cout << "original element sequence:\n";
        copy( ia, ia+10, ofile ); cout << '\n';

	replace_if( &ia[0], &ia[10], 
		    bind2nd(less<int>(),10), new_value );
		
        cout << "sequence after applying replace_if < 10 with 0:\n";
        copy( ia, ia+10, ofile ); cout << '\n';

	replace_if( vec.begin(), vec.end(), EvenValue(), new_value );

        cout << "sequence after applying replace_if even with 0:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}
