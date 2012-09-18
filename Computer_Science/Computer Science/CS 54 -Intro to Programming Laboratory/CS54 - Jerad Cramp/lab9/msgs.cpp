/* programmer: robertoMurillo   date: 10/19/05 *
 * instructor: price            class: cs54d   *
 * file: msgs.cpp                              *
 * purpose: includes hello and goodbye msgs for*
 *          the address book.                  */

#include <iostream>
using namespace std;

#include "msgs.h"

// hello message
void hello()
{
  cout << "Hello and welcome to the Address Book!" << endl;
  cout << endl;

  return;
}

// goodbye message
void goodbye()
{
  cout << endl;
  cout << "Thanks!" << endl;
  cout << endl;

  return;
}
