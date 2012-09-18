/* 
* Author: Elliot Gross
* Date: 3/21/06
* Filename: lab11.cpp
* Instructor: Brian Sea
* Description: This program will read a certain amount 
* of numbers and will output data to an external file
*/

#include <iostream> 
#include <fstream> // includes file i/o
#include <cstdlib> // includes exit
#include "lab11Func.h" //includes lab11Func.h

using namespace std;

int main()
{
	ifstream fin;//creates ifstream
	ofstream fout; //creates ofstream
		
	char filename[16];//creates char array

	greetings();//call for greetings

	cout << "What input file would you like to open (MAX OF 15 char)?";
	cin >> filename;
	
	
	fin.open (filename);//opens file
	while (fin.fail())//error checking (enter new filename)
	{
		fin.close();
		cout << "Enter in a new file please" << endl;
		cin >> filename;
		fin.open(filename);
	}
	if (fin.fail())//error checking
	{
		cout << "ERROR: Input file opening failed" << endl;
	}
	
	fout.open("Mini5Ouput.dat");//opens output file
	if (fout.fail())//error checking
	{
		cout << "ERROR: Output file opening failed" <<endl;
	}
	

	
	
	fout << "Name of File: " << filename<< endl;//sends to output file
	average(filename, fout);//call for average
	sum(filename, fout); //call for sum



	fin.close();//closes stream
	fout.close();//closes stream
	goodbye();//call for goodbye
	return 0;
}
