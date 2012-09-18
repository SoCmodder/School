/******************************************************
 * Mike Gosnell
 * Sample Solution for lab 16
 * Week 12 CS 54
 ******************************************************/

/******************************************************
 * Array Lab to compute standard deviation from numbers
 * found in FILENAME (up to ARRAYSIZE elements)
 ******************************************************/

#include <iostream> //for cin & cout
#include <cmath>    //for square root call
#include <fstream>  //for file input
#include <cassert>  //for asserting the file opened OK

using namespace std;

const int   ARRAYSIZE = 50;
const char* FILENAME  = "numbers.dat";
//technically the char* is an array of characters ...
//(which is a little different than a string)

//FUNCTION DECLARATIONS////////////////////////////////
double Sdeviation(double ourArray[], double average);
double fileInput(double ourArray[]);
//END FUNCTION DECLARATIONS////////////////////////////

int main() {
    double userInputs[ARRAYSIZE];	//initializes the array

    double sum = fileInput(userInputs); //populates array from file
					//and sets up sum
    double average = sum / ARRAYSIZE;   //calculates & stores avg

	//calculates standard deviation and outputs results
    cout << "I found your average to be: " << average << endl;
    cout << "The standard deviation of your numbers is then: "
         << Sdeviation(userInputs, average) << endl;

    return 0;
} //end int main()

///////////////////////////////////////////////////////
//Pre:  array is completely filled (and N != 0)
//Post: returns standard deviation
///////////////////////////////////////////////////////
double Sdeviation(double ourArray[], double average) {
    double sumOfSquares = 0;  //sum of squares for std deviation

    for (int x = 0; x < ARRAYSIZE; ++x) {
        sumOfSquares += pow((ourArray[x] - average), 2);
    }

    return sqrt(sumOfSquares / ARRAYSIZE);
}

///////////////////////////////////////////////////////
//Pre:  none
//Post: fills ourArray with FILENAME's elements
//      returns the sum of the input numbers as a double
///////////////////////////////////////////////////////
double fileInput(double ourArray[]) {
    double sum = 0;
    
    ifstream inputStream;
    inputStream.open(FILENAME);
    
    assert (! inputStream.fail()); //assures file opened OK
    int x = 0; //for loop counter & to see how many numbers we input
	//(last line took care of initial loop condition)

    //read the numbers into the array elements
    // I also test to make sure we're not at the end of the file ...
    for (; !inputStream.eof() && x < ARRAYSIZE; ++x) {
        inputStream >> ourArray[x];	//reads in a single value to a[x]
        sum += ourArray[x];		//calculates the sum as we read in
    }

    inputStream.close();

	//this informs the user of how many inputs we gathered
	// (in case we got to the end of the file before we should have!)
    cout << x << " inputs out of " << ARRAYSIZE << " completed..." << endl;
    return sum;
}
