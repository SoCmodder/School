/*
File Name: fliereading.cpp
Author: Brent Powers
Email Address: bkp347@umr.edu
Description:  cs-53 homework project that is used to gain the understanding of how to use fileinput and fileoutput
Date: 4-20-2004
*/
#include <iostream> //library for standard input out put
#include <iomanip> //library for output modification
#include <string> //string library
#include <fstream> //i/o stream library
using namespace std;
#define MAX_NUM_PLAYERS 10 //maximum number of players to be processed

struct playerStats  //struct that is used throughout the program to hold data about a player
{
	int singles;
	int doubles;
	int triples;
	int homeruns;
	float atbats;
	float sluggingPercentage;
	float battingAvg;
	string fname;
	string lname;
	string team;
};


void openInputDataFile(ifstream& inStream);
void openOutputDataFile(ofstream& outStream);
int getNumPlayers(ifstream& inStream);
void getAllPlayers(playerStats players[ ], const int numPlayers,ifstream& inStream);
int calculateNumHits(const playerStats p);
float calculateBattingAverage(const playerStats p);
float calculateSluggingPercentage(const playerStats p);
void printColumnHeadings(ostream& outStream);
void printOnePlayer(const playerStats p, ostream& outStream);
void printAllPlayers(const playerStats players[ ], const int numPlayers,const string heading, ostream& outStream);
void sortByBattingAvg(playerStats p[ ], const int count);
int index_of_biggest(playerStats p[], int start_index, int number_used);
void sortByName(playerStats p[ ], const int count);
int index_of_biggest_name(playerStats p[], int start_index, int number_used);
int findPlayer(const playerStats players[ ], const int numPlayers);
void displayMenu();
void processUserRequestsFromMenu(playerStats players[ ],const int numPlayers);
void swap_values(playerStats& v1, playerStats& v2);
void new_line( );//function used to to eat and endline

// Start program execution here
int main()
{
	int numPlayers;
	ifstream inStream;
	playerStats players[MAX_NUM_PLAYERS];
	openInputDataFile(inStream);//opens the file and gets the stream ready
	// Find out how many players are listed in the data file
	numPlayers = getNumPlayers(inStream);
	if (numPlayers > 0) 
	{
		if (numPlayers > MAX_NUM_PLAYERS) 
			numPlayers = MAX_NUM_PLAYERS;
		getAllPlayers(players, numPlayers, inStream);//collects all of the data about the players 
	}
	inStream.close();//closes the stream
	processUserRequestsFromMenu(players, numPlayers);//begins the process of letting the user work with the data 
	return(0);
}


/*
Pre: there is good data in the players aray 
Post: the user uses this function to navigate back and forth from a variety of other functions completeing a
bunch of tasks in the process
*/
void processUserRequestsFromMenu(playerStats players[ ], const int numPlayers) 
{
	bool keepGoing = true;
	int choice;
	int position;
	ofstream outStream;
	while (keepGoing) //keeps the user in program until the chose to leave
	{
		displayMenu();//shows the user choice menu
		cin >> choice;
		switch (choice)
		{
		case 1: // Print list of players sorted by last name
			sortByName(players, numPlayers);
			printAllPlayers(players, numPlayers,"List of Players Sorted by Name", cout);
			break;
		case 2: // Print list of players sorted by batting average
			sortByBattingAvg(players, numPlayers);
			printAllPlayers(players, numPlayers,"List of Players Sorted by Batting Average", cout);
			break;
		case 3: // Create output file of list of players
			openOutputDataFile(outStream);
			printAllPlayers(players, numPlayers,"List of Players", outStream);
			outStream.close();
			cout << "\nOutput file out.txt created\n";
			break;
		case 4: // List info about a player
			position = findPlayer(players, numPlayers);
			if (position != -1) 
			{
				printColumnHeadings(cout);
				printOnePlayer(players[position], cout);
			}
			else cout << "\nSpecified player is not in my list.\n"<<endl;
			break;
		case 5: // Exit this program
			keepGoing = false;
			break;
		default: cout << "\nInvalid selection -- try again!\n";
		}
	}
}

/*
Pre: The inStream being passed is the correct name, and the file playerStats.txt exixts and is correct
Post: Opens the connection to the input stream or if fails exits program

  */

void openInputDataFile(ifstream& inStream)
{
	inStream.open("playerStats.txt");
	if (inStream.fail() )
	{
		cout<<"playerStats.txt did not open!!!";
		exit (1);
	}
	return;
}

/*
 * Pre: Valid array with name values all last names are in the same format ie first letter cap. rest not
 * Post: Array sorted by name
 */


void sortByName(playerStats p[], const int count)
{
	int iloop;
	int index_of_next_biggest;
	for (iloop=0;iloop<count-1;iloop++)
	{
		index_of_next_biggest=index_of_biggest_name(p, iloop, count);
		swap_values(p[iloop], p[index_of_next_biggest]);
	}
	return;
}

/*
 * Pre: Array with valid names 
 * Post: The index of the next name to sort in the array
 */

int index_of_biggest_name(playerStats p[], int start_index, int number_used)
{
	string max=p[start_index].lname; 
	int index_of_max=start_index;
	for(int index = start_index+1; index<number_used; index++)
    	if (p[index].lname<max)
		{
			max=p[index].lname;
			index_of_max=index;
		}
	return index_of_max;

}

/*
 * Pre: Two valid values to switch
 * Post: The items are switched around in the array
 */
void swap_values(playerStats& v1, playerStats& v2)
{
	playerStats temp;
	temp = v1;
	v1 =v2;
	v2 =temp;
}

/*
 *Pre: Sorts the users by batting avg, must have valid entries for batting averages
 *Post: Sorted array in order of batting average
 */

void sortByBattingAvg(playerStats p[ ], const int count)
{
	int iloop;
	int index_of_next_biggest;
	for (iloop=0;iloop<count-1;iloop++)
	{
		index_of_next_biggest=index_of_biggest(p, iloop, count);
		swap_values(p[iloop], p[index_of_next_biggest]);
	}
}

/*
Pre: valid parameters are being passed to the functoin
Post: the index o fthe location of the next biggest batting average
  */
int index_of_biggest(playerStats p[], int start_index, int number_used)
{
	float max=p[start_index].battingAvg;
	int index_of_max=start_index;
	for(int index = start_index+1; index<number_used; index++)
		if (p[index].battingAvg>max)
		{
			max=p[index].battingAvg;
			index_of_max=index;
		}
	return index_of_max;
}

/*Pre: out stream is open and file is connected
 *Post: This prints the headings for the results of the function 
 */
 
void printColumnHeadings(ostream& outStream)
{
	outStream.setf(ios::left);
	outStream<<setw(18)<<"Name";
	outStream<<setw(18)<<"Team";
	outStream<<setw(4)<<"AB";
	outStream<<setw(4)<<"1B";
	outStream<<setw(4)<<"2B";
	outStream<<setw(4)<<"3B";
	outStream<<setw(4)<<"HR";
	outStream<<setw(4)<<"H";
	outStream<<setw(6)<<"SLG";
	outStream<<setw(6)<<"AVG";
	outStream<<endl<<"___________________________________________________________________________"<<endl;
	return;
}

/*
Pre: none
Post: an open connection to out.txt or a failed status
  */
void openOutputDataFile(ofstream& outStream)
{
	outStream.open("out.txt.");
	if (outStream.fail())
	{
		cout<<"can not create out,txt";
		exit(1);
	}
	return;
}

/*
 *Pre: there are number values for all the array
 *Post: the total number of hits the player made
 */

 
int calculateNumHits(const playerStats p)
{
   int total;
   total=p.singles+p.doubles+p.triples+p.homeruns;
   return total;
}

/*
Pre: the inStream is open and the file is not corrupted
Post: The number of players that are in the file
  */
int getNumPlayers(ifstream& inStream)
{
	int number=-1;
	inStream>>number;
	return number;
}

/*
Pre: The inStream is ready and open and the array and number of players are all right
Post: The values for the players are entered into the array
  */
void getAllPlayers(playerStats players[ ], const int numPlayers,ifstream& inStream)
{
	char temp1;
	for(int i=0;i<numPlayers;i++) 
	{
		inStream.get(temp1);
		getline(inStream,players[i].fname,' ');
		getline(inStream,players[i].lname, ',');
		getline(inStream,players[i].team, ',');
		inStream>>players[i].singles;
		inStream.get(temp1);
		inStream>>players[i].doubles;
		inStream.get(temp1);
		inStream>>players[i].triples;
		inStream.get(temp1);
		inStream>>players[i].homeruns;
		inStream.get(temp1);
		inStream>>players[i].atbats;
		players[i].battingAvg=calculateBattingAverage(players[i]);
		players[i].sluggingPercentage=calculateSluggingPercentage(players[i]);
		if (players[i].atbats==0)
		{
			cout<<"ERROR: Invalid data for players, resulting in division by zero!";
			exit (1);
		}
	}
		return;
}


/*
 *Pre: that the number of at bats doesn't equale zero
 *Post: the function returns the batting average for a player
 */
float calculateBattingAverage(const playerStats p)
{
   float AVG;
   AVG = calculateNumHits(p)/p.atbats;
   return AVG;
}

/*
 *Pre: the number of at bats is not zero
 *Post: this calculates the sluggin percentage for a batter
 */
float calculateSluggingPercentage(const playerStats p)
{
   float slug;
   slug=((p.singles*1)+(p.doubles*2)+(p.triples*3)+(p.homeruns*4))/p.atbats;
   return slug;
}

/*
Pre: the outStream is opened correctly
Post: the stats are outputed on the screen or in the file
  */
void printOnePlayer(const playerStats players, ostream& outStream)
{
	string full_name;
	full_name=players.fname+' '+players.lname;
	outStream.setf(ios::left);
	outStream<<setw(18)<<full_name;
	outStream<<setw(19)<<players.team;
	outStream<<setw(4)<<players.atbats;
	outStream<<setw(4)<<players.singles;
	outStream<<setw(4)<<players.doubles;
	outStream<<setw(4)<<players.triples;
	outStream<<setw(4)<<players.homeruns;
	outStream<<setw(4)<<calculateNumHits(players);
	outStream.setf(ios::showpoint);
	outStream<<setw(6)<<setprecision(3)<<players.sluggingPercentage;
	outStream<<setw(6)<<setprecision(3)<<players.battingAvg<<endl<<endl<<endl;
	outStream.unsetf(ios::showpoint);
	return;
}

/*
Pre: the array is full and that the outStream is set up correctly
Post: all of the players stats are put out on the screen or file
  */
void printAllPlayers(const playerStats players[ ], const int numPlayers,const string heading, ostream& outStream)
{
	string full_name;
	outStream<<endl<<endl<<heading<<endl<<endl;
	printColumnHeadings(outStream);
		for(int i=0;i<numPlayers;i++)
	{
		full_name=players[i].fname+' '+players[i].lname;
		outStream.setf(ios::left);
		outStream<<setw(18)<<full_name;
		outStream<<setw(19)<<players[i].team;
		outStream<<setw(4)<<players[i].atbats;
		outStream<<setw(4)<<players[i].singles;
		outStream<<setw(4)<<players[i].doubles;
		outStream<<setw(4)<<players[i].triples;
		outStream<<setw(4)<<players[i].homeruns;
		outStream<<setw(4)<<calculateNumHits(players[i]);
		outStream.setf(ios::showpoint);
		outStream<<setw(6)<<setprecision(3)<<players[i].sluggingPercentage;
		outStream<<setw(6)<<setprecision(3)<<players[i].battingAvg<<endl;		outStream.unsetf(ios::showpoint);
	}
	outStream<<endl<<endl<<endl;
	
	return;
}
/*
Pre: The array has valid entries in it
Post: returns the position of the player being looked for, or -1 for not there
  */

int findPlayer(const playerStats players[ ], const int numPlayers)
{
	
	string name;
	cout<<endl<<"Enter the last name or first name of the player you are looking for: ";
	cin>>name;
	new_line();
	int n=0;
	bool found=false;
	while((found==false)&&(n<numPlayers))
	{
		if((players[n].fname==name)||(players[n].lname==name))
			found=true;
		else
			n++;
	}
	if(found!=true)
		n=-1;
	cout<<endl<<endl;
	return n;
}
/*
Pre: None
Post:the menu is outputted on the screen
  */
void displayMenu()
{
	cout<<"Main Menu:"<<endl;
	cout<<"1. Print a formatted list of players sorted by last name"<<endl;
	cout<<"2. Print a formatted list of players sorted by batting average"<<endl;
	cout<<"3. Create an output file called playerStats.out that contains a formatted list of the players (in any order)"<<endl;
	cout<<"4. Display stats for a specific player"<<endl;
	cout<<"5. Exit the program"<<endl;
	cout<<"Enter your selection (1-5):  ";
	return;
}
/*
Pre: None
Post: The line is cleared and ready to input data
  */
void new_line( )
{
	using namespace std;
	char next_char;
	do
	{
		cin.get(next_char);
	}while(next_char != '\n');
}
