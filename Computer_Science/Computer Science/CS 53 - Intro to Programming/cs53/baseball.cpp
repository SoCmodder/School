/*
File: baseball.cpp
Name: Brent Powers
Date: 3-22-2004
Email: bkp347@umr.edu
*/

/*
This program take inputed data about a baseball player and outputs it in a
certain way. The purpose of the assignment is to gain experience with structs 
and with functions.
*/


#include <iostream>
#include <iomanip>  // need this for percisoin and width setting
using namespace std;


struct playerStats  //struct that is used throughout the program to hold data
{
int singles;
int doubles;
int triples;
int homeruns;
float atbats;
};

// Function declarations
void getPlayerName();
void getPlayerTeam();
playerStats getPlayerStatistics();
int calculateNumHits(const playerStats p);
float calculateBattingAverage(const playerStats p);
float calculateSluggingPercentage(const playerStats p);
void printColumnHeadings();
void printPlayerStatistics(const playerStats p, const float battingAvg, 
				           const float sluggingPercentage,
						   const int numHits);



// Begin program execution here
int main()
{
playerStats p;
char  anotherPlayer, ch;
float battingAvg, sluggingPercentage;

  do {
	getPlayerName();
	getPlayerTeam();

    p = getPlayerStatistics();

	battingAvg = calculateBattingAverage(p);
	sluggingPercentage = calculateSluggingPercentage(p);

	printColumnHeadings();
	printPlayerStatistics(p, battingAvg, sluggingPercentage,
		                  calculateNumHits(p));

    cout << "\nDo you want to calculate for another player? (Y/N) ";
    cin >> anotherPlayer;
    cin.get(ch); // "Eat" the newline character that was just entered
  } while ((anotherPlayer == 'Y') || (anotherPlayer == 'y'));

  return(0);
}
/*
 *Pre: There is no requirement to call this function
 *Post: The user is told to enter the players name and they do that,
        but what they are really doing is entering single letters, until 
        they hit enter. This gives the user the sense that they have entered
        some text, but in actuall they didn't. So basically this function's
        purpose is to leave the user warm and fuzzy.
        */

void getPlayerName()
{  
  char ch;
  cout<<"Enter Player Name: ";
   do 
     {
       cin.get(ch);
      }while (ch != '\n');
  return;
}

/*
 *Pre: There is no requirement to call this function
 *Post: There is no actual result of this function, except that the user 
        believes that they have entered something  
        */

void getPlayerTeam()
 {
   char ch2;
   cout<<"Enter Player Team: ";
     do
      {
        cin.get(ch2);
       }while (ch2 != '\n');
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
   cout<<"Enter number of singles: ";
   cin>>temp.singles;
   cout<<"Enter number of doubles: ";
   cin>>temp.doubles;
   cout<<"Enter number of triples: ";
   cin>>temp.triples;
   cout<<"Enter number of homeruns: ";
   cin>>temp.homeruns;
   do          //condition loop that the number can't be zero
     {
     cout<<"Enter number of At Bats: ";
     cin>>temp.atbats;
     if (temp.atbats==0)
     cout<<"Please enter a number greater than zero"<<endl;
     } while(temp.atbats==0);
   return temp;
}

/*
 *Pre: the struct p has valid numerical entries
 *Post: The function returns the number of hits a player makes, based on the sum
        of the different types of hits.
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
cout<<setw(4)<<"AB";
cout<<setw(4)<<"1B";
cout<<setw(4)<<"2B";
cout<<setw(4)<<"3B";
cout<<setw(4)<<"HR";
cout<<setw(4)<<"H";
cout<<setw(6)<<"SLG";
cout<<setw(6)<<"AVG";
cout<<endl<<"____________________________________"<<endl;
return;
}
/*
 *Pre: That all of the variables have valid numerical values.
 *Post: Displays the values that match the column headers above them
        */
void printPlayerStatistics (const playerStats p, const float battingAvg, const float sluggingPercentage, const int numHits)
{
cout.setf(ios::left);
cout<<setw(4)<<p.atbats;
cout<<setw(4)<<p.singles;
cout<<setw(4)<<p.doubles;
cout<<setw(4)<<p.triples;
cout<<setw(4)<<p.homeruns;
cout<<setw(4)<<numHits;
cout<<setw(6)<<setprecision(3)<<sluggingPercentage;
cout<<setw(6)<<setprecision(3)<<battingAvg;
return;
}
