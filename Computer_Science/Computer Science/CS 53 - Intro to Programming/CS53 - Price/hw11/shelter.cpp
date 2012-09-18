/* programmer: robertoMurillo
 * date: 11/30/05
 * file: shelter.cpp
 * purpose: a shelter for all the cats and dogs.
 */

#include "shelter.h"
#include <iostream>
using namespace std;

/********** DEFINITIONS **********/

// the default constructor.
// pre: none.
// post: variable are given default values.
shelter::shelter()
{
  m_sheltName = "municipal";
  m_numcats = 0;
  m_numdogs = 0;
}

// the user-manipulated constructor.
// pre: a name, # of cats, and # of dogs must be passed.
// post: the member variables are given the values passed to the fnct.
shelter::shelter(string name, int cats, int dogs)
{
  m_sheltName = name;
  m_numcats = cats;
  m_numdogs = dogs;
}

// The op >> () function will extract a shelter in specified format if
// called.
// Pre: file must be in right format.
// Post: a shelter is input to the calling object in the specified format.
istream& operator >>(istream & in, shelter& s)
{
  char sheltName[1000];

  in.getline(sheltName, 1000, '\n'); // turns shelter name into NTCA

  s.m_sheltName = sheltName; // sets the NTCA shelter name to the member
                             // variable
  in >> s.m_numcats; // inputs the cats
  in >> s.m_numdogs; // inputs the dogs

  for (int i = 0; i < s.m_numcats; i++)
    in >> s.cats[i];

  for (int i = 0; i < s.m_numdogs; i++)
    in >> s.dogs[i];

  return in;
}

// the operator << overloads the << operator to output shelters
// pre: none
// post: outputs a shelter to the ostream.
ostream& operator <<(ostream & o, const shelter& s)
{
  if ( s.m_numcats == 0 && s.m_numdogs == 0 )
    o << "The " << s.m_sheltName << " shelter is empty." << endl;

  else
    o << s.m_sheltName << " shelter contains:" << endl;
    o << "cats---" << endl;
    for ( int i = 0; i < s.m_numcats; i++ )
      o << "        " << s.cats[i];

    o << "dogs---" << endl;
    for ( int i = 0; i < s.m_numdogs; i++ )
      o << "        " << s.dogs[i];

  return o;
}

// the open_cages () fnct opens cages in the shelter.
// Pre: none.
// Post: outputs the stats of the shelter and runs the fight function
//       until a winner is declared.
void shelter::open_cages()
{
  bool catsWin = false;
  bool dogsWin = false;

  do
  {
    cout << *this << endl << endl; // outputs stats of shelter.
                                   // while fight funct is true.
  } while ( fight(cats, dogs, m_numcats, m_numdogs) );

  cout << *this << endl; // outputs final stats.

  for (int i = 0; i < m_numcats; i++) // checks to see which is the winner
    if (cats[i].m_isAlive == true)
      catsWin = true;

  for (int i = 0; i < m_numdogs; i++)
    if (dogs[i].m_isAlive == true)
      dogsWin = true;

  if (dogsWin)
    cout << "WINNER: To the dogs go the spoils." << endl;

  else if (catsWin)
    cout << "WINNER: To the cats go the spoils." << endl;

  else
    cout << "Oh noes!  It was a draw!" << endl;

  return;
}

// The op + functions add a cat or a dog depending on which the program
// is trying to add.
// Pre: none.
// Post: the functions check to see if the cats/dogs array is full, and if
//       not, it adds the new cat or dog at the end of the array and sorts
//       the array.
void shelter::operator +(cat & cat1)
{
  if ( m_numcats < SIZE )
  {
    cats[m_numcats] = cat1;
    m_numcats++;
    selectSort(cats, m_numcats); // sorts the array from weakest to
                                 // strongest
  }

  return;
}

// The op + functions add a cat or a dog depending on which the program
// is trying to add.
// Pre: none.
// Post: the functions check to see if the cats/dogs array is full, and if
//       not, it adds the new cat or dog at the end of the array and sorts
//       the array.
void shelter::operator +(dog & dog1)
{
  if ( m_numdogs < SIZE )
  {
    dogs[m_numdogs] = dog1;
    m_numdogs++;
    selectSort(dogs, m_numdogs);  // sorts the array from weakest to
                                  // strongest
  }

  return;
}

// The fight () function calculates fitness and kills 1 of the winning
// animals and two of the losing animals.
// Pre: none.
// Post: compares the fitnesses, determines the winner, kills 1 of the
// winning animals and 2 of the losing animals. then it checks to see if
// there is 1 live animal of cats and dogs and returns true if so, and
// fals if not.
bool fight(cat cats[ ], dog dogs[ ], int numcats, int numdogs)
{
  float sumOfCatsFit = 0; // cats fitness
  int sumCatsAlive = 0; // cats left alive
  float sumOfDogsFit = 0; // dogs fitness
  int sumDogsAlive = 0; // dogs left alive
  int i = 0; // variable used in the array for dogs
  int j = 0; // variable used in the array for cats
  bool stillFighting = false;

  for (i = 0; i < numcats; i++)
  {
    // calculates the fitness for all the alive cats!
    if (cats[i].getlife())
    {
      sumCatsAlive++;
      sumOfCatsFit += ((cats[i].gettype() + cats[i].getclaws()) *
                       (cats[i].getweight()/cats[i].getage()));
    }
  }

  sumOfCatsFit /= sumCatsAlive; // totals the fitness of the cats alive!

  for (i = 0; i < numdogs; i++)
  {
    // calculates the fitness for all the alive dogs!
    if (dogs[i].getlife())
    {
      sumDogsAlive++;
      sumOfDogsFit += ((dogs[i].gettype() + dogs[i].getteeth()) *
                       (dogs[i].getweight()/dogs[i].getage()));
    }
  }

  sumOfDogsFit /= sumDogsAlive; // totals the fitness of the dogs alive!

  // compares the two fitnesses and chooses the winner of the fight.
  // ( in this case it would be dogs ).
  // also sets 1 cat/dog and 2 cats/dogs dead depending on the winner of
  // the fight.
  if (sumOfDogsFit > sumOfCatsFit)
  {
    i = 0;
    while (!dogs[i].getlife() && i < numdogs) {
    i++;
    }

    if (i < numdogs)
    {
      dogs[i].setdead();
      i++;
    }

    j = 0;
    while (!cats[j].getlife() && j < numcats) {
        j++;
    }

    if (j < numcats)
    {
      cats[j].setdead();
      j++;
    }

    if (j < numcats)
    {
      cats[j].setdead();
      j++;
    }
  }

  // compares the two fitnesses and chooses the winner of the fight.
  // ( in this case it would be cats ).
  // also sets 1 cat/dog and 2 cats/dogs dead depending on the winner of
  // the fight.
  else if (sumOfCatsFit > sumOfDogsFit)
  {
    j = 0;
    while (!cats[j].getlife() && j < numcats) {
    j++;
    }

    if (j < numcats)
    {
      cats[j].setdead();
      j++;
    }

    i = 0;
    while (!dogs[i].getlife() && i < numdogs) {
        i++;
    }

    if (i < numdogs)
    {
      dogs[i].setdead();
      i++;
    }

    if (i < numdogs)
    {
      dogs[i].setdead();
      i++;
    }
  }

  // the two fitnesses are equal so what do we do?!
  // we kill one of each animal!
  else
  {
    i = 0;
    while (!dogs[i].getlife() && i < numdogs) {
    i++;
    }

    if (i < numdogs)
    {
    dogs[i].setdead();
    i++;
    }

    j = 0;
    while (!cats[j].getlife() && j < numcats) {
    j++;
    }

    if (j < numcats)
    {
      cats[j].setdead();
      j++;
    }
  }

  // checks to see if there are still cats and dogs left.
  if (j < numcats && i < numdogs)
    stillFighting = true;

  return stillFighting;
}


/********** DEFINITIONS **********/



