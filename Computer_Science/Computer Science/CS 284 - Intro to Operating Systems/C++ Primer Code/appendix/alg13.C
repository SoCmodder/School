#include <algorithm>
#include <vector>
#include <string>
#include <iostream.h>

int main() 
{
	string s_array[] = { "Ee", "eE", "ee", "Oo", "oo", "ee" };

	// returns first occurrence of "ee" -- &s_array[2]
	string to_find[] = { "oo", "gg", "ee" };
		
	string *found_it = 
		find_first_of( s_array, s_array+6, 
			       to_find, to_find+3 );

	// generates:
	// found it: ee
	//         &s_array[2]:    0x7fff2dac
	//         &found_it:      0x7fff2dac

	if ( found_it != &s_array[6] )
	     cout << "found it: "     << *found_it     << "\n\t"
		  << "&s_array[2]:\t" << &s_array[2]   << "\n\t"
		  << "&found_it:\t"   << found_it      << "\n\n";
		
	vector< string, allocator > svec( s_array, s_array+6);
	vector< string, allocator > svec_find( to_find, to_find+2 );
		
	// returns occurrence of "oo" -- svec.end()-2
	vector< string, allocator >::iterator found_it2;

	found_it2 = find_first_of( svec.begin(),      svec.end(), 
				   svec_find.begin(), svec_find.end(),
				   equal_to<string>() );

	// generates:
	// found it, too: oo
	//         &svec.end()-2:  0x100067b0
	//         &found_it2:     0x100067b0

	if ( found_it2 != svec.end() )
	     cout << "found it, too: "  << *found_it2   << "\n\t"
		  << "&svec.end()-2:\t" << svec.end()-2 << "\n\t"
		  << "&found_it2:\t"    << found_it2    << "\n";

}
