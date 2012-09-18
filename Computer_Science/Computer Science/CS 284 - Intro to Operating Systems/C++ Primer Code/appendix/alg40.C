#include <algorithm>
#include <vector>

/* generates:
   original element sequence:
   Christopher Robin Mr. Winnie the Pooh Piglet Tigger Eeyore 
   sequence after applying replace():
   Christopher Robin Pooh Piglet Tigger Eeyore 
*/
	
int main()
{
	string oldval( "Mr. Winnie the Pooh" );
	string newval( "Pooh" );
		
        ostream_iterator< string >  ofile( cout, " " );
	string sa[] = { 
		"Christopher Robin", "Mr. Winnie the Pooh",
		"Piglet", "Tigger", "Eeyore" 
        };

	vector< string, allocator > vec( sa, sa+5 );
        cout << "original element sequence:\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
		
	replace( vec.begin(), vec.end(), oldval, newval );
		
        cout << "sequence after applying replace():\n";
        copy( vec.begin(), vec.end(), ofile ); cout << '\n';
}
