/* programmer: robertoMurillo
 * date: 11/30/05
 * file: shelter.h
 * purpose: a shelter for all the cats and dogs.
 */

#ifndef SHELTER_H
#define SHELTER_H

#include "cat.h"
#include "dog.h"
#include "sort.h"
using namespace std;

/********** GLOBAL CONSTS **********/

const int SIZE = 20;

/********** GLOBAL CONSTS **********/

/********** CLASS **********/

// The constructors will initialize the shelter object.
// Pre: none.
// Post: variable are given default values.

// The user-manipulated constructor.
// Pre: none.
// Post: the member variables are given the values passed to the fnct.

// The operator << overloads the << operator to output shelters
// Pre: none.
// Post: outputs a shelter to the ostream.

// The op >> () function will extract a shelter in specified format if
// called.
// Pre: file must be in right format.
// Post: a shelter is input to the calling object in the specified format.

// The op + functions add a cat or a dog depending on which the program
// is trying to add.
// Pre: none.
// Post: the functions check to see if the cats/dogs array is full, and
//       if not, it adds the new cat or dog at the end of the array and
//       sorts the array.

// The isFullOfDogs/Cats functions check to see if the cat/dog array is
// full.
// Pre: none.
// Post: a value of true or false is returned depending on if the arrays
//       are full or not.

// The open_cages () fnct opens cages in the shelter.
// Pre: none.
// Post: outputs the stats of the shelter and runs the fight function
//       until a winner is declared.

// The fight () function calculates fitness and kills 1 of the winning
// animals and two of the losing animals.
// Pre: none.
// Post: compares the fitnesses, determines the winner, kills 1 of the
// winning animals and 2 of the losing animals. then it checks to see if
// there is 1 live animal of cats and dogs and returns true if so, and
// fals if not.

// The accessor (get) functions return the value of the associated member.
// Pre: none.
// Post: return value is the value of the associated member.

// The mutator (set) functions return nothing but set the value of the
// assoc'd member equal to the value passed.
// Pre: none.
// Post: member variable is set to value passed.

class shelter
{
  public:
    shelter();
    shelter(string name, int cats, int dogs);
    friend ostream& operator <<(ostream & o, const shelter& s);
    friend istream& operator >>(istream & in, shelter& s);
    void operator +(cat & cat1);
    void operator +(dog & dog1);
    bool isFullofCats(){return (m_numcats == SIZE);}
    bool isFullofDogs(){return (m_numdogs == SIZE);}
    void open_cages();
    friend bool fight(cat cats[ ], dog dogs[ ], int numcats,
                      int numdogs);

    // accessors
    int getNumCats()const {return m_numcats;}
    int getNumDogs()const {return m_numdogs;}
    // mutators
    void setNumCats(int numcats){m_numcats = numcats;}
    void setNumDogs(int numdogs){m_numdogs = numdogs;}

  private:
    string m_sheltName; // shelter name
    int m_numcats; // number of cats
    int m_numdogs; // number of dogs
    cat cats[SIZE]; // array full of cats!
    dog dogs[SIZE]; // array full of dogs!
};

/********** CLASS **********/

#endif

