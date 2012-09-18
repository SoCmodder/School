// #include <iostream>

#include <iostream.h>
#include <string>

/**
 ** Please enter your name: winnie-the-pooh
 ** hello, winnie-the-pooh!
 **
 **/


int main() 
{
	string in_string;

	// write literal string to user's terminal
	cout << "Please enter your name: ";

	// read user's input into in_string
	cin >> in_string;

	if ( in_string.empty() )
     	     // generate an error message to userls terminal
     	     cerr << "error: input string is empty!\n";
	else cout << "hello, " << in_string << "!\n";
}
