/*

File Name:     hw8.cpp

Author:        Jennifer Leopold

Email Address: leopoldj@umr.edu

Description:   CS 53 - Homework Assignment #8

               Program to get input for up to 10 Doom3(TM) monsters, 
			   maintaining this information as an array of Monster objects.
			   Then display the list of monsters sorted by name, and 
			   the list sorted by health rating.

Date:          12/10/2004

*/

#include <iostream>
#include <iomanip>
#include <string>
#include "Monster.h"
using namespace std;

#define MAX_MONSTERS 10

// Function declarations
bool exists(const Monster m[], const int numMonsters, Monster newMonster);
void getListOfMonsters(Monster m[], int& numMonsters);
void printColumnHeadings();
void printMonster(const Monster m);
void printListOfMonsters(Monster m[], const int numMonsters);
void sortByHealthRating(Monster m[], const int numMonsters);
int findHighestRating(const Monster m[], const int numMonsters, const int start);
void sortByName(Monster m[], const int numMonsters);
int findLowestName(const Monster p[], const int numMonsters, const int start);

/****************************************************************************
Function name: exists

Description:   See if specified monster exists in the list.

Parameters:    Array of Monster objects.
               (int) number of monsters in the list.
			   Monster to look for in the list.

Returns:       true if monster already exists; otherwise, false
****************************************************************************/
bool exists(const Monster m[], const int numMonsters, Monster newMonster) {
bool found = false;
int i = 0;

  while ((i < numMonsters) && (! found))
    if (newMonster == m[i])
	  found = true;
	else i++;

  return(found);
}

/****************************************************************************
Function name: getListOfMonsters

Description:   Create array of information about monsters.

Parameters:    Array of Monster objects.
               (int) number of monsters in the list.

Returns:       None (parameters passed by reference).
****************************************************************************/
void getListOfMonsters(Monster m[], int& numMonsters) {
char another, ch;
Monster newMonster;

  numMonsters = 0;
  do {
    cin >> newMonster;
	// Don't add duplicates to list
	if (! exists(m, numMonsters, newMonster)) {
	  m[numMonsters] = newMonster;
	  numMonsters++;
	}
	else cout << "\nThat monster already exists in the list!\n";
	if (numMonsters < MAX_MONSTERS) {
      cout << "Do you want to enter another? (Y/N) ";
	  cin >> another;
	  cin.get(ch);  // "Eat" \n from last input
	}
	else another = 'N'; 
  } while ((another == 'Y') || (another == 'y'));
  return;
}

/****************************************************************************
Function name: printColumnHeadings

Description:   Print column headings for monsters' information.

Parameters:    None.

Returns:       Nothing.
****************************************************************************/
void printColumnHeadings() {
  cout.unsetf(ios::right);
  cout.setf(ios::left);
  cout << endl << setw(10) << setfill(' ') << "GAME";
  cout << setw(25) << setfill(' ') << "NAME";
  cout << setw(25) << setfill(' ') << "WEAPONS";
  cout << "RATING\n";
  cout << setw(66) << setfill('_') << " " << endl;
  return;
}

/****************************************************************************
Function name: printListOfMonsters

Description:   Print list of monster info to screen.

Parameters:    Array of Monster objects.
               (int) number of monsters in the list.

Returns:       Nothing.
****************************************************************************/
void printListOfMonsters(Monster m[], const int numMonsters) {
int i;

  for (i = 0; i < numMonsters; i++)
	cout << m[i];

  return;
}

/****************************************************************************
Function name: sortByHealthRating

Description:   Sort Monster array in descending order by health rating.

Parameters:    m is array of Monster objects.
               numMonsters is (int) number of Monster objects to process.

Returns:       (m array contents will be reordered)
****************************************************************************/
void sortByHealthRating(Monster m[], const int numMonsters) {
Monster temp;
int indexToSwap;

  for (int i = 0; i < numMonsters; i++) {
	indexToSwap = findHighestRating(m, numMonsters, i);
	temp = m[i];
	m[i] = m[indexToSwap];
	m[indexToSwap] = temp;
  }
  return;
}

/****************************************************************************
Function name: findHighestRating

Description:   Find index position of Monster struct with highest health
               rating among start..(count - 1) in the m array.

Parameters:    m is array of Monster objects.
               numMonsters is (int) number of elements in the m array.
			   start is (int) index position to start looking at in array.

Returns:       index position of Monster element with highest rating among
                 start..(count - 1) in the m array. 
****************************************************************************/
int findHighestRating(const Monster m[], const int numMonsters, const int start) {
float maxRating = m[start].getHealthRating();
int maxRatingIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (m[i].getHealthRating() > maxRating) {
		maxRating = m[i].getHealthRating();
		maxRatingIndex = i;
	}
      
  return(maxRatingIndex);
}

/****************************************************************************
Function name: sortByName

Description:   Sort Monster array in ascending order by name.

Parameters:    m is array of Monster structures.
               numMonsters is (int) number of Monster structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/
void sortByName(Monster m[], const int numMonsters) {
Monster temp;
int indexToSwap;

  for (int i = 0; i < numMonsters; i++) {
	indexToSwap = findLowestName(m, numMonsters, i);
	temp = m[i];
	m[i] = m[indexToSwap];
	m[indexToSwap] = temp;
  }
  return;
}

/****************************************************************************
Function name: findLowestName

Description:   Find index position of Monster struct with lowest last 
               name (alphabetically) among start..(count - 1) in the m array.

Parameters:    m is array of Monster objects.
               numMonsters is (int) number of elements in the m array.
			   start is (int) index position to start looking at in array.

Returns:       index position of Monster element with highest name among
                 start..(count - 1) in the m array. 
****************************************************************************/
int findLowestName(const Monster m[], const int numMonsters, const int start) {
string minName = m[start].getName();
int minAvgIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (m[i].getName() < minName) {
		minName = m[i].getName();
		minAvgIndex = i;
	}
      
  return(minAvgIndex);
}

// Begin program execution here
int main()
{
Monster monsters[MAX_MONSTERS];
int count;

  getListOfMonsters(monsters, count);

  sortByHealthRating(monsters, count);

  cout << "\nList of Monsters Sorted by Health Rating\n";
  printColumnHeadings();
  printListOfMonsters(monsters, count);

  sortByName(monsters, count);

  cout << "\nList of Monsters Sorted by Name\n";
  printColumnHeadings();
  printListOfMonsters(monsters, count);

  return(0);
}
