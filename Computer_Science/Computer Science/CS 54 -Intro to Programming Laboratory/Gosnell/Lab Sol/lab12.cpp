//original file created by:
//Programmer: Mark Schisler
//Class: CS-53
//File: math.cpp
//Purpose: to provide an output for a function

#include <iostream>
#include <cmath>    //for the pow() call

using std::pow;     //instead of flooding the namespace, we'll
using std::cout;    // only include the specific things from the 
using std::cin;     // new headers that we'll be using ...
using std::endl;

///////////////////////////////////////////
//pre:  x,y,z !=0
//post: f is outputed
//f() outputs the value of a math function
double f(int x, double y, double z);

int main()
{
    //our function requires 3 variables (3 user inputs)
    int    x = 0;
    double y = 0;
    double z = 0;

    do { //forces non-zero input for all values
        cout << "Fantastic Function Finder\n"
                "x must be an integer & x,y,z != 0" << endl;
        cout << "Please enter x:" << endl;
        cin  >> x;

        cout << "Please enter y:" << endl;
        cin  >> y;

        cout << "Please enter z:" << endl;
        cin  >> z;
    //repeat loop if any number is 0
    } while (x==0 || y==0 || z==0);

    //computes and outputs the value
    cout << "\n\nThe function output is:" << f(x,y,z) << endl;

    return 0;
}

double f(int x, double y, double z)
{
    return (((9*y)-(10/z)*(6%x))/(2*pow(y,3)));
}
