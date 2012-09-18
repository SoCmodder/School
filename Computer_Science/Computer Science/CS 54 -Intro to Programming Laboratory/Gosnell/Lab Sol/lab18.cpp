//Sample Solution for Week 15
// Lab 18 -- Structures

#include <iostream>
#include <cstdlib>
#include <string>

//using namespace std; covers these ...
using std::cout;
using std::endl;
using std::cin;
using std::string;
//

//Create Structure
////////////////////////////////////////////////////////////////
struct cs53class {
    int   stuno;
    char  name[30];
    float gpa;
    char  major[20];
    char  city[35];
};
////////////////////////////////////////////////////////////////

void StructRead(cs53class&);
void StructWrite(cs53class);
int StructComp(cs53class, cs53class);

int main() {
    cs53class myo1, myo2;

    cout << "First user ";
    StructRead(myo1);

    cout << "Second user ";
    StructRead(myo2);

    int myReturn = StructComp(myo1, myo2);
    cout << "Finding highest gpa to be: " << endl;

        if (myReturn ==  -1)
            StructWrite(myo2);
        else if (myReturn == 1) 
            StructWrite(myo1);
	else
            cout << "They're equal!  (GPAs)" << endl;

    return 0;
}

void StructRead(cs53class& cc) {
//we account for spaces in input by using getline (from the keyboard cin)
    string tempString;
    cout << "INPUT" << endl;
    
    cout << "student number: ";
    getline(cin, tempString, '\n');
    cc.stuno = atoi(tempString.c_str());

    cout << "name: ";
    getline(cin, tempString, '\n');
    tempString.copy(cc.name, 30, 0);

    cout << "gpa: ";
    getline(cin, tempString, '\n');
    cc.gpa = atoi(tempString.c_str());

    cout << "major: ";
    getline(cin, tempString, '\n');
    tempString.copy(cc.major, 20, 0);

    cout << "city: ";
    getline(cin, tempString, '\n');
    tempString.copy(cc.city, 35, 0);
    
    cout << endl;
}

void StructWrite(cs53class cc) {
//essentially a copy of the read with getline changed to cout
    cout << "student number: ";
    cout << cc.stuno;
    cout << "\nname: ";
    cout << cc.name;
    cout << "\ngpa: ";
    cout << cc.gpa;
    cout << "\nmajor: ";
    cout << cc.major;
    cout << "\ncity: ";
    cout << cc.city;
    cout << endl;
}

int StructComp(cs53class c1, cs53class c2) {
    //the compare function determines which (if any) struct has a higher gpa)
    //  therefore we implement with a return of int as a flag ...
    if (c1.gpa > c2.gpa)
        return 1;
    else if (c1.gpa < c2.gpa)
        return -1;
    else
        return 0;
}
