/*-----------------------------------------------------------
 * Programmer: Mike Gosnell
 * CS 54 lab 10 -- Sample Solution
 * Date: 10/14/02
 *-----------------------------------------------------------
 * Program Description:
 * Write a program that reads in 25 numbers.
 * Find and display the largest and the smallest of the 25 numbers,
 * the sum, the average, and the product of all the numbers.
 * Write this program 3 times; one using a while loop, one a using
 * do-while loop, and one using a for loop.
 *
 * We'll just include all loops in this program and can comment
 * out the two we don't want to include at any given time.
 *
 * This example code is posted at http://web.umr.edu/~mrghx4/
 */

#include <iostream>     //standard include to allow output (cout)

using namespace std;    //we're using the new header so we need to know the namespace

const int inputNumbers = 25; //sets the number of inputs once
//This is easiest if we were to ever need to change the input size

int main()
{
    //input statistics as listed in the program description
    double mySum  = 0, //so we can add all inputs to the sum
           myAvg  = 0,
           myProd = 1, //so we can multiply all inputs by this number
           myMin  =  999999999, //we set min to a huge number
           myMax  = -999999999; //and max to a small number
                                //so they'll be updated with any normal input
    //the user's input
    double doubleInput;
    int currentInputs = 0; //the current number of inputs

    //Display the initial menu choices.   (only once)
    cout << "Please input " << inputNumbers << " numbers\n"
         << "(You can keep inputting until you get results).\n";

////////////////////DO WHILE LOOP///////////////////////////
    do {
        cin >> doubleInput; //user inputs a response (we assume it's a number)
        ++currentInputs; //we have one more input

        //Updates to the current input statistics
        mySum  += doubleInput;
        myProd *= doubleInput;

        //updates the max or min (we assume it can't be both)
        if (doubleInput < myMin) {
            myMin = doubleInput;
        }
        else if (doubleInput > myMax) {
            myMax = doubleInput;
        }
    } while (currentInputs < inputNumbers);
////////////////////////////////////////////////////////////


////////////////////WHILE LOOP//////////////////////////////
    while (currentInputs < inputNumbers) {
        cin >> doubleInput; //user inputs a response (we assume it's a number)
        ++currentInputs; //we have one more input

        //Updates to the current input statistics
        mySum  += doubleInput;
        myProd *= doubleInput;

        //updates the max or min (we assume it can't be both)
        if (doubleInput < myMin) {
            myMin = doubleInput;
        }
        else if (doubleInput > myMax) {
            myMax = doubleInput;
        }
    }
////////////////////////////////////////////////////////////


////////////////////////FOR LOOP////////////////////////////
    //notice the first parameter in the for loop is set to nothing since
    //we already initialized currentInputs = 0 above ... alternatively
    //we could put in for(currentInputs = 0; <other stuff>) but it would be redundant
    for (; currentInputs < inputNumbers ; ++currentInputs) {
        cin >> doubleInput; //user inputs a response (we assume it's a number)

        //Updates to the current input statistics
        mySum  += doubleInput;
        myProd *= doubleInput;

        //updates the max or min (we assume it can't be both)
        if (doubleInput < myMin) {
            myMin = doubleInput;
        }
        else if (doubleInput > myMax) {
            myMax = doubleInput;
        }
    }
////////////////////////////////////////////////////////////

    //after any loop, we have the sum & can run this independently
    myAvg = mySum / inputNumbers; //only need to calculate the average once

    //output the 'input statistics'
    cout << "\nInput Statistics:"
         << "\nMax     = " << myMax
         << "\nMin     = " << myMin
         << "\nSum     = " << mySum
         << "\nAverage = " << myAvg
         << "\nProduct = " << myProd
         << endl;

    return 0;
}
