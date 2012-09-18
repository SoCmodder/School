// #include <fstream>
#include <fstream.h>
#include "WordCount.h"

/**
 **
 ** note: must include the WordCount.C as well as io20_6.02.c:
 **       Stan's Silicon Graphics invocation:
 **
 stanl@john:d.ch20 236 : CC -n32 -experimental io20_6.02.c WordCount.C 
 stanl@john:d.ch20 237 : a.out
 stanl@john:d.ch20 238 : cat word.out

 <2> Renoir
 <7,12>  <34,18>  

 **
 **/

int main()
{
    // open a file word.out for output
    ofstream oFile( "word.out" );

    if ( ! oFile ) {
	 cerr << "unable to open output file: word.out!\n";
	 return -1;
    }

    // create and manually set
    WordCount artist( "Renoir" );
    artist.found( 7, 12 ); artist.found( 34, 18 );

    // invokes operator <<(ostream&, const WordCount&);
    oFile << artist;
}

