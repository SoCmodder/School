#include <algorithm>
#include <vector>
#include <iostream.h>
	
/* generates:
original order of the vector: 29 23 20 22 17 15 26 51 19 12 35 40 
sorting vector based on element 26
12 15 17 19 20 22 23 26 51 29 35 40 
sorting vector in descending order based on element 23
40 35 29 51 26 23 22 20 19 17 15 12 
*/

int main()
{
	int ia[] = {29,23,20,22,17,15,26,51,19,12,35,40}; 
	vector< int,allocator > vec( ia, ia+12 );
	ostream_iterator<int> out( cout," " ); 

	cout << "original order of the vector: ";
	copy( vec.begin(), vec.end(), out ); cout << endl;
		
	cout << "sorting vector based on element "
	     << *( vec.begin()+6 ) << endl;
	nth_element( vec.begin(), vec.begin()+6, vec.end() );
	copy( vec.begin(), vec.end(), out ); cout << endl;
		
	cout << "sorting vector in descending order "
             << "based on element "
	     << *( vec.begin()+6 ) << endl;
	nth_element( vec.begin(), vec.begin()+6, 
	             vec.end(),   greater<int>() );
	copy( vec.begin(), vec.end(), out ); cout << endl;
		
	return 0;
}
