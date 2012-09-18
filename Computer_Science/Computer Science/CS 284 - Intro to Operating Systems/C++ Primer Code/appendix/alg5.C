#include <algorithm>
#include <string>
#include <list>
#include <iterator>

#include <assert.h>
#include <iostream.h>
#include <fstream.h>

int main() 
{
	/*
	**********************************************************************
	* text read:
	   Alice Emma has long flowing red hair. Her Daddy says
	   when the wind blows through her hair, it looks almost alive,
	   like a fiery bird in flight. A beautiful fiery bird, he tells her,
	   magical but untamed. "Daddy, shush, there is no such thing,"
	   she tells him, at the same time wanting him to tell her more.
	   Shyly, she asks, "I mean, Daddy, is there?"
	 **********************************************************************
	 * output of program:
	 * 	count(): fiery occurs 2 times
	 **********************************************************************
	 */

 
	ifstream infile( "alice_emma" );
	assert ( infile != 0 );

        list<string,allocator> textlines; 

	typedef list<string,allocator>::difference_type diff_type;
	istream_iterator< string, diff_type > instream( infile ), eos;

        copy( instream, eos, back_inserter( textlines ));

	string search_item( "fiery" );

	/************************************************************
	 * note: this is the Standard C++ interface for using count()
	 *       however, the current RogueWave implementation 
	 *       supports the earlier version in which distance_type
	 *       had not been developed, and so count() returned its
	 *       value via a final argument to itself.
         *     
         * this is how the invocation should occur:
	 *
	 ************************************************************
	 *
	 * typedef iterator_traits<InputIterator>::
	 *		distance_type dis_type;
	 *	
	 * dis_type elem_count;
	 * elem_count = count( textlines.begin(), textlines.end(), search_item );
	 ***********************************************************************
	 */
		
        int elem_count = 0;
	list<string,allocator>::iterator ibegin = textlines.begin(),
		                                  iend   = textlines.end();

	// obsolete form of count()
	count( ibegin, iend, search_item, elem_count );


 	cout << "count(): " << search_item 
             << " occurs "  << elem_count << " times\n"; 
		
	return 0;
}
