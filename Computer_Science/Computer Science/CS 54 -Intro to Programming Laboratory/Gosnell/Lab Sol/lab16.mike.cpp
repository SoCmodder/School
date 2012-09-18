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

const int ARRAYSIZE = 50;
const char* FILENAME = "numbers.dat";

//FUNCTION DECLARATIONS////////////////////////////////
double Sdeviation(double ourArray[], double average);
double fileInput(double ourArray[]);
//END FUNCTION DECLARATIONS////////////////////////////

int main() {
//LOCAL DIRECTIVES/////////////////////////////////////
using std::cout;
using std::endl;
///////////////////////////////////////////////////////

    double userInputs[ARRAYSIZE];
    int numInputs;  //user can determine the # of inputs

    double sum = fileInput(userInputs);
    double average = sum / ARRAYSIZE;

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
//LOCAL DIRECTIVES/////////////////////////////////////
using std::sqrt;
using std::pow;
///////////////////////////////////////////////////////

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
//LOCAL DIRECTIVES/////////////////////////////////////
using std::ifstream;
using std::cout;
using std::endl;
///////////////////////////////////////////////////////
double sum = 0;
    
    ifstream inputStream;
    inputStream.open(FILENAME);
    
    assert (! inputStream.fail()); //assures file opened OK

    int x = 0; //for loop counter & to see how many numbers we input

    //read in the numbers to the userInput array
    // I also test to make sure we're not at the end of the file ...
    for (; !inputStream.eof() && x < ARRAYSIZE; ++x) {
        inputStream >> ourArray[x];
        sum += ourArray[x];
    }

    inputStream.close();

    cout << x << " inputs out of " << ARRAYSIZE << " completed..." << endl;
    return sum;
}
