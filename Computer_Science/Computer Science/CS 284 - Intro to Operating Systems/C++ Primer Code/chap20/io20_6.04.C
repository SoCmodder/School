// #include <fstream>
#include <fstream.h>
#include <iterator>
#include <vector>
#include <algorithm>

/* 
 * generates:

A Alice Daddy Emma Her I Shyly a 
alive almost asks at beautiful bird blows but 
creature fiery flight flowing hair has he her 
him in is it like long looks magical 
mean more no red same says she shush 
such tell tells the there through time to 
untamed wanting when wind 
*/

template <class InputIterator>
void filter_string( InputIterator first, InputIterator last,
                    string filt_elems = string("\",."))
{
        for ( ; first != last; first++ )
        {
                string::size_type pos = 0;
                while (( pos = (*first).find_first_of( filt_elems, pos ))
                            != string::npos )
                                (*first).erase( pos, 1 );
        }
}

int main() 
{
	ifstream infile( "alice_emma" );

	istream_iterator<string> ifile( infile );
	istream_iterator<string> eos;

	vector< string > text;
	copy( ifile, eos, inserter( text, text.begin() ));

	string filt_elems( "\",.?;:" );
	filter_string( text.begin(), text.end(), filt_elems );

	vector<string>::iterator iter;

	sort( text.begin(), text.end() );
	iter = unique( text.begin(), text.end() );
	text.erase( iter, text.end() );
	
	ofstream outfile( "alice_emma_sort" );

	iter = text.begin();
	for ( int line_cnt = 1; iter != text.end(); ++iter, ++line_cnt ) 
	{
		outfile << *iter << " ";
		if ( ! ( line_cnt % 8 ))
	     		outfile << '\n';
	}
}
