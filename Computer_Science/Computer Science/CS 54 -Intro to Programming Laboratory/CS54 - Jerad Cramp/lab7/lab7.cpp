/* programmer: robertoMurillo    date: 10/5/05 *
 * instructor: price             class: cs54d  *
 * file: lab7.cpp                              *
 * purpose: practicing functions with pass by  *
 *          reference and overloading.         */
 
#include <iostream>
#include <cstdlib>
using namespace std;

/*************** PROTOTYPES ***************/

void welcome();
int getRndInt(const int low, const int high);
void swap(int & int1, int & int2);
void swap(char & char1, char & char2);
void fauxSwap(const int int1, const int int2);
void farewell();
char getChar();
char play();

/*************** PROTOTYPES ***************/

int main()
{

  /*************** VARIABLE DECLARATIONS ***************/
  
  const int low = 1;
  const int high = 100;
  char char1, char2, playGame;   // char1 and 2 are user selected char's
                                 // playGame is the Y/N choice of user
  int rndInt1, rndInt2, rndInt3; // all random int's chosen by either
                                 // program or user.
  
  /*************** VARIABLE DECLARATIONS ***************/
  
  srand(time(0));
  
  /*************** THE GAME! ***************/
  
  welcome();
  
  do
  {
    rndInt1 = getRndInt(low, high);
    rndInt2 = getRndInt(low, high);
    rndInt3 = getRndInt(low, high);
    
    cout << "Call 1: " << rndInt1 << "." << endl
         << "Call 2: " << rndInt2 << "." << endl
         << "Call 3: " << rndInt3 << "." << endl
         << endl;
    
    rndInt1 = getRndInt(low, high);
    rndInt2 = getRndInt(low, high);
    cout << "Number 1: " << rndInt1 << endl
         << "Number 2: " << rndInt2 << endl
         << endl;
         
    swap(rndInt1, rndInt2);
    
    cout << "Number 1: " << rndInt1 << endl
         << "Number 2: " << rndInt2 << endl
         << endl;
    
    char1 = getChar();
    char2 = getChar();
    cout << endl
         << "Character 1: " << char1 << endl
         << "Character 2: " << char2 << endl
         << endl;
    
    swap(char1, char2);
    
    cout << "Character 1: " << char1 << endl
         << "Character 2: " << char2 << endl
         << endl;
    
    rndInt1 = getRndInt(low, high);
    rndInt2 = getRndInt(low, high);
    cout << "Number 1: " << rndInt1 << endl
         << "Number 2: " << rndInt2 << endl
         << endl;
         
    fauxSwap(rndInt1, rndInt2);
    
    cout << "Number 1: " << rndInt1 << endl
         << "Number 2: " << rndInt2 << endl
         << endl;    
    
    playGame = play();
    
  } while( playGame == 'Y');

  /*************** END OF THE GAME ***************/

return 0;
}

/*************** FUNCTION DEFINITIONS ***************/

void welcome()
{
  cout << "Hello and welcome to Roberto's program!";
  cout << endl;
}

int getRndInt(const int low, const int high)
{
  int  retVal;
       
  retVal = rand() % (high - low + 1) + low;
                     
return (retVal);
}
                               

void swap(int & int1, int & int2)
{
  int temp; // temporary variable for swap function
  
  temp = int1;
  int1 = int2;
  int2 = temp; 
}

void swap(char & char1, char & char2)
{
  int temp; // temporary variable for swap function
  
  temp = char1;
  char1 = char2;
  char2 = temp;
}

void fauxSwap(int int1, int int2)
{
  int temp; // temporary variable for swap function
  
  temp = int1;
  int1 = int2;
  int2 = temp;
}

char getChar()
{
  char cChoice; // user's selected character
  
  cout << "Please enter in a character: ";
  cin >> cChoice;

return cChoice;
}

char play()
{
  char cChoice; // "do they want to play again" answer
  char uppercase; // turns cChoice uppercase
  
  cout << "Would you like to play again(y/n): ";
  cin >> cChoice;
  
  uppercase = toupper(cChoice);
  
return uppercase;
}

void farewell()
{
  cout << "Thanks for playing!";
}

/*************** FUNCTION DEFINITIONS ***************/ 
