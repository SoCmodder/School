/* programmer: robertoMurillo   date: 10/19/05 *
 * instructor: price            class: cs54d   *
 * file: addrBook.cpp                            *
 * purpose: includes functions for             *
 *          the address book.                  */

#include <iostream>
#include <cstring>
using namespace std;

#include "addrBook.h"

void fillAll(contact cont[], int &index)
    {
    index = 0;

    cont[index].fname = "George";
    cont[index].lname = "Washington";
    cont[index].city  = "Mount Vernon";
    cont[index].state = "VA";
    cont[index].zip   = 10001;
    ++index;

    cont[index].fname = "John";
    cont[index].lname = "Adams";
    cont[index].city  = "Arlington";
    cont[index].state = "VA";
    cont[index].zip   = 10010;
    ++index;

    cont[index].fname = "Thomas";
    cont[index].lname = "Jefferson";
    cont[index].city  = "Monticello";
    cont[index].state = "VA";
    cont[index].zip   = 10011;
    ++index;

    cont[index].fname = "James";
    cont[index].lname = "Madison";
    cont[index].city  = "Arlington";
    cont[index].state = "VA";
    cont[index].zip   = 10010;
    ++index;

    cont[index].fname = "James";
    cont[index].lname = "Monroe";
    cont[index].city  = "Sometown";
    cont[index].state = "VA";
    cont[index].zip   = 12345;
    ++index;

    cont[index].fname = "John Quincy";
    cont[index].lname = "Adams";
    cont[index].city  = "Sometown";
    cont[index].state = "VA";
    cont[index].zip   = 12345;
    ++index;

    cont[index].fname = "Martin";
    cont[index].lname = "Short";
    cont[index].city  = "Hollywood";
    cont[index].state = "CA";
    cont[index].zip   = 54321;
    ++index;

    cont[index].fname = "Jenny";
    cont[index].lname = "Harrison";
    cont[index].city  = "Hollywood";
    cont[index].state = "CA";
    cont[index].zip   = 54321;
    ++index;

    return;
    }

void printOne(contact & cont)
    {
    cout << cont.lname << ", " << cont.fname << "    " << cont.city << ", "
        << cont.state << " " << cont.zip << endl;
    return;
    }

// prints all of the contacts in the array
void printAll( contact cont [ ], const int filled )
{
  for ( int i = 0; i < filled; i++ )
    printOne(cont[i]);

  return;
}

// user enters in all of the contact info here
void fillOne( contact & cont )
{
  cout << "Enter first name: ";
  cin >> cont.fname;
  cout << "Enter last name: ";
  cin >> cont.lname;
  cout << "Enter city: ";
  cin >> cont.city;
  cout << "Enter state: ";
  cin >> cont.state;
  cout << "Enter zip code: ";
  cin >> cont.zip;

  return;
}

// looks up the last name entered, if none, then the message is produced
void lookup( contact cont[ ], const int filled, const string lname )
{
  int count = 0;

  for ( int i = 0; i < filled; i++ )
  {
    if( cont[i].lname == lname )
    {
      printOne(cont[i]);
      count++;
    }
  }

  if ( count == 0 )
    cout << "No one was found!" << endl;

  return;
}

// looks up the zip code entered, if none, produces the message None
void lookup( contact cont[ ], const int filled, const int zip )
{
  int count = 0;

  for ( int i = 0; i < filled; i++ )
  {
    if ( cont[i].zip == zip )
      printOne(cont[i]);
      count++;
  }

  if( count == 0 )
    cout << "No one was found!" << endl;

  return;
}

