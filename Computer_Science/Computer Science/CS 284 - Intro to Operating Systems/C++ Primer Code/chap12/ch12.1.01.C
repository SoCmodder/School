template < class ForwardIterator, class Type >
ForwardIterator
find( ForwardIterator first, ForwardIterator last, Type value )
{
  	for ( ; first != last; ++first )
   		if ( value == *first )
        		return first;
  	return last;
}

#include <iostream.h>
// #include <iostream>

/**
 **
 stanl@john:d.12 303 : a.out
 enter search value: 210
 The value 210 is present

 stanl@john:d.12 304 : a.out
 enter search value: 42
 The value 42 is not present
 **
 **/

int main()
{
	int search_value;
  	int ia[ 6 ] = { 27, 210, 12, 47, 109, 83 };

  	cout << "enter search value: ";
  	cin >> search_value;

  	int *presult = find( ia, ia+6, search_value );

  	cout << "The value " << search_value
     		<< (presult == &ia[6]
      			? " is not present" : " is present" )
       		<< endl;
}
