#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream.h>

/* generates:
   0 1 1 3 5 8 13 
   shifting array sequence left by 1:
   1 1 3 5 8 13 13 
   shifting vector sequence left by 2:
   1 3 5 8 13 8 13 
*/

int main()
{
	int ia[] = { 0, 1, 1, 3, 5, 8, 13 };
	vector< int, allocator > vec( ia, ia+7 );
        ostream_iterator< int >  ofile( cout, " " );
		
        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	// shift left by one
	copy( ia+1, ia+7, ia );

        cout << "shifting array sequence left by 1:\n";
        copy( ia, ia+7, ofile ); cout << '\n';

	// shift left by two
	copy( vec.begin()+2, vec.end(), vec.begin() );
		
        cout << "shifting vector sequence left by 2:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	return 0;
}
