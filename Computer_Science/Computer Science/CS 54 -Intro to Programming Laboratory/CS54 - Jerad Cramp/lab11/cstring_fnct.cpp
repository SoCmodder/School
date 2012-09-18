/* programmer: robertoMurillo   date: 11/02/05 *
 * instructor: price            class: cs54d   *
 * file: cstring_fnct.cpp                      *
 * purpose: using cstrings and file i/o.       */

#include <iostream>
#include <fstream>
#include <cstring>
#include "cstring.h"
using namespace std;

void welcome()
{
  cout << "Welcome to CS 54's company records program!" << endl
       << endl;

  return;
}

void farewell()
{
  cout << "Thanks for using the program.  Adios!" << endl
       << endl;

  return;
}

void getFileName( string & filename1 )
{
  cout << "Please enter the name of the file to be read: ";
  cin >> filename1;

  return;
}

void processFile( string & filename1 )
{
  ifstream in; // input stream to read from a file
  ofstream out_returns, out_wholesale, out_retail;

  const int REC_LENGTH = 100; // record length
  char record[REC_LENGTH];  // array of the record
  int count = 0;

  // opens the file given from the user
  in.open(filename1.c_str());

  // checks to make sure the file opens
  if (in.fail())
  {
    cout << "Error!  File cannot be opened.";
    return;
  }

  /********** OPENS OUTPUT FILES AND CHECKS THEM **********/

  out_returns.open("returns.txt");
  if (out_retail.fail())
  {
    cout << "Error!  File cannot be opened.";
    return;
  }

  out_wholesale.open("wholesale.txt");
  if (out_wholesale.fail())
  {
    cout << "Error!  File cannot be opened.";
    return;
  }

  out_retail.open("retail.txt");
  if (out_retail.fail())
  {
    cout << "Error!  File cannot be opened.";
    return;
  }

  /********** OPENS OUTPUT FILES AND CHECKS THEM **********/

  // processes all the files and sorts them into returns, retail, or
  // wholesale
  while (!in.eof()) {
    in.getline(record, REC_LENGTH);

    if ( ( record[5] == 'A' || record[5] == 'E' ) && record[20] == '+' )
      out_returns << record;

    if ( isdigit(record[5]) )
      out_wholesale << record;

    else
      out_retail << record;

    count++;
  }

  cout << count << " records were processed." << endl;

  // closes all files
  in.close();
  out_returns.close();
  out_retail.close();
  out_wholesale.close();

  return;
}
