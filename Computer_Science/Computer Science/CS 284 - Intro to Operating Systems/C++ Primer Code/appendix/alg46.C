#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
Expecting to find the substring `ate': a t e 
Expecting to find the substring `vat': v a t 
*/

int main() 
{
        ostream_iterator< char >  ofile( cout, " " );
	
	char str[ 25 ]   = "a fine and private place";
	char substr[] = "ate";
		
	char *found_str = search(str,str+25,substr,substr+3);

	cout << "Expecting to find the substring `ate': ";
        copy( found_str, found_str+3, ofile ); cout << '\n';
		
	vector< char, allocator > vec( str, str+24 );
	vector< char, allocator > subvec(3);

	subvec[0]='v'; subvec[1]='a'; subvec[2]='t';
	
	vector< char, allocator >::iterator iter; 
        iter = search( vec.begin(), vec.end(),
		       subvec.begin(), subvec.end(),
		       equal_to< char >() );
		
	cout << "Expecting to find the substring `vat': ";
        copy( iter, iter+3, ofile ); cout << '\n';

}
