// #include <fstream>
#include <fstream.h>
#include "WordCount.h"

/** 
 **
 ** as is the case with io20_6.02.c, WordCount.C
 ** must also be compiled with this program ...
 **
 stanl@john:d.ch20 258 : cat word.out

 <2> Renoir
 <7,12>  <34,18>  

 stanl@john:d.ch20 259 : a.out

 Read in: <2> Renoir
 <7,12>  <34,18>  

 stanl@john:d.ch20 260 : cat word.out

 <2> Renoir
 <7,12>  <34,18>  

 <2> Renoir
 <7,12>  <34,18>  
 **
 **/

int main()
{
    WordCount wd;

    fstream file;
    // ios is preStandard class name
    // file.open( "word.out", ios_base::in );
    file.open( "word.out", ios::in );

    if ( ! file ) {
	 cerr << "oops! unable to open input file word.out\n";
	 return -1;
    }

    file >> wd;
    file.close();

    cout << "Read in: " << wd << endl;

    // ios_base::out would discard current data
    // file.open( "word.out", ios_base::app );
    file.open( "word.out", ios::app );

    if ( ! file ) {
         cerr << "oops! unable to open input file ``word.out''\n";
         return -1;
    }

    file << endl << wd << endl;
    file.close();
}
