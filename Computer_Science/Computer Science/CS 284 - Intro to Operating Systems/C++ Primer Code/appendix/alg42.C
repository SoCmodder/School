#include <algorithm>
#include <list>
#include <string>

/* generates:
Original sequence of strings:
        Signature of all things I am here to
        read seaspawn and seawrack that rusty boot 

Sequence after reverse() applied:
        boot rusty that seawrack and seaspawn read to
        here am I things all of Signature 
*/

class print_elements {
public:
	void operator()( string elem ) {	
		cout << elem 
		     << ( _line_cnt++%8 ? " " : "\n\t" ); 
	}

	static void reset_line_cnt() { _line_cnt = 1; }

private:
	static int _line_cnt;
};

int print_elements::_line_cnt = 1;

int main()
{
	string sa[] = { "Signature", "of", "all", "things",
			"I", "am", "here", "to", "read",
			"seaspawn", "and", "seawrack", "that",
			"rusty", "boot"
	};

	list< string, allocator > slist( sa, sa+15 );

	cout << "Original sequence of strings:\n\t";
        for_each( slist.begin(), slist.end(), print_elements() ); 
	cout << "\n\n";

	reverse( slist.begin(), slist.end() );

	print_elements::reset_line_cnt();

	cout << "Sequence after reverse() applied:\n\t";
        for_each( slist.begin(), slist.end(), print_elements() ); cout << "\n";

	list< string, allocator > slist_copy( slist.size() );
	reverse_copy( slist.begin(), slist.end(), slist_copy.begin() );
}
