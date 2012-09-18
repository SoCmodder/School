/*-----------------------------------------------------------
 * Programmer: Mike Gosnell
 * CS 54 lab 8 -- Sample Solution
 * Date: 10/09/02
 *-----------------------------------------------------------
 * Program Description:
 * Write a program to convert metric to English units.
 *  The program should prompt the user for the type of conversion.
 *  The program should then prompt for a value to be converted.
 *  The program should then output the original value (specify units)
 *  and the converted value (also with units).
 *
 * This example code is posted at http://web.umr.edu/~mrghx4/lab8.cpp
 */

#include <iostream>     //standard include to allow output (cout)
using namespace std;    //we're using the new header so we need to know the namespace

int main()
{
    int userSelection = 0;
    double metricUnit = 0, englishUnit = 0;

    //we want to run the program until exit is choosen
    do {
        //Here we display the initial menu choices.
        //We can assume that the input will be a number
        // although not necessarily valid.
        do {
            cout << "\nSelect Conversion Type\n"
                 << "1) centimeters -> inches\n"
                 << "2) liters -> gallons\n"
                 << "3) kilometers -> miles\n"
                 << "4) kilograms -> pounds\n"
                 << "5) exit\n> ";
            cin  >> userSelection;

            //we'll repeat until a valid selection is made
            if (userSelection >= 6 || userSelection <= 0) {
                cout << "\nThe input was invalid.\n";
            }
        } while (userSelection >= 6 || userSelection <= 0);

        //We only need to do the rest of the program if they haven't entered EXIT
        if (userSelection != 5) {
            do {    //to make sure input of units is valid ...
                //Display the appropriate conversion request
                switch (userSelection) {
                    case 1:
                        cout << "Please enter the length in centimeters > ";
                        break;
                    case 2:
                        cout << "Please enter the volume in liters > ";
                        break;
                    case 3:
                        cout << "Please enter the length in kilometers > ";
                        break;
                    case 4:
                        cout << "Please enter the mass in kilograms > ";
                        break;
                    default:
                        cout << "Should Never Get Here";
                } //end switch (userSelection) {}

                //input the users metric value & test validity
                cin >> metricUnit;
                if (metricUnit < 0) {
                    cout << "\nThe input was invalid.\nMust be greater or equal to 0\n";
                }
            } while (metricUnit < 0); //keep trying until input is valid

            //Now input is valid and we can compute english units
            switch (userSelection) {
                case 1:
                    englishUnit = metricUnit * 0.394;
                    cout << metricUnit << " cm is equivalent to " << englishUnit << " inch(es).\n";
                    break;
                case 2:
                    englishUnit = metricUnit * 0.264;
                    cout << metricUnit << " l is equivalent to " << englishUnit << " gallon(s).\n";
                    break;
                case 3:
                    englishUnit = metricUnit * 0.622;
                    cout << metricUnit << " km is equivalent to " << englishUnit << " mile(s).\n";
                    break;
                case 4:
                    englishUnit = metricUnit * 2.2;
                    cout << metricUnit << " kg is equivalent to " << englishUnit << " pound(s).\n";
                    break;
                default:
                    cout << "Should never get here either";
            } //end switch (userSelection) {}

        } //end if (userSelection != 5) {}

    } while (userSelection != 5); //continue with execution until EXIT is choosen

    return 0;
}
