//Code originally from:
//Programmer: Mark Schisler
//Class: CS-53
//Date: 10-21-2002
//File: gas.cpp
//Purpose: To have a MPG calculator
// with inputs of liters and miles

#include <iostream>

using std::cout; //more efficient way of specifying namespace with
using std::endl; //minimal changes to the way you code ...
using std::cin;

/////////////////////////////////////////////////////////
//LitersToGallons() converts a value in Liters to Gallons
//pre:  liters must be a number (units in liters)
//post: the numbers value in gallons is returned
double LitersToGallons(double Liters);

/////////////////////////////////////////////////////////
//MPG() returns MPG gallon for Liters (gas),
//and Miles (traveled).
//pre:  Liters of gas can not be 0
//post: the number returned will be the corresponding
// miles/gallon ratio for the pair.
double MPG(double Liters, double Miles);

int main()
{
    //user inputs
    double liters = 0;
    double miles  = 0;

    //done is the state of the program - default is not done
    bool done = false;
    int userSelect = 2; //menu selection

    do {//outputs the menu & gets user selection
        cout << "**********" << endl
             << "*  MENU  *" << endl
             << "**********" << endl
             << "1) MPG    " << endl
             << "2) Exit   " << endl
             << "**********" << endl
             << "Make Selection:";
        cin  >> userSelect;

        //perform the appropriate option based on user's menu selection
        switch(userSelect)
        {
            case 1: //perform MPG input, calculation, & output
                do { //loop forces (both) positive input
                    cout << "\nPlease enter the number of Liters used:";
                    cin  >> liters;

                    cout << "\nPlease enter the number of Miles traveled:";
                    cin  >> miles;

                    if (liters <= 0 || miles <= 0)
                        cout << "Inputs must be postitive" << endl;

                } while (liters <= 0 || miles <= 0);

                cout << "You are getting " << MPG(liters, miles) << " MPG!\n" << endl;

                break;

            case 2: //wanted to exit
                done = true;
                break;

            default:
                cout << "Invalid choice\n";
        }

    } while(!done); // ends the main do loop when (menu) 2 is selected

    return 0;
}

double LitersToGallons(double Liters)
{
    return (Liters * 0.264179);
}

double MPG(double Liters, double Miles)
{
    return (Miles / LitersToGallons(Liters));
}
