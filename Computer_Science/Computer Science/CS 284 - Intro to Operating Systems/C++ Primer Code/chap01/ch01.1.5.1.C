// #include <iostream>
// #include <fstream>

#include <iostream.h>
#include <fstream.h>
#include <string>

/**
 ** 
 stanl@john:d.01 264 : xsh32 ch01.1.5.1.c
 **
 stanl@john:d.01 267 : cat input_file
 Shyly, she asks, "I mean, Daddy, is there?"
 **
 stanl@john:d.01 265 : a.out
 **
 stanl@john:d.01 266 : cat out_file
 Shyly, she asks, "I mean, Daddy, is there?" 
 **
 **/

int main()
{
 	ofstream outfile( "out_file" );
 	ifstream infile( "input_file" );

 	if ( ! infile ) {
    		cerr << "error: unable to open input file!\n";
    		return -1;
 	}

 	if ( ! outfile ) {
    		cerr << "error: unable to open output file!\n";
    		return -2;
   	}

   	string word;
   	while ( infile >> word )
         	outfile << word << ' ';

   	return 0;
}
