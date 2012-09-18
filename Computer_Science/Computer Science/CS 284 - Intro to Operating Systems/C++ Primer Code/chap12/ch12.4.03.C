#include <string>
#include <algorithm>
#include <iterator>
#include <fstream.h>
// #include <fstream>

/**
 **
 stanl@john:d.12 355 : xsh32 ch12.4.03.c

 stanl@john:d.12 356 : a.out
 please enter a file to open: infile
 ineluctable modality of the visible ... stanl@john:d.12 357 : 

 stanl@john:d.12 357 : cat infile
 ineluctable modality of the visible ...
 **
 **/

main()
{
	string file_name;

	cout << "please enter a file to open: ";
	cin >> file_name;

	if ( file_name.empty() || !cin ) {
		cerr << "unable to read file name\n"; return -1;
	}

	ifstream infile( file_name.c_str());
	if ( !infile ) {
		cerr << "unable to open " << file_name << endl;
		return -2;
	}

	istream_iterator< string > ins( infile ), eos;
	ostream_iterator< string > outs( cout, " " );
	copy( ins, eos, outs );
}
