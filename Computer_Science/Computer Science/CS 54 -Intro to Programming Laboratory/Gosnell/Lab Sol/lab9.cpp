/*-----------------------------------------------------------
 * Programmer: Mike Gosnell
 * CS 54 lab 9 -- Sample Solution
 * Date: 10/11/02
 *-----------------------------------------------------------
 * Program Description:
 * Write a program that will ask the user the following question:
 * Will the St. Louis Cardinals go to the World Series?
 * The program should prompt for 4 possible answers:
 *
 *    1.  Yes
 *    2.  No
 *    3.  I don't know
 *    4.  I don't care
 *
 * This question is asked 20 times.
 * (To save space on the print-out, we simply allow for 20 inputs
 *  without printing the question 20 times.) After all the input
 *  is gathered, the program should output the number of times each
 *  answer was selected.
 *
 * This example code is posted at http://web.umr.edu/~mrghx4/
 */

#include <iostream>     //standard include to allow output (cout)
using namespace std;    //we're using the new header so we need to know the namespace

int main()
{
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0; //the number of times each answer was given
    int userSelection;  //the user's input
    int inputs = 0;  //we currently have no inputs
    //we keep track of inputs becaue I'm testing to make sure each input is valid

    //Display the initial menu choices.   (only once)
    cout << "Please answer the following question 20 times\n"
         << "Will the Cardinals win the World Series?\n"
         << "1) Of course!\n"
         << "2) Not a chance!\n"
         << "3) Who knows!\n"
         << "4) Who cares!\n";

    do {//we want to input until we have 20 responses
        //We will assume that the input will be a number
        // (although not necessarily valid.)
        cin >> userSelection; //user inputs a response

        ++inputs; //we assume the input was valid
        //we take care of invalid entries in default:

        switch (userSelection) { //increment appropriate answer
            case 1:
                ++a1;
                break;

            case 2:
                ++a2;
                break;

            case 3:
                ++a3;
                break;

            case 4:
                ++a4;
                break;

            default:    //not a valid answer
                cout << "The input of " << userSelection << " was invalid.";
                --inputs;  //input was invalid so we can't count it
        } //end switch (userSelection) {}

    } while (inputs < 20); //continue with execution until we get 20 inputs

    cout << "\n\nTally of the responses to:\n"
         << "Will the Cardinals win the World Series?\n"
         << "1) Of course!\t"    << a1 << endl
         << "2) Not a chance!\t" << a2 << endl
         << "3) Who knows!\t"    << a3 << endl
         << "4) Who cares!\t"    << a4 << endl;

    return 0;
}
