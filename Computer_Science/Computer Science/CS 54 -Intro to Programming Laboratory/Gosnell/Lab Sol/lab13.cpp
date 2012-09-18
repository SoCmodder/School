/******************************************************
 * Mike Gosnell
 * Sample Solution for lab 13
 * Week 10 CS 54
 ******************************************************/

/******************************************************
 * A fast food vendor sells pizza slices ($1.25),
 * French fries ($1.00), and soft drinks ($.75).
 * Write a program to compute a customer’s bill.
 * The program should request the quantity of each
 * item ordered in a subprogram, calculate the
 * Total Cost with a function, and use a void function
 * to display an itemized bill on the screen and in a
 * file called "food.out". This program should check
 * for negative input. If negative input is given, the
 * program should ask for correct input until a correct
 * answer is given.
 ******************************************************/

/********************
 * In my sample solutions whenever possible,
 * I've allowed an easy way for the program to
 * be updated to allow more runs.  In this example,
 * I've attempted to do as much as possible to facilitate
 * more items being included in the calculations through
 * adding additional constants in the heading section
 *
 * With the use of arrays, we could easily account for
 * any number of inputs. However, as arrays haven't been
 * covered in class yet, this solution is still 'clunky' in
 * that a change in # of items would require adding cases
 * to our functions ...
 ********************/

#include <iostream> //for cin & cout
#include <fstream>  //for ifstream & ofstream
#include <cstdlib>  //for exit(1)
#include <iomanip>  //for setw() function
#include <string>   //for std::string (names of items)

//GLOBAL DIRECTIVES////////////////////////////////////
using std::string;
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//CONSTANT HEADING SECTION
//
//Update this accordingly to allow for more inputs
///////////////////////////////////////////////////////
//
// NOTE - Items begin at 1 and end with TOTALITEMS
//total # of items
const int TOTALITEMS = 3;

//each item has a string description and a cost in $
const string ITEM1 = "Pizza Slices :";
const double COST1 = 1.25;

const string ITEM2 = "French Fries :";
const double COST2 = 1.00;

const string ITEM3 = "Soft Drinks  :";
const double COST3 = 0.75;

//Implementation With Arrays///////////////////////////
//total # of items
//const int TOTALITEMS = 3;
//
//const string ITEMS[totalItems] =
//   {"EMPTY", "Pizza Slices :", "French Fries :", "Soft Drinks  :"};
//
//const double COST[totalItems] =
//   {0, 1.25, 1.00, 0.75};
//
//
//END CONSTANTS
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
//FUNCTION DECLARATIONS
void obtainInput(int itemNumber, int& numItems);
void calculateCost(int itemNumber, int numItems, double& itemCost);
void outputResults(int itemNumber, int numItems, double itemCost, std::ostream& ourOutput);
void displayFile(const char* fileName);
//END FUNCTION DECLARATIONS
///////////////////////////////////////////////////////

int main() {
    //LOCAL DIRECTIVES/////////////////////////////////////
    using std::ofstream;
    ///////////////////////////////////////////////////////

    //we'll use this to reference our file we create
    const char* myFileName = "food.out";

    int currentNumItems;
    double currentCost, totalCost(0); //we know total cost is initially 0

    //sets up an output file stream called to_file
    ofstream to_file;
    to_file.open(myFileName);

///NON-ARRAY IMPLEMENTATION START//////////////////////
    //output initial line indicating column names ...
    outputResults(0, currentNumItems, currentCost, to_file);

    //create food.out file (note that the outputResults function uses our ofstream)
    for (int x = 1; x <= TOTALITEMS; ++x) {
        obtainInput(x, currentNumItems);
        calculateCost(x, currentNumItems, currentCost);
        totalCost += currentCost;
        outputResults(x, currentNumItems, currentCost, to_file);
    }
    //output final line with total displayed ...
    outputResults((1 + TOTALITEMS), -1, totalCost, to_file);
///NON-ARRAY IMPLEMENTATION END////////////////////////
//
///ARRAY IMPLEMENTATION START//////////////////////////
//    for (int x = 0; x <= TOTALITEMS; ++x) {
//        obtainInput(x, currentNumItems);
//        calculateCost(x, currentNumItems, currentCost);
//        totalCost += currentCost;
//        outputResults(x, currentNumItems, currentCost, to_file);
//    }
//    outputResults(TOTALITEMS + 1, -1, totalCost, to_file);
///ARRAY IMPLEMENTATION END////////////////////////////

    //close food.out file
    to_file.close();

    //we've written the output 'food.out' file ...
    //but still need to display everything to the screen
    displayFile(myFileName);

    return 0;
} //end int main()

///////////////////////////////////////////////////////
//Pre:  none
//Post: calling numItems variable contains a non-negative
//      value = to the # of <item#> item being ordered
///////////////////////////////////////////////////////
void obtainInput(int itemNumber, int& numItems) {
    //LOCAL DIRECTIVES/////////////////////////////////////
    using std::cout;
    using std::cin;
    ///////////////////////////////////////////////////////
    do {
        cout << "Enter the number of ";
        switch(itemNumber) {
            case 1:
                cout << ITEM1;
                cin >> numItems;
                break;

            case 2:
                cout << ITEM2;
                cin >> numItems;
                break;

            case 3:
                cout << ITEM3;
                cin >> numItems;
                break;

            default:
                cout << "invalid itemNumber passed to calculateCost\n" << std::endl;
                exit(1);
        }
    } while (numItems < 0);
    //with arrays, we would do
    //do {
    //    cout << "Enter the number of " << ITEM[itemNumber];
    //    cin >> numItems;
    //} while(numItems < 0);
    return;
}

///////////////////////////////////////////////////////
//Pre:  none
//Post: itemCost will contain the cost of numItems
//       at the cost per item known to the program
///////////////////////////////////////////////////////
void calculateCost(int itemNumber, int numItems, double& itemCost) {
    switch(itemNumber) {
        case 1:
            itemCost = numItems * COST1;
            break;

        case 2:
            itemCost = numItems * COST2;
            break;

        case 3:
            itemCost = numItems * COST3;
            break;

        default:
            std::cout << "invalid itemNumber passed to calculateCost\n" << std::endl;
            exit(1);
    }
    //with an array, we would do
    //itemCost = numItems * Cost[itemNumber];
    return;
}

///////////////////////////////////////////////////////
//Pre:  none
//Post: The current line from the specified output (bill)
//       is output to the 'ourOutput' output stream
//
// ourOutput could be cout or a file, BUT since we do it
//  per given line, it follows that we'd only do this to
//  a file for this program...
///////////////////////////////////////////////////////
void outputResults(int itemNumber, int numItems, double itemCost, std::ostream& ourOutput) {
    //LOCAL DIRECTIVES/////////////////////////////////////
    using std::cout;
    using std::cin;
    using std::endl;
    using std::ios;
    using std::setw;
    ///////////////////////////////////////////////////////

    ourOutput.setf(ios::fixed); //sets up output more in $ format
    ourOutput.precision(2);     //to always include cents
    //(ios::showpoint) <- don't include so quantity isn't displayed as 1.00

    switch(itemNumber) {
        case 0:
            ourOutput << setw(16) << "ITEM" << setw(16) << "QUANTITY" << setw(16) << "TOTAL COST" << endl;
            break;
        case 1:
            ourOutput << setw(16) << ITEM1 << setw(16) << numItems << setw(16) << itemCost << endl;
            break;
        case 2:
            ourOutput << setw(16) << ITEM2 << setw(16) << numItems << setw(16) << itemCost << endl;
            break;
        case 3:
            ourOutput << setw(16) << ITEM3 << setw(16) << numItems << setw(16) << itemCost << endl;
            break;
        case 4:
            ourOutput << endl << endl;
            ourOutput << setw(32) << "Purchase Total:" << setw(16) << itemCost << endl;
            break;
        default:
            cout << "invalid itemNumber passed to outputResults\n" << endl
                 << itemNumber << endl << endl;
            exit(1);
    }

//with arrays, we would do
//    if (itemNumber == 0) { //takes care of the first output
//        ourOutput << setw(16) << "ITEM"
//                  << setw(16) << "QUANTITY"
//                  << setw(16) << "TOTAL COST" << endl;
//    }
//    else {
//        if (itemNumber == 1 + TOTALITEMS) { //takes care of the last output
//            ourOutput << endl << endl;
//            ourOutput << setw(32) << "Purchase Total:"
//                      << setw(16) << itemCost << endl;
//        }
//        else { //default output
//            ourOutput << setw(16) << ITEM[itemNumber]
//                      << setw(16) << numItems
//                      << setw(16) << itemCost << endl;
//        }
//    }
    return;
}


///////////////////////////////////////////////////////
//This function outputs the entire 'fileName' file to the screen
// (one character at a time)
//
//Pre:  fileName exists
//Post: the data is <cout> as strings one line at a time
///////////////////////////////////////////////////////
void displayFile(const char* fileName) {
    //LOCAL DIRECTIVES/////////////////////////////////////
    //using std::cout;
    //using std::ifstream;
    //above statements left out to show the other way you can do output
    // within the new file headers ...
    ///////////////////////////////////////////////////////
    char a; //temporary character buffer:  input -> output

    std::ifstream in_file(fileName);
    if (in_file.fail()) {exit (2);} //make sure file is open

    while (! in_file.eof()) { //until we get to the end of the file
        in_file.get(a); //gets a single character
        std::cout << a;     //output each character to the screen
    }

    in_file.close();

    std::cout << std::endl; //throw an extra line of output to be safe
    return;
}
