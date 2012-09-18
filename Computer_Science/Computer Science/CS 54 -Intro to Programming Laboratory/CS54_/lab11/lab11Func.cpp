/* 
* Author: Elliot Gross
* Date: 3/21/06
* Filename: lab11.cpp
* Instructor: Brian Sea
* Description: This program will read a certain amount 
* of numbers and will output data to an external file
*/

#include <iostream>
#include <fstream> //includes fstream
#include "lab11Func.h" //includes lab11Func.h
using namespace std;


void greetings()//function definition for greetings
{
	cout << endl << "Welcome to the Magic Filemaker!" << endl << endl;
	return;
}
void goodbye()//function definition for goodbye
{
	cout << endl << "Thanks!" << endl << endl;
	return;
}

void sum(char filename[], ofstream &fout)//function def. for sum
{
	ifstream fin; //creates a new ifstream
	fin.open(filename); //opens a new file

	while (fin.fail())//asks to enter new filename in
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

	float next, sum = 0;
	while(fin >> next)
		sum = sum + next;//gets the sum
   	fout << "The sum is " << sum << endl;

	
	fin.close();//closes the stream

}

void average(char filename[], ofstream &fout)
//function definition for avg
{
	ifstream fin;//creates a new ifstream
	fin.open(filename);//opens a new file

	if (fin.fail())//asks to enter new filename in
	{
		cout << "ERROR: Input file opening failed" << endl;
	}

	float next=0 , sum = 0;
	float avg=0;
	int count=0;
	while(fin >> next)
	{
		sum = sum + next; //sums 
		count ++;
	}
	avg = sum/count; //creates avg
	fout << "The number of integers calculated is " << count << endl;
	fout << "The average is " << avg << endl;

	fin.close(); //closes stream

}

