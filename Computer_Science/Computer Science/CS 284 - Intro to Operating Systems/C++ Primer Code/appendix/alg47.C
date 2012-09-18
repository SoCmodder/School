#include <algorithm>
#include <vector>
#include <iostream.h>

/* generates:
Expecting to find two instances of 'o': o o 
Expecting to find the substring `mou':  m o u 
*/
	
int main() 
{
        ostream_iterator< char >  ofile( cout, " " );

	const char blank = ' ';
	const char oh    = 'o';

	char str[ 26 ]  = "oh my a mouse ate a moose";
	char *found_str = search_n( str, str+25, 2, oh );
		
	cout << "Expecting to find two instances of 'o': ";
        copy( found_str, found_str+2, ofile ); cout << '\n';

	vector< char, allocator > vec( str, str+25 );
		
	// find the first sequence in which three characters
	// do not equal a blank space: mou of mouse

	vector< char, allocator >::iterator iter;
        iter = search_n( vec.begin(), vec.end(), 3, 
			 blank, not_equal_to< char >() );
		
	cout << "Expecting to find the substring `mou':  ";
        copy( iter, iter+3, ofile ); cout << '\n';
}
