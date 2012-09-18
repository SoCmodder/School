/*
File Name:     studentInput.cpp

Author:        Jennifer Leopold

Email Address: leopoldj@umr.edu

Description:   CS 53 - Sample Program

               Program to read student info from an input file,
			   storing it in an array of structs.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

#define MAX_NUM_STUDENTS 10

struct studentInfo {
	string fname;
	string lname;
	int ID;
	float gpa;
};

// Function declarations
void openInputDataFile(ifstream& inStream);
void openOutputDataFile(ofstream& outStream);
int getNumStudents(ifstream& inStream);
void getAllStudents(studentInfo students[], const int numStudents, 
					ifstream& inStream);
studentInfo getOneStudent(ifstream& inStream);
void printOneStudent(const studentInfo s, ostream& outStream);
void printAllStudents(const studentInfo students[], const int numStudents,
					  const string heading, ostream& outStream);

/****************************************************************************
Function name: openInputDataFile

Description:   Open data file "students.txt". 
               Exit program if file not found.

Parameters:    (ifstream&) inStream is the data file stream.

Returns:       (inStream passed by reference).
****************************************************************************/
void openInputDataFile(ifstream& inStream) {
  inStream.open("students.txt");
  if (inStream.fail()) {
	cout << "Cannot open file students.txt!\n";
	exit(1);
  }
}

/****************************************************************************
Function name: openOutputDataFile

Description:   Open data file "students.out". Exit program if file 
               cannot be opened for output.

Parameters:    (ofstream&) outStream is the data file stream.

Returns:       (outStream passed by reference).
****************************************************************************/
void openOutputDataFile(ofstream& outStream) {
  outStream.open("students.out");
  if (outStream.fail()) {
	cout << "Cannot open file students.out!\n";
	exit(1);
  }
}

/****************************************************************************
Function name: getNumStudents

Description:   Read first line in data file that tells how many lines of
               student data need to be processed.

Parameters:    (ifstream&) inStream is the data file stream.

Returns:       (int) number of students to process in data file.
****************************************************************************/
int getNumStudents(ifstream& inStream) {
int numStudents;

  inStream >> numStudents;
  return(numStudents);
}

/****************************************************************************
Function name: getAllStudents

Description:   Read in all student data from inStream.

Parameters:    students is array of studentInfo structures.
               numStudents is (int) number of students to process.
			   (ifstream&) inStream is the data file stream.

Returns:       (students array contents will be changed)
****************************************************************************/
void getAllStudents(studentInfo students[], const int numStudents, 
					ifstream& inStream) {
char ch;

  // Process each student
  for (int i = 0; i < numStudents; i++) {
	inStream.get(ch); // Read the '\n' from end of previous line
	students[i] = getOneStudent(inStream);	
  }
}

/****************************************************************************
Function name: getOneStudent

Description:   Read in a student's info from data file.

Parameters:    (ifstream) inStream to read data for (string) team.

Returns:       playerStats struct.
****************************************************************************/
studentInfo getOneStudent(ifstream& inStream) {
studentInfo s;
char comma;

  getline(inStream, s.fname, ' ');
  getline(inStream, s.lname, ',');
  inStream >> s.ID;
  inStream >> comma;  // Don't forget to read comma between ID and gpa!!!
  inStream >> s.gpa;

  return(s);
}


/****************************************************************************
Function name: printOneStudent

Description:   Print student's info to outStream.

Parameters:    studentInfo struct s
               ostream& outStream (where to output to)

Returns:       Nothing.
****************************************************************************/
void printOneStudent(const studentInfo s, ostream& outStream) {

  outStream << s.fname + " " + s.lname;
  outStream << "  " << s.ID;
  outStream << "  " << s.gpa << endl;
  return;
}

/****************************************************************************
Function name: printAllStudents

Description:   Print info for all students.

Parameters:    students is array of studentInfo structures.
               numStudents is (int) number of students in the array.
			   heading is (string) title to print for list.
			   ostream outStream specifies where to output to.

Returns:       Nothing. 
****************************************************************************/
void printAllStudents(const studentInfo students[], const int numStudents,
					  const string heading, ostream& outStream) {
  outStream << endl << heading << endl << endl;
  for (int i = 0; i < numStudents; i++)
	printOneStudent(students[i], outStream);
  return;
}

// Start program execution here
int main()
{
int numStudents;
ifstream inStream;
ofstream outStream;
studentInfo students[MAX_NUM_STUDENTS];

  openInputDataFile(inStream);

  // Find out how many students are listed in the data file
  numStudents = getNumStudents(inStream);

  if (numStudents > 0) {
    if (numStudents > MAX_NUM_STUDENTS) numStudents = MAX_NUM_STUDENTS;
	getAllStudents(students, numStudents, inStream);
  }

  // Close input file because we're done with it
  inStream.close();

  // Print list of students to cout (i.e., to screen)
  printAllStudents(students, numStudents, "Student List (to cout)", cout);

  // Print list of students to students.out file 
  openOutputDataFile(outStream);
  printAllStudents(students, numStudents, "Student List (to file)", outStream);

  // Close output file when we're done with it
  outStream.close();

  return(0);
}
