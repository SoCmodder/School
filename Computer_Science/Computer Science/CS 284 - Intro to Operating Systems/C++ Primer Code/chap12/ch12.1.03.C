#include <algorithm>
#include <list>
#include <iostream.h>
// #include <iostream>

/**
 **
 stanl@john:d.12 320 : a.out
 enter search value: 42
 The value 42 is not present

 stanl@john:d.12 321 : a.out
 enter search value: 83
 The value 83 is present
 **
 **/

int main()
{
  	int search_value;
  	int ia[ 6 ] = { 27, 210, 12, 47, 109, 83 };
  	list<int> ilist( ia, ia+6 );

  	cout << "enter search value: ";
  	cin >> search_value;

  	list<int>::iterator presult;
  	presult = find( ilist.begin(), ilist.end(), search_value );

  	cout << "The value " << search_value
     		<< (presult == ilist.end()
      			? " is not present" : " is present" )
       		<< endl;
}
