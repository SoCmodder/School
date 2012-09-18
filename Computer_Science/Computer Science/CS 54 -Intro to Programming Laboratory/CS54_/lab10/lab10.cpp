/* 
* Author: Elliot Gross
* Date: 3/14/06
* Filename: lab10.cpp
* Instructor: Brian Sea
* Description: This program will take a phrase and apply the caesar
* cipher to the phrase to "encrypt" it
*/

#include <iostream>
#include "lab10Func.h" //includes lab9Func.h
using namespace std;

int main()
{
	char source[10] = "omgHAX";
	char destination[15] = "Dole";
	char s1[10] = "Hooray!";
	char d1[5] = "Yay!";
	char s2[15] = "Sniper pwns ";
	char d2[15] = "Pistol pwns"; 

	int size = strlen(destination);
	int size1 = strlen(d1);
	int size2 = strlen(d2);
	int n = strlen(destination);

	cout << "Testing ntsCopy!" << endl;
	cout << source << endl;
	cout << destination << endl;

	ntsCopy(source, destination, size);
	
	cout << source << endl;
	cout << destination << endl;
	// test1 for ntscopy

	cout << "Testing ntsCopy!" << endl;
	cout << s1<< endl;
	cout << d1 << endl;

	ntsCopy(s1, d1, size1);
	
	cout << s1 << endl;
	cout << d1 << endl;
	//test 2 for ntscopy

	cout << "Testing ntsCopy!" << endl;
	cout << s2 << endl;
	cout << d2 << endl;

	ntsCopy(s2, d2, size2);
	
	cout << s2 << endl;
	cout << d2 << endl;
	//test 3 for ntscopy

	strncpy(source, "omgHAX", 10);
	strncpy(destination, "Dole", 15);

	cout << "Testing ntsNCopy!" << endl;
	cout << source << endl;
	cout << destination << endl;
	
	ntsNCopy(source, destination, size, size);

	cout << source << endl;
	cout << destination << endl;
	// test 1 for ntsNCopy

	strncpy(s1, "Hooray!", 10);
	strncpy(d1, "Yay!", 5);

	cout << "Testing ntsNCopy!" << endl;
	cout << s1 << endl;
	cout << d1 << endl;
	
	ntsNCopy(s1, d1, size1, size1);

	cout << s1 << endl;
	cout << d1 << endl;

	// test 2 for ntsNCopy

	strncpy(s2, "Sniper pwns ", 15);
	strncpy(d2, "Pistol pwns ", 15);

	cout << "Testing ntsNCopy!" << endl;
	cout << s2 << endl;
	cout << d2 << endl;
	
	ntsNCopy(s2, d2, size2, size2);

	cout << s2 << endl;
	cout << d2 << endl;

	// test 3 for ntsNCopy

	strncpy(source, "omgHAX", 10);
	strncpy(destination, "Dole", 15);

	cout << "Testing ntsCat!" << endl;
	cout << source << endl;
	cout << destination << endl;
	
	ntsCat(source, destination, size);

	cout << source << endl;
	cout << destination << endl;
	//test 1 for ntsCat

	strncpy(s1, "Hooray!", 10);
	strncpy(d1, "Yay!", 5);

	cout << "Testing ntsCat!" << endl;
	cout << s1 << endl;
	cout << d1 << endl;
	
	ntsCat(s1, d1, size1);

	cout << s1 << endl;
	cout << d1 << endl;
	//Test 2 for ntsCat
	
	strncpy(s2, "Sniper pwns ", 15);
	strncpy(d2, "Pistol pwns ", 15);

	cout << "Testing ntsCat!" << endl;
	cout << s2 << endl;
	cout << d2 << endl;
	
	ntsCat(s2, d2, size2);

	cout << s2 << endl;
	cout << d2 << endl;
	//Test 3 for ntsCat

	strncpy(source, "omgHAX", 10);
	strncpy(destination, "Dole", 15);
	
	cout << "Testing ntsNCat!" << endl;
	cout << source << endl;
	cout << destination << endl;
	
	ntsNCat(source, destination, size, size);

	cout << source << endl;
	cout << destination << endl;
	// Test 1 for ntsNCat

	strncpy(s1, "Hooray!", 10);
	strncpy(d1, "Yay!", 5);
	
	cout << "Testing ntsNCat!" << endl;
	cout << s1 << endl;
	cout << d1 << endl;
	
	ntsNCat(s1, d1, size1, size1);

	cout << s1 << endl;
	cout << d1 << endl;
	// Test 2 for ntsNCat

	strncpy(s2, "Sniper pwns ", 15);
	strncpy(d2, "Pistol pwns ", 15);

	cout << "Testing ntsNCat!" << endl;
	cout << s2 << endl;
	cout << d2 << endl;
	
	ntsNCat(s2, d2, size2, size2);

	cout << s2 << endl;
	cout << d2 << endl;
	// Test 3 for ntsNCat


	return 0;
}
