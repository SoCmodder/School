// #include <fstream>
#include <fstream.h>

/**
 **
 stanl@john:d.ch20 222 : cat input
 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23

 stanl@john:d.ch20 223 : a.out < input
 stanl@john:d.ch20 224 : cat copy.out
 23 109 45 89 6 34 12 90 34 23 56 23 8 89 23
 **
 **/


int main()
{
    // open a file copy.out for output
    ofstream outFile( "copy.out" );

    if ( ! outFile ) {
        cerr << "Cannot open ``copy.out'' for output\n";
        return -1;
    }

    char ch;
    while ( cin.get( ch ) )
	    outFile.put( ch );
}

