// Programmer: Alton Coalter     Date: 10.08.17
// File: driver.cpp              Class: CS 54
// Instructor: N/A
// Description: Driver file for lab9, using structs and arrays
//              to institute a primitive address book.

#include <iostream>
#include <cstring>
using namespace std;

#include "addrBook.h"
#include "msgs.h"

int
main()
    {
    contact cont[20];
    int     zip, filled;
    string  lname;

    hello();

    filled = 0;
    fillAll(cont, filled);
    cout << "There are now " << filled << " entries in your address book.\n\n";

    cout << "Enter the values for contact number " << filled+1 << ".\n";
    fillOne(cont[filled]);
    ++filled;
    cout << "\nEnter the values for contact number " << filled+1 << ".\n";
    fillOne(cont[filled]);
    ++filled;

    cout << "\n\nContents of address book:\n";
    printAll(cont, filled);
    cout << "\n\n";

    do
        {
        cout << "Enter a zip code to look up or 0 to move on: ";
        cin >> zip;

        if (zip)
            lookup(cont, filled, zip);
        } while (zip);

    do
        {
        cout << "Enter a last name to look up or Q to move on: ";
        cin >> lname;

        if (lname != "Q" && lname != "q")
            lookup(cont, filled, lname);
        } while (lname != "Q" && lname != "q");

    goodbye();
    return 0;
    }
