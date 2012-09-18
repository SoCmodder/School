/******************************************************
 * Mike Gosnell
 * Sample Solution for lab 15
 * Week 11 CS 54      (lab 2)
 ******************************************************/

/******************************************************
 * This program reads in 2 integers from a file
 *  and outputs them to another file in reverse order
 ******************************************************/

#include <fstream> //for file I/O

const char* INPUTFILE = "filein.dat";
const char* OUTPUTFILE = "fileout.dat";

int main() {
//LOCAL DIRECTIVES/////////////////////////////////////
using std::ifstream;
using std::ofstream;
///////////////////////////////////////////////////////
    int in1, in2;
    
    ifstream in_stream; 	//sets up the input file for reading
    in_stream.open(INPUTFILE);

    in_stream >> in1 >> in2;	//reads numbers from input file

    in_stream.close();		//closes input file


    ofstream out_stream; 	//sets up the output file for writing
    out_stream.open(OUTPUTFILE);

	//writes numbers to output file in reverse order
    out_stream << in2 << " " << in1;

    out_stream.close();		//closes output file

    return 0;
} //end int main()
