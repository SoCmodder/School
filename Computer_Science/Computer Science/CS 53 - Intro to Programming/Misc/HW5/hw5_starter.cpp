#include <iostream>
using namespace std;

#include <cstring>

struct monsterInfo {
	char monsterName[25];
	char monsterWeapons[25];
	int health;
};

const int MAX_MONSTERS = 10;

// Function declarations
string getName();
string getWeapons();
int getHealth();
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
string getName()
{
	char name[25];
	cout << "Enter monsters name:";
	cin >> name;

	return(name);
}

/****************************************************************************
Function name: getWeapons

Description:   Read in a monster's weapon(s).

Parameters:    None.

Returns:       (string) weapon(s) entered.
****************************************************************************/
string getWeapons()
{
	char weapons[25];
	cout << "Enter the monsters weapon(s):"
	cin >> weapons;

	return(weapons);
}

/****************************************************************************
Function name: getHealth

Description:   Read in a monster's health

Parameters:    None.

Returns:       (int) health entered.
****************************************************************************/
int getHealth()
{
	int health;
	cout << "Enter the monsters health:"
	cin >> health;

	return(health);
}

/****************************************************************************
Function name: getMonster

Description:   Get user's input for information about a monster.

Parameters:    None

Returns:       monsterInfo struct.
****************************************************************************/
monsterInfo getMonster()
{
	monsterInfo monster;

	monster.monsterName = getName();
	monster.monsterWeapons = getWeapons();
	monster.health = getHealth();

/****************************************************************************
Function name: getListOfMonsters

Description:   Create array of information about monsters.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       None (parameters passed by reference).
****************************************************************************/


/****************************************************************************
Function name: printColumnHeadings

Description:   Print column headings for monsters' information.

Parameters:    None.

Returns:       Nothing.
****************************************************************************/


/****************************************************************************
Function name: printListOfMonsters

Description:   Print list of monster info to screen.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       Nothing.
****************************************************************************/


/****************************************************************************
Function name: sortByHealthRating

Description:   Sort monsterInfo array in descending order by health rating.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/


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


/****************************************************************************
Function name: sortByName

Description:   Sort monsterInfo array in ascending order by name.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/


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
