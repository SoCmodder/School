#include <vector>
#include <algorithm>
#include <iostream.h>
// #include <iostream>

/**
 **
 original elements of vector: 51 23 7 88 41 98 12 103 37 6 
 sorted elements of vector:   6 7 12 23 37 41 51 88 98 103 

 please enter search value: 41
 search_value found!

 reversed elements of vector: 103 98 88 51 41 37 23 12 7 6 
 **
 **/

int ia[ 10 ] = {
  	51, 23, 7, 88, 41, 98, 12, 103, 37, 6 
};

int main()
{
  	vector< int > vec( ia, ia+10 );
	vector<int>::iterator 
		it = vec.begin(), 
		end_it = vec.end();

	cout << "original elements of vector: ";
	for ( ; it != end_it; ++ it ) cout << *it << ' ';
	cout << "\n";

  	// sort the array
  	sort( vec.begin(), vec.end() );

	cout << "sorted elements of vector:   ";
        it = vec.begin(); end_it = vec.end();
        for ( ; it != end_it; ++ it ) cout << *it << ' ';
	cout << "\n\n";

  	// grab value to search for
  	int search_value;
	cout << "please enter search value: ";
  	cin >> search_value;

  	// search for an element
  	vector<int>::iterator found;
  	found = find( vec.begin(), vec.end(), search_value );

  	if ( found != vec.end() )
             cout << "search_value found!\n\n";
        else cout << "search_value not found!\n\n";

  	// reverse the array
  	reverse( vec.begin(), vec.end() );

        cout << "reversed elements of vector: ";
        it = vec.begin(); end_it = vec.end();
        for ( ; it != end_it; ++ it ) cout << *it << ' ';
	cout << endl;
}

