/*
* Author: Elliot Gross
* Date: 2/15/06
* Filename: mini3.cpp
* Instructor: Brian Sea
* Description: This program will run a test program that tests basic
* arithmetic.
*/

#include <iostream> //allows for input/output
#include <string> // allows for the use of strings
#include <cctype>   // tolower
#include <cstdlib>  // srand, rand
#include <ctime>   // time

using namespace std;
// constant variables for min and max ranges as well as 
// number of questions that can be asked
const int MINQ = 5;
const int MAXQ =  20;
const int MIN_E = 0;
const int MAX_E = 20;
const int MIN_M = -25;
const int MAX_M = 30;
const int MIN_H = -99;
const int MAX_H = 200;

void greetings (); // function prototype for greetings
void displayMenu(); // function prototype for displayMenu
int randomNumber( int min, int max ); //function prototype
// for randomNumber

int main()
{
srand(time(NULL)); // seeds
greetings(); // calls the function greetings
displayMenu(); // calls the function displayMenu

return 0;
}
/*
 * Function: greetings
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Purpose: Welcomes the user after receiving their name 
 */
void greetings () //function definition of greetings
{
  string name;
  cout <<  "Hi there! What is your name?"; 
  cin >> name;
  cout << "Welcome " << name << "!" << endl;  
}
/*
 * Function: displayMenu
 * Arguments: None
 * Returns: None
 * PreConditions: None
 * Purpose: Displays the menu and executes choices on the menu 
 */
void displayMenu()
{
  string diff = "Easy";
  int choice;
  int num_q = 10;
  int num1=0, num2=0;
  int ans = 0, sum = 0, correct =0;
  int randomOperator = 0;
  char randomOp = 'a';
    
  do
  {
    cout << "1. Number of questions to ask: " << num_q << endl;
    cout << "2. Hardness: " << diff << endl;
    cout << "3. Start Test" << endl;
    cout << "4. Quit" << endl;
    cout << "What would you like to do?";
    cin >> choice;
    // displays menu and sets their selection to choice
  
   
    switch (choice) // switch between menu choices
    {
      case 1:
        cout << "How many questions do you wish to ask?";
        cin >> num_q; // asks user how many questions
		if (num_q > 20 || num_q <5) // error checking 
		{
			cout<< "Number of questions invalid, "
			    << "must be between 5 and 20. Set to 10" << endl;
			num_q = 10;
		}
        break;  
      case 2:
        cout <<"What difficulty would you like to use?";
        cin >> diff; //asks user for difficulty
		if (diff != "Easy" && diff != "Medium" && diff != "Hard")
			// error checks to make sure it's easy, medium, or hard
		{
			cout << "Difficulty invalid, set to Easy" << endl;
			diff = "Easy"; // defaults to easy if invalid
		}
        break;
      case 3:
		if (diff == "Easy") //what runs when easy
		{
			for(int i=0; i < num_q; i++) 
				// runs for number of questions
			{
				num1=randomNumber(MIN_E, MAX_E); 
				// gets first random number
				num2=randomNumber(MIN_E, MAX_E); 
				// gets 2nd random number
				randomOperator = rand()%2; 
				//mods by 2 yielding 1 or 0
				if (randomOperator ==0) 
					//what runs if 0 is answer
				{
					randomOp = '+'; // outputs + sign
					sum=num1 + num2; // adds the 2 
					//random numbers together
				}
				else if (randomOperator == 1)
					//what runs if answer is 1
				{
					randomOp = '-';
					//outputs - sign
					sum = num1 - num2;
					// subtracts the two numbers
				}
				else if (randomOperator ==2) 
					// what runs if answer is 2
				{
					randomOp = '*';
					//outputs * sign
					sum = num1 * num2;
					//multiplies the two numbers
				}
				cout << num1<<" "<< randomOp <<num2<<"= "<< endl;
				//displays the problem
				cin >> ans;
				//sets user input to ans
				if (sum == ans) // sees if answer is correct
				{
					cout << "Correct!" << endl;
					correct++;
				}
				else //runs if answer is incorrect
				{
					cout << "Sorry, incorrect" << endl;
				}
			}
		}
		// for the next two see above loop for easy for commenting
		else if(diff == "Medium")
		{
			for(int i=0; i < num_q; i++)
			{
				num1=randomNumber(MIN_M, MAX_M);
				num2=randomNumber(MIN_M, MAX_M);	
				randomOperator = rand()%2;
				if (randomOperator ==0)
				{
					randomOp = '+';
					sum=num1 + num2;
				}
				else if (randomOperator == 1)
				{
					randomOp = '-';
					sum = num1 - num2;
				}
				else if (randomOperator ==2)
				{
					randomOp = '*';
					sum = num1 * num2;
				}
				cout << num1<<" "<< randomOp <<num2<<"= "<< endl;
				cin >> ans;
				if (sum == ans)
				{
					cout << "Correct!" << endl;
					correct++;
				}
				else
				{
					cout << "Sorry, incorrect" << endl;
				}
			}
		}
		//see above loop for commenting
		else if(diff == "Hard")
		{
			for(int i=0; i < num_q; i++)
			{
				num1=randomNumber(MIN_H, MAX_H);
				num2=randomNumber(MIN_H, MAX_H);
				randomOperator = rand()%3;//includes 0,1, and 2
				if (randomOperator ==0)
				{
					randomOp = '+';
					sum=num1 + num2;
				}
				else if (randomOperator == 1)
				{
					randomOp = '-';
					sum = num1 - num2;
				}
				else if (randomOperator ==2)
				{
					randomOp = '*';
					sum = num1 * num2;
				}
				
				cout << num1<<" "<< randomOp <<" "<<num2<<"="<< endl;
				cin >> ans;
				if (sum == ans)
				{
					cout << "Correct!" << endl;
					correct++;
				}
				else
				{
					cout << "Sorry, incorrect" << endl;
				}
			}
		}
		else
			cout << "Please choose Easy, Medium, or Hard" 
				 << " as your difficulty" << endl;
		cout << "You got "<< correct <<" out of " << num_q << endl;
		correct = 0; // resets number correct to 0
		break;
      case 4:
        return; // exits
      default:
        cout <<"Unknown choice! Please pick again!" << endl;
		//error trapping for unknown choice
    }
  }while(choice != 4);    //exits when 4
  return;
}
/*
 * Function: randomNumber
 * Arguments:
 *  min -   the minimum number in the range
 *  max -   the maximum number in the range
 * Returns: a random integer between min and max
 *
 * PreConditions:
 *  the random number generator has been seeded
 */
int randomNumber( int min, int max )
{
    if( max < min )
    {
        // STL swap
        swap(min, max);
    }

    return ( rand() % (max - min + 1 ) + min );
}




