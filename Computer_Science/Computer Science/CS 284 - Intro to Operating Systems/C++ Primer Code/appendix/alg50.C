#include <algorithm>
#include <vector>
#include <string>

#include <iostream.h>

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

/* generates:
   original element sequence of array container:
   0 1 1 2 3 5 8 

   array after fill_n( ia+2, 3, 9 ):
   0 1 9 9 9 5 8 

   original sequence of strings:
        Stephen closed his eyes to hear his boots
        crush crackling wrack and shells 

   sequence after fill_n() applied:
        Stephen closed his xxxxx xxxxx xxxxx xxxxx xxxxx
        xxxxx crackling wrack and shells 
*/

int main()
{
	int value = 9; int count = 3;
	int ia[]  = { 0, 1, 1, 2, 3, 5, 8 };
	ostream_iterator< int > iofile( cout, " " );
		
        cout << "original element sequence of array container:\n";
        copy( ia, ia+7, iofile ); cout << "\n\n";

	fill_n( ia+2, count, value );

        cout << "array after fill_n( ia+2, 3, 9 ):\n";
                copy( ia, ia+7, iofile ); cout << "\n\n";

	string replacement( "xxxxx" );
	string sa[] = { "Stephen", "closed", "his", "eyes", "to",
			"hear", "his", "boots", "crush", "crackling",
			"wrack", "and", "shells" };

	vector< string, allocator > svec( sa, sa+13 );

        cout << "original sequence of strings:\n\t";
        for_each( svec.begin(), svec.end(), print_elements() );
        cout << "\n\n";

	fill_n( svec.begin()+3, count*2, replacement );
		
        print_elements::reset_line_cnt();

        cout << "sequence after fill_n() applied:\n\t";
        for_each( svec.begin(), svec.end(), print_elements() ); 
	cout << "\n";
}
