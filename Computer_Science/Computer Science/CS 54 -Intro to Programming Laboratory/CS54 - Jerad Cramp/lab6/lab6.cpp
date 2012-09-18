/* programmer: robertoMurillo    date: 09/28/05 *
 * instructor: price             class: cs54d   *
 * file: lab6.cpp                               *
 * purpose: practicing functions                */
 
#include <iostream>
using namespace std;

/*************** FUNCTION PROTOTYPES ***************/

void greeting(const int low, const int high);
void win();
void lose(int getRndInt);
char getYN();
int inputNum(const int low, const int high);
int getRndInt(const int low, const int high);

/*************** FUNCTION PROTOTYPES ***************/

int main()
{
  /*************** VARIABLE DECLARATIONS ***************/

  const int low = 1, high = 10;
  int retVal; // computer's random number choice
  int iGuess; // user's number guess
    
  /*************** VARIABLE DECLARATIONS ***************/

  /*************** NUMBER GAME ***************/
  
  greeting(low, high);
  char choice = getYN(); // assigning the getYN function to a variable so
                         // it only runs once
    
  if (choice == 'Y')
    {
      retVal = getRndInt(low, high);
    
      do
      {
        cout << "I have picked a number.  What is your guess: ";
        iGuess = inputNum(low, high); // assigning inputNum to a variable
                                      // to make life easier
      } while(iGuess < low && iGuess > high);
    
      if (iGuess == retVal)
        win();
    
      else if (iGuess != retVal)
        lose(retVal);   
    }
  
  else if (choice == 'N')
    cout << "Oh, I see how it is."
         << endl;
  
  /*************** NUMBER GAME ************/
    
return 0;
}

/*************** FUNCTION DEFINITIONS ***************/
void greeting(const int low, const int high)
{
  cout << "Hi! I will think of a number between " << low << " and "
       << high << " and then you can try to guess it. Do you want to" 
       << " play (y/n): ";
}

char getYN()
{
  char choice;
  
  do
  {
    cin >> choice;
    if (choice == 'y')
      {
        choice = 'Y';
      }
      
    else if (choice == 'n')
      {
        choice = 'N';
      }
        
    else if (choice != 'Y' && choice != 'N')
      cout << "Invalid input. Please enter Y or N.";
  
  } while(choice != 'Y' && choice != 'N');
    
  return choice;
}

int getRndInt(const int low, const int high)
{
  int  retVal;
          
  srand(time(0));
  retVal = rand() % (high - low + 1) + low;
           
  return (retVal);
}                                 

int inputNum(const int low, const int high)
{
  int numChoice;
  
  do
  {
    cin >> numChoice;
  } while (numChoice < low && numChoice > high);
  
  return numChoice;
}

void win()
{
  cout << "You are correct!"
       << endl;
}

void lose(int retVal)
{
  cout << "No, I'm sorry.  I was thinking of the number "
       << retVal << "."
       << endl;
}

/*************** FUNCTION DEFINITIONS ***************/  
