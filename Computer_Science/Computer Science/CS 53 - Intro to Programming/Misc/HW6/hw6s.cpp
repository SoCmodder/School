/*

File Name:     hw6.cpp

Author:        Matt Ludwikosky

Email Address: mmlpp5@umr.edu

Description:   CS 53 - Homework Assignment #6

               Program that reads in information from a file
			   and outputs that data in a sorted and presentable
			   fashion

Date:          11/9/2004

Note:		   File hw5_solution.cpp as posted on Blackboard is
		       being modified to complete this assignment

*/

#include <iostream>
#include <iomanip>
#include <fstream>
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
string getName(ifstream& infile);
string getWeapons(ifstream& infile);
monsterInfo getMonster(ifstream& infile);
void getListOfMonsters(monsterInfo monsters[], int& numMonsters);
void printColumnHeadings();
void printMonster(const monsterInfo monsters);
void printListOfMonsters(const monsterInfo monsters[], const int numMonsters);
void sortByHealthRating(monsterInfo monsters[], const int numMonsters);
int findHighestRating(const monsterInfo monsters[], const int numMonsters, const int start);
void sortByName(monsterInfo monsters[], const int numMonsters);
int findLowestName(const monsterInfo p[], const int numMonsters, const int start);

void openInputDataFile(ifstream& inStream);
void openOutputDataFile(ofstream& outStream);
void printOneMonster(const monsterInfo s[], ofstream& outStream);
void printAllMonsters(const monsterInfo monsters[], const int numMonsters, ofstream& outStream);
void processUserRequestsFromMenu(const monsterInfo monsters[], int numMonsters);
int getNumMonsters(ifstream& infile);
void displayMenu();
void findMonster(monsterInfo monsters[],int numMonsters);

/****************************************************************************
Function name: openInputDataFile

Description:   Open data file "Monsters.txt". 
               Exit program if file not found.

Parameters:    (ifstream&) inStream is the data file stream.

Returns:       (inStream passed by reference).
****************************************************************************/
void openInputDataFile(ifstream& inStream) {
  inStream.open("monsters.txt");
  if (inStream.fail()) {
	cout << "Cannot open file monsters.txt!\n";
	exit(1);
  }
}

/****************************************************************************
Function name: openOutputDataFile

Description:   Open data file "Monsters.out". Exit program if file 
               cannot be opened for output.

Parameters:    (ofstream&) outStream is the data file stream.

Returns:       (outStream passed by reference).
****************************************************************************/
void openOutputDataFile(ofstream& outStream) {
  outStream.open("monsters.out");
  if (outStream.fail()) {
	cout << "Cannot open file monsters.out!\n";
	exit(1);
  }
}

/****************************************************************************
Function name: printOneMonster

Description:   Print Monster's info to outStream.

Parameters:    MonsterInfo struct s
               ostream& outStream (where to output to)

Returns:       Nothing.
****************************************************************************/
void printOneMonster(const monsterInfo s, ofstream& outStream) {

  outStream << s.name;
  outStream << "  " << s.weapons;
  outStream << "  " << s.healthRating << endl;
  return;
}

/****************************************************************************
Function name: printAllMonsters

Description:   Print info for all Monsters.

Parameters:    Monsters is array of MonsterInfo structures.
               numMonsters is (int) number of Monsters in the array.
			   heading is (string) title to print for list.
			   ostream outStream specifies where to output to.

Returns:       Nothing. 
****************************************************************************/
void printAllMonsters(const monsterInfo monsters[], const int numMonsters, ofstream& outStream) {
  for (int i = 0; i < numMonsters; i++)
	printOneMonster(monsters[i], outStream);
  return;
}

/****************************************************************************
Function name: processUserRequestsFromMenu

Description:   Displays a menu and takes requests

Parameters:    Monsters is array of MonsterInfo structures.
               numMonsters

Returns:       Nothing. 
****************************************************************************/
void processUserRequestsFromMenu(monsterInfo monsters[], int numMonsters) {
   int choice = 0;
 
   ofstream outStream;
   
   while( choice != 5)
   {
      displayMenu();

      cin >> choice;

      switch(choice)
	  {
         case 1:
	        sortByName(monsters, numMonsters);
		    printColumnHeadings();
            printListOfMonsters(monsters, numMonsters);
		    break;
	     case 2:
		    sortByHealthRating(monsters, numMonsters);
		    printColumnHeadings();
		    printListOfMonsters(monsters, numMonsters);
		    break;
	     case 3:
		    openOutputDataFile(outStream);
		    printAllMonsters(monsters, numMonsters, outStream);
		    break;
	     case 4:
		    findMonster(monsters, numMonsters);
		    break;
	     case 5:
		    break;
	     default:
		    cout << "\nPlease enter a value between 1 and 5\n";
		    break;
	  }
   }

  return;
}



void displayMenu() {
	cout << "\n(1) Print list of monsters in ascending order by name"
		 << "\n(2) Print list of monsters in decending order by health"
		 << "\n(3) Output monsters to monsters.out"
		 << "\n(4) Search for monster"
		 << "\n(5) Quit"
		 << "\n==>";
	return;
}






void findMonster(monsterInfo monsters[], int numMonsters)
{
	cout << monsters[numMonsters].name;
	return;
}


/****************************************************************************
Function name: getName

Description:   Read in a monster's name.

Parameters:    None.

Returns:       (string) name entered.
****************************************************************************/
string getName(ifstream& infile) {
  string name;

  infile >> name;

  return(name);
}

/****************************************************************************
Function name: getWeapons

Description:   Read in a monster's weapon(s).

Parameters:    None.

Returns:       (string) weapon(s) entered.
****************************************************************************/
string getWeapons(ifstream& infile) {
  string weapons;

  infile >> weapons;

  return(weapons);
}

/****************************************************************************
Function name: getMonster

Description:   Get user's input for information about a monster.

Parameters:    None

Returns:       monsterInfo struct.
****************************************************************************/
monsterInfo getMonster(ifstream& infile) {
monsterInfo monster;

  monster.name = getName(infile);
  monster.weapons = getWeapons(infile);
  infile >> monster.healthRating;

  return(monster);
}

/****************************************************************************
Function name: getListOfMonsters

Description:   Create array of information about monsters.

Parameters:    Array of monsterInfo structs.
               (int) number of monsters in the list.

Returns:       None (parameters passed by reference).
****************************************************************************/
void getListOfMonsters(monsterInfo monsters[], int& numMonsters) {
  ifstream infile;

  openInputDataFile(infile);

  numMonsters = getNumMonsters(infile);

  for(int i = 0; i < numMonsters; i++)
     monsters[i] = getMonster(infile);

  return;
}

/****************************************************************************
Function name: getNumMonsters

Description:   Read first line in data file that tells how many lines of
               student data need to be processed.

Parameters:    (ifstream&) inStream is the data file stream.

Returns:       (int) number of students to process in data file.
****************************************************************************/
int getNumMonsters(ifstream& infile) {
int numMonsters;

  infile >> numMonsters;
  cout << "\nnumMonsters: " << numMonsters;
  return(numMonsters);
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
void printListOfMonsters(const monsterInfo monsters[], const int numMonsters) {

  for (int i = 0; i < numMonsters; i++) {
	cout.unsetf(ios::right);
    cout.setf(ios::left);
    cout << setw(MAX_STRING_LENGTH + 1) << monsters[i].name;
    cout << setw(MAX_STRING_LENGTH + 2) << monsters[i].weapons;
	cout.unsetf(ios::left);
	cout.setf(ios::right);
    cout << setw(4) << monsters[i].healthRating << endl;
  }

  return;
}

/****************************************************************************
Function name: sortByHealthRating

Description:   Sort monsterInfo array in descending order by health rating.

Parameters:    monsters is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (monsters array contents will be reordered)
****************************************************************************/
void sortByHealthRating(monsterInfo monsters[], const int numMonsters) {
monsterInfo temp;
int indexToSwap;

  for (int i = 0; i < numMonsters; i++) {
	indexToSwap = findHighestRating(monsters, numMonsters, i);
	temp = monsters[i];
	monsters[i] = monsters[indexToSwap];
	monsters[indexToSwap] = temp;
  }
  return;
}

/****************************************************************************
Function name: findHighestRating

Description:   Find index position of monsterInfo struct with highest health
               rating among start..(numMonsters - 1) in the monsters array.

Parameters:    monsters is array of monsterInfo structures.
               numMonsters is (int) number of elements in the monsters array.
			   start is (int) index position to start looking at in array.

Returns:       index position of monsterInfo element with highest rating among
                 start..(numMonsters - 1) in the monsters array. 
****************************************************************************/
int findHighestRating(const monsterInfo monsters[], const int numMonsters, const int start) {
float maxRating = monsters[start].healthRating;
int maxRatingIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (monsters[i].healthRating > maxRating) {
		maxRating = monsters[i].healthRating;
		maxRatingIndex = i;
	}
      
  return(maxRatingIndex);
}

/****************************************************************************
Function name: sortByName

Description:   Sort monsterInfo array in ascending order by name.

Parameters:    monsters is array of monsterInfo structures.
               numMonsters is (int) number of monsterInfo structures to process.

Returns:       (monsters array contents will be reordered)
****************************************************************************/
void sortByName(monsterInfo monsters[], const int numMonsters) {
monsterInfo temp;
int indexToSwap;

  for (int i = 0; i < numMonsters; i++) {
	indexToSwap = findLowestName(monsters, numMonsters, i);
	temp = monsters[i];
	monsters[i] = monsters[indexToSwap];
	monsters[indexToSwap] = temp;
  }
  return;
}

/****************************************************************************
Function name: findLowestName

Description:   Find index position of monsterInfo struct with lowest last 
               name (alphabetically) among start..(numMonsters - 1) in the monsters array.

Parameters:    monsters is array of monsterInfo structures.
               numMonsters is (int) number of elements in the monsters array.
			   start is (int) index position to start looking at in array.

Returns:       index position of monsterInfo element with highest name among
                 start..(numMonsters - 1) in the monsters array. 
****************************************************************************/
int findLowestName(const monsterInfo monsters[], const int numMonsters, const int start) {
string minName = monsters[start].name;
int minAvgIndex = start;

  for (int i = start + 1; i < numMonsters; i++)
    if (monsters[i].name < minName) {
		minName = monsters[i].name;
		minAvgIndex = i;
	}
      
  return(minAvgIndex);
}

// Begin program execution here
int main()
{
monsterInfo monsters[MAX_MONSTERS];
int numMonsters;

  getListOfMonsters(monsters, numMonsters);
  processUserRequestsFromMenu(monsters, numMonsters);

  return(0);
}
