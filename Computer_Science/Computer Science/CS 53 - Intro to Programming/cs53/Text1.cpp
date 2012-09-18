#include <iostream> //library for standard input out put
#include <iomanip> //library for output modification
#include <string> //string library
using namespace std;
#define MAX_NUM_PLAYERS 10

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


void getName(string& fname, string& lname); //function to get players name
void getTeam(string& team);//function to get players team
playerStats getPlayerStatistics();//collects needed data about the player
int calculateNumHits(const playerStats p);//calculates the number of hits the player makes
float calculateBattingAverage(const playerStats p);//calculates the batting average
float calculateSluggingPercentage(const playerStats p);//calculates the sluffing percentage
void printColumnHeadings();//prints column headings
void sortByBattingAvg(playerStats p[ ], const int count);//function used to sort be batting average
int index_of_biggest(playerStats p[], int start_index, int number_used);//gives value for next biggest batting avg
void swap_values(playerStats& v1, playerStats& v2);//swap two values that are in a array
void sortByName(playerStats p[ ], const int count);//function that sorts stuff by the name
void printPlayerStatistics (const playerStats p);//prints a players stats on the screen
void new_line( );//function used to to eat and endline
int index_of_biggest_name(playerStats p[], int start_index, int number_used); //tool for sorting by name


int main()
{
   playerStats p[MAX_NUM_PLAYERS];
   int i, count = 0;
   char anotherPlayer, ch;
   string fname, lname, team;
     do {
         getName(fname, lname);
         getTeam(team);
		 p[count] = getPlayerStatistics(); //collects vitals on the players
		 p[count].fname = fname;
		 p[count].lname = lname;
		 p[count].team = team;
		 p[count].battingAvg = calculateBattingAverage(p[count]);
		 p[count].sluggingPercentage = calculateSluggingPercentage(p[count]);
		 count++;
		 cout << "\nDo you want to enter another player? (Y/N) ";
		 cin >> anotherPlayer;
		 cin.get(ch);
	 } while (((anotherPlayer == 'Y') || (anotherPlayer == 'y')) && (count < MAX_NUM_PLAYERS)); //loop for player to decide if they want to continue
   sortByBattingAvg(p, count);
   cout << "\nList of Players Sorted by Batting Average\n";
   printColumnHeadings();
    for (i = 0; i < count; i++) //prints all players in order of batting avg
       printPlayerStatistics(p[i]);
    sortByName(p, count);
    cout << "\nList of Players Sorted by Name\n";
    printColumnHeadings();
    for (i = 0; i < count; i++) //prints all players in order of last name
       printPlayerStatistics(p[i]);
	return(0);
}
/*
  *Pre: The persons name is only two words and less than 9 letters each
  *Post: The output is the first and last name of the player
  */
void getName(string& fname, string& lname)
{
	cout<<endl<<"Please Enter The Player's Full Name: ";
	cin>>fname;
	cin>>lname;
	
	return;
}

/* 
 * Pre: The name of the team including white space is no larger that 18 spaces
 * Post: gets the user inputed team
 */
  
void getTeam(string& team)
{
	new_line ();  // function called to eat the line so i can use getline
	cout<<endl<<"Please Enter The Player's Team: ";
	getline(cin, team, '\n');
	return;
}


/*
 *Pre: The user inputs valid numerical data
 *Post: The user inputs data into a struct that is passed back
        to a struct in main.
        */

playerStats getPlayerStatistics()
{
   playerStats temp;
   cout<<endl<<"Enter number of singles: ";
   cin>>temp.singles;
   cout<<"Enter number of doubles: ";
   cin>>temp.doubles;
   cout<<"Enter number of triples: ";
   cin>>temp.triples;
   cout<<"Enter number of homeruns: ";
   cin>>temp.homeruns;
   do          //condition loop that the number can't be zero  IE ERROR CHECKING
     {
     cout<<"Enter number of At Bats: ";
     cin>>temp.atbats;
     if (temp.atbats==0)
     cout<<"Please enter a number greater than zero"<<endl;
     } while(temp.atbats==0);
  cout<<endl;
   return temp;
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
 *Post: this calculates the sluggin percentage for a batter.
 */
float calculateSluggingPercentage(const playerStats p)
{
   float slug;
   slug=((p.singles*1)+(p.doubles*2)+(p.triples*3)+(p.homeruns*4))/p.atbats;
   return slug;
}

/*Pre: no requirments for said function
 *Post: This prints the headings for the results of the function 
 */
 
void printColumnHeadings()
{
cout.setf(ios::left);
cout<<setw(18)<<"Name";
cout<<setw(18)<<"Team";
cout<<setw(4)<<"AB";
cout<<setw(4)<<"1B";
cout<<setw(4)<<"2B";
cout<<setw(4)<<"3B";
cout<<setw(4)<<"HR";
cout<<setw(4)<<"H";
cout<<setw(6)<<"SLG";
cout<<setw(6)<<"AVG";
cout<<endl<<"___________________________________________________________________________"<<endl;
return;
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
 * Pre: A valid array and no same values in array
 * Post: The spot where the next smallest value in the array is
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
 * Pre: Have valid data in the array to print out
 * Post: Outputted data of all of the players stats
 */
void printPlayerStatistics (const playerStats p)
{
	string full_name;
	full_name=p.fname+' '+p.lname;
	cout.setf(ios::left);
	cout<<setw(18)<<full_name;
	cout<<setw(18)<<p.team;
	cout<<setw(4)<<p.atbats;
	cout<<setw(4)<<p.singles;
	cout<<setw(4)<<p.doubles;
	cout<<setw(4)<<p.triples;
	cout<<setw(4)<<p.homeruns;
	cout<<setw(4)<<calculateNumHits(p);
	cout.setf(ios::showpoint);
	cout<<setw(6)<<setprecision(4)<<p.sluggingPercentage;
	cout<<setw(6)<<setprecision(3)<<p.battingAvg<<endl<<endl;
	cout.unsetf(ios::showpoint);
	return;
}

/*
 *Pre:none
 * Post: gets a freshline outputted
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