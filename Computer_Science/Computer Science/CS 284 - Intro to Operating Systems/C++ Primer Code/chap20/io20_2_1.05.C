#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream.h>

/**
 **
 * generates:
 **
 The number of words read is 65
 The longest word has a length of 9
 The longest word is beautiful
 **
 * default less:
 **
 The number of words read is 65
 The longest word has a length of 4
 The longest word is wind
 **
 **/

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

bool length_less( string s1, string s2 ) 
	{ return s1.size() < s2.size(); }

int main() 
{
        typedef vector<string,allocator>::difference_type diff_type;
        istream_iterator< string, diff_type > input( cin ), eos;

	vector< string, allocator > text;
	copy(   input, eos, back_inserter( text ));

	string filt_elems( "\",.;:");
	filter_string( text.begin(), text.end(), filt_elems );

	int     cnt = text.size();
	string *max = max_element( text.begin(), text.end(), length_less );
	int     len = max->size();
	
	cout << "The number of words read is " << cnt << endl;
        cout << "The longest word has a length of " << len << endl;
	cout << "The longest word is " << *max << endl;
}	
