/******************************************************
 * Mike Gosnell
 * Sample Solution for lab 15
 * Week 11 CS 54      (lab 2)
 * 
 * Solution implemented with a deque (double ended queue)
 * (A deque allows adding and removing from either end.)
 ******************************************************/

/******************************************************
 * This program reads in ANY number of integers from a 
 * file and outputs them to another file in reverse order
 ******************************************************/

#include <fstream> //for file I/O
#include <cassert> //assures that the files opened OK
#include <deque>   //built-in data structure I use
		   //to store the numbers (double ended queue)

const char* INPUTFILE = "in.dat";
const char* OUTPUTFILE = "out.dat";

int main() {
//LOCAL DIRECTIVES/////////////////////////////////////
using std::ifstream;
using std::ofstream;
using std::deque;
///////////////////////////////////////////////////////
    deque<int> numberDeque; //double-ended queue of integers
    int currentNumber;
    
    ifstream in_stream; 	//sets up the input file for reading
    in_stream.open(INPUTFILE);
    assert(! in_stream.fail()); //make sure it opened with no problems

    in_stream >> currentNumber;	//reads 1st # from input file
    while (! in_stream.eof()) { //while there are still numbers
	numberDeque.push_front(currentNumber);
        in_stream >> currentNumber;	//reads numbers from input file
    }

    in_stream.close();		//closes input file


    ofstream out_stream; 	//sets up the output file for writing
    out_stream.open(OUTPUTFILE);
    assert(! out_stream.fail());

	//writes numbers to output file in reverse order
    while (! numberDeque.empty()) { //while there are still numbers
        currentNumber = numberDeque.front();
	numberDeque.pop_front();
        out_stream << currentNumber << " ";
    }

    out_stream << std::endl; 	//sticks on a trailing endline
    out_stream.flush();

    out_stream.close();		//closes output file

    return 0;
} //end int main()
