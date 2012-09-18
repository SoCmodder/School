/* programmer: robertoMurillo   date: 11/02/05 *
 * instructor: price            class: cs54d   *
 * file: cstring.h                             *
 * purpose: using cstrings and file i/o.       */

#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>
#include "cstring.h"
using namespace std;

/*************** PROTOTYPES ***************/

void welcome();  // welcomes user

void farewell();  // goodbye message

void getFileName( string & filename1 );  // gets the filename

void processFile( string & filename1 );  // reads and writes to the files
                                        // specified

/*************** PROTOTYPES ***************/

#endif
