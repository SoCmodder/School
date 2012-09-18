#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
   original element sequence:
   29 23 20 22 17 15 26 51 19 12 35 40 
   stable_partition on even element:
   20 22 26 12 40 29 23 17 15 51 19 
   stable_partition of less-than 25:
   23 20 22 17 15 19 12 29 26 51 35 40 
*/
	
class even_elem {
public:
	bool operator()( int elem ) {
		return elem%2 ? false : true;
	}
};
	
int main()
{
	int ia[] = { 29,23,20,22,17,15,26,51,19,12,35,40 }; 
	vector< int, allocator > vec( ia, ia+12 );
        ostream_iterator< int >  ofile( cout, " " );
		
        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	stable_partition( &ia[0], &ia[12], even_elem() );

        cout << "stable_partition on even element:\n";
        copy( ia, ia+11, ofile ); cout << '\n';

	stable_partition( vec.begin(), vec.end(),
			  bind2nd(less<int>(),25)  );

        cout << "stable_partition of less-than 25:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}

