#include <iostream>
using namespace std;

#include <string>
#include <cstring>

struct monsterInfo {
	string monsterName;
	string monsterWeapons;
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
void printMonster(monsterInfo m);
void printListOfMonsters(monsterInfo m[],  int& numMonsters);
//void sortByHealthRatingmonsterInfo m[],  int numMonsters);
//int findHighestRating(monsterInfo m[],  int numMonsters,  int start);
//void sortByName(monsterInfo m[],  int numMonsters);
//int findLowestName(monsterInfo p[],  int numMonsters,  int start);

/****************************************************************************
Function name: getName

Description:   Read in a monster's name.

Parameters:    None.

Returns:       (string) name entered.
****************************************************************************/
string getName()
{
	string name;
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
	string weapons;
	cout << "Enter the monsters weapon(s):";
	cin.ignore();
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
	cout << "Enter the monsters health:";
	cin.ignore();
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

	return(monster);
}

/****************************************************************************
Function name: getListOfMonsters

Description:   Create array of information about monsters.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       None (parameters passed by reference).
****************************************************************************/
void getListOfMonsters(monsterInfo m[], int& numMonsters)
{
   char choice = 'y';

   do
   {
	   m[numMonsters] = getMonster();

	   cout << "Do you want to enter another? (Y/N)";
	   cin >> choice;

	   if(choice == 'y' || choice == 'Y')
		   numMonsters++;

   } while(choice == 'y' || choice == 'Y');

   return;
}
/****************************************************************************
Function name: printColumnHeadings

Description:   Print column headings for monsters' information.

Parameters:    None.

Returns:       Nothing.
****************************************************************************/
void printColumnHeadings()
{
	cout << "\nNAME                      WEAPON(S)                RATING\n"
		 << "_________________________________________________________\n";
}

/****************************************************************************
Function name: printListOfMonsters

Description:   Print list of monster info to screen.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       Nothing.
****************************************************************************/
void printListOfMonsters( monsterInfo m[],  int& numMonsters)
{

	for(int i = 0; i <= numMonsters; i++)
	{
		cout << m[i].monsterName;
		
		for(int x = 1; x <= (26 - (m[i].monsterName.length())); x++)
			cout << " ";

		cout << m[i].monsterWeapons;

		for(x = 1; x <= (25 - (m[i].monsterWeapons.length())); x++)
			cout << " ";

		cout << m[i].health << endl;
	}
}

/****************************************************************************
Function name: sortByHealthRating

Description:   Sort monsterInfo array in descending order by health rating.

Parameters:    m is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (m array contents will be reordered)
****************************************************************************/
void sortByHealthRating(monsterInfo m[],  int& numMonsters)
{
	monsterInfo temp;

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
int count = 0;

  getListOfMonsters(monsters, count);

  sortByHealthRating(monsters, count);

  cout << "\nList of Monsters Sorted by Health Rating\n";
  printColumnHeadings();
  printListOfMonsters(monsters, count);

//  sortByName(monsters, count);

  cout << "\nList of Monsters Sorted by Name\n";
  printColumnHeadings();
  printListOfMonsters(monsters, count);

  return(0);
}
