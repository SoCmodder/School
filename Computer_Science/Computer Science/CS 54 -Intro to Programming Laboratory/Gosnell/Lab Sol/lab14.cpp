/******************************************************
 * Mike Gosnell
 * Sample Solution for lab 14
 * Week 11 CS 54      (lab 1)
 * 
 * Solution running until the user inputs two 0's
 ******************************************************/

/******************************************************
 * This program implements a function to determine
 * if the user's first number is a multiple of the
 * second input. 
 *
 * The program ends when two 0's are entered as input.
 ******************************************************/

#include <iostream> //for cin & cout

//FUNCTION DECLARATIONS////////////////////////////////
int multipleCheck(int num1, int num2, double& numProd);
//END FUNCTION DECLARATIONS////////////////////////////

int main() {
//LOCAL DIRECTIVES/////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
///////////////////////////////////////////////////////
    int in1, in2;
    double product;

    cout << "To Exit, enter 0 twice\n";

    cout << "Input 2 numbers: ";
    cin >> in1 >> in2;

    while (in1 != 0 && in2 != 0) { //exit when both numbers == 0
	if (multipleCheck(in1, in2, product) == 0) {
	    cout << in1 << " * " << in2 << " = " << product << endl;
	    cout << in1 << " is a multiple of " << in2 << endl << endl;
	}
	else {
	    cout << in1 << " * " << in2 << " = " << product << endl;
	    cout << in1 << " is not a multiple of " << in2 << endl << endl;
	}
        cout << "Input 2 numbers: ";
        cin >> in1 >> in2;
    }

    return 0;
} //end int main()

///////////////////////////////////////////////////////
//Pre:  none
//Post: product is updated & 0 is returned if #1 is a 
//       multiple of #2
///////////////////////////////////////////////////////
int multipleCheck(int num1, int num2, double& numProd) {
    numProd = num1 * num2;
    return num1 % num2;
}
