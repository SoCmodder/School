#include <algorithm>
#include <list>
	
class even_by_twos {
public:
	even_by_twos( int seed = 0 ) : _seed( seed ){}
	int operator()() { return _seed += 2; }
private:
	int _seed;
};

template <class Type>
void print_elements( Type elem ) { cout << elem << " "; }

int main()
{
        list< int, allocator > ilist( 10 );
        void (*pfi)( int ) = print_elements;

	generate_n( ilist.begin(), ilist.size(), even_by_twos() );

	// generates:
	// generate_n with even_by_twos():
	// 2 4 6 8 10 12 14 16 18 20 

	cout << "generate_n with even_by_twos():\n";
	for_each( ilist.begin(), ilist.end(), pfi ); cout << "\n";

	generate_n( ilist.begin(), ilist.size(), even_by_twos( 100 ) );

	// generates:
	// generate_n with even_by_twos( 100 ):
	// 102 104 106 108 110 112 114 116 118 120

	cout << "generate_n with even_by_twos( 100 ):\n";
	for_each( ilist.begin(), ilist.end(), pfi );
}
