/*

File Name:     hw5.cpp

Author:        Jennifer Leopold

Email Address: leopoldj@umr.edu

Description:   CS 53 - Homework Assignment #5

               Program to get input for up to 10 Doom3(TM) monsters, 
			   maintaining this information in an array of structs.
			   Then display the list of monsters sorted by name, and 
			   the list sorted by health rating.

Date:          11/5/2004

*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#define MAX_MONSTERS 10
#define MAX_STRING_LENGTH 25

struct monsterInfo {
	string name;
	string weapons;
	int healthRating;
};

// Function declarations
string getName();
string getWeapons();
monsterInfo getMonster();
void getListOfMonsters(monsterInfo m[], int& numMonsters);
void printColumnHeadings();
void printMonster(const monsterInfo m);
void printListOfMonsters(const monsterInfo m[], const int numMonsters);
void sortByHealthRating(monsterInfo m[], const int numMonsters);
int findHighestRating(const monsterInfo m[], const int numMonsters, const int start);
void sortByName(monsterInfo m[], const int numMonsters);
int findLowestName(const monsterInfo p[], const int numMonsters, const int start);

/****************************************************************************
Function name: getName

Description:   Read in a monster's name.

Parameters:    None.

Returns:       (string) name entered.
****************************************************************************/
string getName() {
char cname[MAX_STRING_LENGTH];
string name;

  cout << "\nEnter monster's name: ";
  cin.getline(cname, MAX_STRING_LENGTH-1);
  name = cname;
  return(name);
}

/****************************************************************************
Function name: getWeapons

Description:   Read in a monster's weapon(s).

Parameters:    None.

Returns:       (string) weapon(s) entered.
****************************************************************************/
string getWeapons() {
char cweapons[MAX_STRING_LENGTH];
string weapons;

  cout << "Enter monster's weapon(s): ";
  cin.getline(cweapons, MAX_STRING_LENGTH-1);
  weapons = cweapons;
  return(weapons);
}

/****************************************************************************
Function name: getMonster

Description:   Get user's input for information about a monster.

Parameters:    None

Returns:       monsterInfo struct.
****************************************************************************/
monsterInfo getMonster() {
monsterInfo monster;

  monster.name = getName();
  monster.weapons = getWeapons();
  cout << "Enter monster's health rating: ";
  cin >> monster.healthRating;
 
  return(monster);
}

/****************************************************************************
Function name: getListOfMonsters

Description:   Create array of information about monsters.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       None (parameters passed by reference).
****************************************************************************/
void getListOfMonsters(monsterInfo m[], int& numMonsters) {
char another, ch;

  numMonsters = 0;
  do {
    m[numMonsters] = getMonster();
	numMonsters++;
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
int i;

  cout << "\nNAME";
  for (i = 1; i < MAX_STRING_LENGTH - 3; i++)
	  cout << " ";
  cout << " WEAPON(S)";
  for (i = 1; i < MAX_STRING_LENGTH - 9; i++)
	  cout << " ";
  cout << " RATING\n";

  // Underline column headings
  for (i = 1; i <= 7 + (MAX_STRING_LENGTH * 2); i++)
    cout << "_";
  cout << endl;
  return;
}

/****************************************************************************
Function name: printListOfMonsters

Description:   Print list of monster info to screen.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       Nothing.
****************************************************************************/
void printListOfMonsters(const monsterInfo m[], const int numMonsters) {
int i;

  for (i = 0; i < numMonsters; i++) {
	cout.unsetf(ios::right);
    cout.setf(ios::left);
    cout << setw(MAX_STRING_LENGTH + 1) << m[i].name;
    cout << setw(MAX_STRING_LENGTH + 2) << m[i].weapons;
	cout.unsetf(ios::left);
	cout.setf(ios::right);
    cout << setw(4) << m[i].healthRating << endl;
  }

  return;
}

/****************************************************************************
Function name: sortByHealthRating

Description:   Sort monsterInfo array in descending order by health rating.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/
void sortByHealthRating(monsterInfo m[], const int numMonsters) {
monsterInfo temp;
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

Description:   Find index position of monsterInfo struct with highest health
               rating among start..(count - 1) in the m array.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of elements in the m array.
			   start is (int) index position to start looking at in array.

Returns:       index position of monsterInfo element with highest rating among
                 start..(count - 1) in the m array. 
****************************************************************************/
int findHighestRating(const monsterInfo m[], const int numMonsters, const int start) {
float maxRating = m[start].healthRating;
int maxRatingIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (m[i].healthRating > maxRating) {
		maxRating = m[i].healthRating;
		maxRatingIndex = i;
	}
      
  return(maxRatingIndex);
}

/****************************************************************************
Function name: sortByName

Description:   Sort monsterInfo array in ascending order by name.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/
void sortByName(monsterInfo m[], const int numMonsters) {
monsterInfo temp;
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

Description:   Find index position of monsterInfo struct with lowest last 
               name (alphabetically) among start..(count - 1) in the m array.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of elements in the m array.
			   start is (int) index position to start looking at in array.

Returns:       index position of monsterInfo element with highest name among
                 start..(count - 1) in the m array. 
****************************************************************************/
int findLowestName(const monsterInfo m[], const int numMonsters, const int start) {
string minName = m[start].name;
int minAvgIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (m[i].name < minName) {
		minName = m[i].name;
		minAvgIndex = i;
	}
      
  return(minAvgIndex);
}

// Begin program execution here
int main()
{
monsterInfo monsters[MAX_MONSTERS];
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
