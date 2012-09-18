/*-----------------------------------------------------------
 * Programmer: Mike Gosnell
 * CS 54 lab 10 -- Sample Solution
 * Date: 10/11/02
 *-----------------------------------------------------------
 * Program Description:
 * Write a program that reads in 25 numbers.
 * Display the 25 numbers on 5 rows. Find and display the largest
 * and the smallest of the 25 numbers, the sum, the average, and
 * the product of all the numbers. Write this program 3 times;
 * one using while loop, one using do-while loop, and one using for loop.
 *
 * We'll just include 1 loops in this program since it's not the real 
 * assignment.
 *
 * This example code is posted at http://web.umr.edu/~mrghx4/
 */

#include <iostream>     //standard include to allow output (cout)
#include <cstdlib>	//for the atof conversion to double

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
    string userInput;
    double doubleInput;

    //for outputting the results (as a string)
    string myOutput = "";  //always good to initialize a string if you're going to concatenate

    //Display the initial menu choices.   (only once)
    cout << "Please input " << inputNumbers << " numbers\n"
         << "(You can keep inputting until you get results).\n";

    for (int x = 0; x < inputNumbers ; x++) {
	//we'll store the input first as a string for output
        cin >> userInput; //user inputs a response (we assume it's a number)

	//then convert to a double to do numeric processing
	doubleInput = atof((userInput).c_str());
           //the atof takes an array of characters (numbers) and converts 
           //    to a floating point number (also works for double)
           //userInput is a string, so we call .c_str() on it to convert
           //    to an array of characters so we can pass it to atof()
           
	   //clearly this hasn't been covered yet, and that's why this
           //    lab wasn't given :)

        myOutput += userInput; //this adds the user's input to the result we'll output later
	
	//for the specifications in the output of 5 items per row ...
        if (((x+1) % 5) == 0) { //sticks a return after every 5 characters
            myOutput += "\n";
        }
        else { //tabs between the 5 characters
            myOutput += "\t";
        }

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

    myAvg = mySum / inputNumbers; //only need to calculate the average once

    //output the 'input statistics'
    cout << "Your Input\n" << myOutput << endl;

    cout << "\nInput Statistics:"
         << "\nMax     = " << myMax
         << "\nMin     = " << myMin
         << "\nSum     = " << mySum
         << "\nAverage = " << myAvg
         << "\nProduct = " << myProd
         << endl;

    return 0;
}
