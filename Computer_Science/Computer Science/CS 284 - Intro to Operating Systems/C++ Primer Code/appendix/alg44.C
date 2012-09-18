#include <algorithm>
#include <vector>
#include <iostream.h>
	
/* generates:
   original element sequence:
   1 3 5 7 9 0 2 4 6 8 10 
   rotate on middle element(0) ::
   0 2 4 6 8 10 1 3 5 7 9 
   rotate on next to last element(8) ::
   8 10 1 3 5 7 9 0 2 4 6 
   rotate_copy on middle element ::
   7 9 0 2 4 6 8 10 1 3 5 
*/
int main()
{
	int ia[] = { 1, 3, 5, 7, 9, 0, 2, 4, 6, 8, 10 };

	vector< int, allocator > vec( ia, ia+11 );
        ostream_iterator< int >  ofile( cout, " " );

        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	rotate( &ia[0], &ia[5], &ia[11] );

        cout << "rotate on middle element(0) ::\n";
        copy( ia, ia+11, ofile ); cout << '\n';

	rotate( vec.begin(), vec.end()-2, vec.end() );
		
	cout << "rotate on next to last element(8) ::\n";
	copy( vec.begin(), vec.end(), ofile ); cout << '\n';

	vector< int, allocator > vec_res( vec.size() );

        rotate_copy( vec.begin(), vec.begin()+vec.size()/2,
                     vec.end(), vec_res.begin() );

        cout << "rotate_copy on middle element ::\n";
        copy( vec_res.begin(), vec_res.end(), ofile ); cout << '\n';

}
