// #include <fstream>

#include <fstream.h>
#include <string>
#include <vector>
#include <algorithm>

/**
 ** Please enter file to sort: alice_emma

 ** alice_emma:

Alice Emma has long flowing red hair. Her
Daddy says when the wind blows through her
hair, it looks almost alive, like a fiery
bird in flight. A beautiful fiery bird, he
tells her, magical but untamed. "Daddy, shush, there
is no such creature," she tells him, at
the same time wanting him to tell her
more. Shyly, she asks, "I mean, Daddy, is
there?" 

 ** alice_emma.sort:

"Daddy, "I A Alice Daddy Daddy, Emma Her
Shyly, a alive, almost asks, at beautiful bird
bird, blows but creature," fiery fiery flight. flowing
hair, hair. has he her her her, him
him, in is is it like long looks
magical mean, more. no red same says she
she shush, such tell tells tells the the
there there?" through time to untamed. wanting when
wind 

 **/

int main()
{
	string ifile;

	cout << "Please enter file to sort: ";
	cin >> ifile;

	// construct an ifstream input file object
	ifstream infile( ifile.c_str() );

	if ( ! infile ) {
     	     cerr << "error: unable to open input file: "
                  << ifile << endl;

              return -1;
        }

	string ofile = ifile + ".sort";

	// construct an ofstream output file object
	ofstream outfile( ofile.c_str() );
	if ( ! outfile) {
     	     cerr << "error: unable to open output file: "
                  << ofile << endl;
     	     return -2;
	}

	string buffer;
	vector< string > text;

	int cnt = 1;
	while ( infile >> buffer ) {
        	text.push_back( buffer );
        	cout << buffer << (cnt++ % 8 ? " " : "\n" );
	}

	sort( text.begin(), text.end() );

	// ok: print out sorted words into outfile
	vector< string >::iterator iter = text.begin();

	for ( cnt = 1; iter != text.end(); ++iter, ++cnt )
     	      outfile << *iter << (cnt % 8 ? " " : "\n" );

	return 0;
}
