/*
 * Author: Brian Sea
 * Date: 4/4/06
 * Purpose:
 *  This program gets the full name, major and gpa of the student and
 *  outputs it to the screen
 */
#include <iostream>
#include "student.h"


using namespace std;

/*
 *  Function: OutputStudent
 *  Arguments:
 *      out     -   the stream to output to (i.e. cout)
 *      output  -   the student that we which to display info about
 *  Returns: nothing
 */
void OutputStudent( ostream & out, const Student &output);

int main()
{
    // Create a student with a name, GPA and major.
    Student Brian("Brian", "Sea", 3.8, "Computer Science");

    // Create another student with a name, the GPA should default to 4.0
    // and the major should default to Undecided
    const Student Josh( "Josh", "Wilkerson");

    // Create a blank student.  First name should now be "Unknown",
    // last name should be blank, GPA should be 0, and major should be
    // "Undecided"
    Student You;

    string fname, lname, major;
    double GPA;
    bool checkGPA;

    cout << "The default student: ";
    OutputStudent(cout, You);
    cout << endl;

    // Get the first name and set it
    cout << "Please enter your first name: ";
    getline( cin, fname);
    You.setFname( fname );

    // Get the last name and set it
    cout << "Please enter your last name: ";
    getline(cin, lname);
    You.setLname( lname );

    // Get the student's GPA and try to set it
    do
    { 
        cout << "Please enter your GPA (out of 4.0): ";
        cin >> GPA;
        cin.ignore();   // ignore the return character because of getline

        // try to set the GPA.  If it's not a valid GPA then setGPA
        // should return false, otherwise it should return true
        checkGPA = You.setGPA( GPA);
        if( checkGPA == false )
        {
            cout << "ERROR: This is an invalid GPA. Please try again.\n";
        }
    }while( !checkGPA );

    // Get the major and set it
    cout  << "Please enter your major: ";
    getline( cin, major );
    You.setMajor( major );

    // Output the students to screen to verify that our tests work.
    cout << "\nHere is Brian: \n";;
    OutputStudent(cout,  Brian );
    cout << endl;

    cout << "Here is Josh: \n";
    OutputStudent(cout, Josh);
    cout << endl;

    cout << "Here is You: \n";
    OutputStudent( cout, You );
    cout << endl;

	return 0;
}

/*
 *  Function: OutputStudent
 *  Arguments:
 *      out     -   the stream to output to (i.e. cout)
 *      output  -   the student that we which to display info about
 *  Returns: nothing
 */
void OutputStudent( ostream & out, const Student &output)
{
    out << "Name: " << output.getFname() << "  " << output.getLname()<< endl;
    out << "Major: " << output.getMajor() << endl;
    out << "GPA: " << output.getGPA() << endl;
    return;
}
