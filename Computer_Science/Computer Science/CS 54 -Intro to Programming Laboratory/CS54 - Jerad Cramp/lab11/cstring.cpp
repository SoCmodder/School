/* programmer: robertoMurillo   date: 11/02/05 *
 * instructor: price            class: cs54d   *
 * file: cstring.cpp                      *
 * purpose: using cstrings and file i/o.       */

#include <iostream>
#include "cstring.h"
using namespace std;

int main()
{
  string filename1;

  welcome(); // welcomes user

  getFileName(filename1); // gets the filename from the user
  processFile(filename1); // reads and writes to proper files

  farewell(); // goodbye message

  return 0;
}
