#include <algorithm>
#include <vector>
#include <iostream.h>
// #include <iostream>

/**
 **
 stanl@john:d.12 315 : a.out
 enter search value: 218
 The value 218 is not present

 stanl@john:d.12 316 : a.out
 enter search value: 210
 The value 210 is present
 **
 **/

int main()
{
  	int search_value;
  	int ia[ 6 ] = { 27, 210, 12, 47, 109, 83 };
  	vector<int> vec( ia, ia+6 );

  	cout << "enter search value: ";
  	cin >> search_value;

  	vector<int>::iterator presult;
  	presult = find( vec.begin(), vec.end(), search_value );

  	cout << "The value " << search_value
     		<< (presult == vec.end()
      			? " is not present" : " is present" )
       		<< endl;
}
