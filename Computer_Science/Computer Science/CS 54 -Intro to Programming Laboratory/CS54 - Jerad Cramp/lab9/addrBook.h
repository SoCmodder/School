/* programmer: robertoMurillo   date: 10/19/05 *
 * instructor: price            class: cs54d   *
 * file: addrBook.h                            *
 * purpose: includes prototypes and structs for*
 *          the address book.                  */

#ifndef ADDRBOOK_H
#define ADDRBOOK_H

/*************** STRUCTS ***************/

struct contact
{
  string fname; // first name of contact
  string lname; // last name of contact
  string city; // city of contact
  string state; // state of contact
  int zip; // zip code of contact
};

/*************** STRUCTS ***************/

/*************** PROTOTYPES ***************/

void fillAll(contact cont[], int &index);

void printOne(contact & cont);

// prints all contacts in array
void printAll( contact cont[ ], const int filled );

// user enters in contact info here
void fillOne( contact & cont );

// looks up contacts by last name
void lookup(contact cont[ ], const int filled, const string lname);

// looks up contacts by zip code
void lookup(contact cont[ ], const int filled, const int zip);

/*************** PROTOTYPES ***************/

#endif

