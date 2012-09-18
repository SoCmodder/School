// Section 7.3.1
// $ CC lookup.cpp main3_1a.cpp

/*
  the number 3 was found 1 times
  the number 1 was found 2 times
  ok, 11 was not found
*/

#include <iostream>
using std::cout;

#include <vector>
using std::vector;

// definition in lookup.C
vector<int>::const_iterator 
	look_up( const vector<int> &vec,
		 int value,     // is value in the vector?
		 int &occurs ); // how many times?

int main() {

	int ia[10] = { 0, 1, 1, 2, 3, 5, 8 };
	
	vector<int> vi ( ia, ia+7 );

	vector<int>::const_iterator it;
	int times = 0;

	look_up( vi, 3, times );
	cout << "the number 3 was found " << times << " times\n";	

	look_up( vi, 1, times );
	cout << "the number 1 was found " << times << " times\n";	

	it = look_up( vi, 11, times );
	if ( it == vi.end() )
		cout << "ok, 11 was not found\n";	

        return 0;
}

