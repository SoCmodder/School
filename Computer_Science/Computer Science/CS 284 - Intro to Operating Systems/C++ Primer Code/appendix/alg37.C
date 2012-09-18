#include <algorithm>
#include <vector>
#include <assert.h>
#include <iostream.h>
	
/* generates:
   original vector sequence:
   0 1 0 2 0 3 0 4 0 5 
   vector after remove, without applying erase():
   1 2 3 4 5 3 0 4 0 5 
   vector after erase():
   1 2 3 4 5 
*/

int main()
{
	int value = 0;
	int ia[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5 };

	vector< int, allocator >           vec( ia, ia+10 );
	ostream_iterator< int >            ofile( cout," ");
	vector< int, allocator >::iterator vec_iter;

	cout << "original vector sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
		
	vec_iter = remove( vec.begin(), vec.end(), value );

	cout << "vector after remove, without applying erase():\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
		
	// erase the invalid elements from container
	vec.erase( vec_iter, vec.end() );

	cout << "vector after erase():\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}
