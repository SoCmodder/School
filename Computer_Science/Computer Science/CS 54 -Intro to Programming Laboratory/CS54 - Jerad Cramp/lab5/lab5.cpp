/* programmer: robertoMurillo    date: 09/21/05
 * instructor: price             class: cs54d
 * file: lab5.cpp
 * purpose: calculating grades for students */
 
#include <iostream>
using namespace std;

int main()
{
  /*************** DECLARING VARIABLES ***************/
  
  const int PERCENT_CONVERT = 100;    // convert's grade from a number to 
                                      // to a percentage
  const double maxPoints = 115.0;     // total points available
  const int FIRST_DIGIT_CONVERT = 10; // converts the percentage to a
                                      // grade relevant to the first digit
  const char PERFECT = 10; // student's grade
  const char A = 9;   // student's grade
  const char B = 8;   // student's grade
  const char C = 7;   // student's grade
  const char D = 6;   // student's grade
  
  double numericGrade;   // calculated average of all the grades
  long studentID;        // student ID number
  int hwk1;              // grade for homework one
  int quiz1;             // grade for quiz
  int hwk2;              // grade for homework two
  int test1;             // grade for test
  int iGrade;            // student's grade as an integer, out of 10
  char cChoice;          // would they like to calculate another grade?
  
  /*************** DECLARING VARIABLES ***************/
  
  cout << "Hello and welcome to Grades Made Easy." << endl;
  cout << endl;
  
  do
  {
    /*************** USER INPUT ***************/
    
    cout << "Please enter the Student's ID number: ";
    cin >> studentID;
    cout << endl;
  
    /*************** USER INPUT ***************/
  
    /*************** ENTERING GRADES ***************/

    cout << "Please enter the points scored for the first homework " 
         << "assignment: ";
    cin >> hwk1;
    cout << endl
         << "Please enter the points scored for the quiz: ";
    cin >> quiz1;
    cout << endl
         << "Please enter the points scored for the second homework: ";
    cin >> hwk2;
    cout << endl
         << "Please enter the points scored for the test: ";
    cin >> test1;
    cout << endl
         << "Thanks." << endl
         << endl;

    /*************** ENTERING GRADES ***************/
  
    /*************** CALCULATING AVERAGE ***************/
  
    numericGrade =  ( ( hwk1 + quiz1 + hwk2 + test1 ) / maxPoints ) 
                    * PERCENT_CONVERT;
    iGrade = ( static_cast<int>( numericGrade ) / FIRST_DIGIT_CONVERT  );
  
    /*************** CALCULATING AVERAGE ***************/
  
    /*************** STUDENT'S GRADE IS ***************/
    
    switch (iGrade)
    {
      case PERFECT:
      case A:
        cout << "Student " << studentID << " has a grade of A (" 
             << numericGrade << "%)."
             << endl;
        break;
      case B: 
        cout << "Student " << studentID << " has a grade of B (" 
             << numericGrade << "%)."
             << endl;
        break;
      case C:
        cout << "Student " << studentID << " has a grade of C (" 
             << numericGrade << "%)."
             << endl;
        break;
      case D:
        cout << "Student " << studentID << " has a grade of D (" 
             << numericGrade << "%)."
             << endl;
        break;
      default:
        cout << "Student " << studentID << " has a grade of F (" 
             << numericGrade << "%)."
             << endl;
        break;
    }
  
    /*************** STUDENT'S GRADE IS ***************/
    
    /*************** QUIT? ***************/
    
    cout << endl;
    cout << "Would you like to calculate another grade(y/n): ";
    cin >> cChoice;
  } while( !(cChoice == 'N' || cChoice == 'n') );
    
    /*************** QUIT? ***************/

return 0;
}
