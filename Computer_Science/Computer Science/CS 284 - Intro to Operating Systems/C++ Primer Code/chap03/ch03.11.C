// #include <iostream>
#include <iostream.h>
#include <algorithm>
#include <string>

template <class elemType>
void printElems( elemType *pbegin, elemType *pend, ostream &os = cout )
{
	while ( pbegin != pend )
		os << *pbegin++ << ' ';
}

/**
 **
integer array before sort(): 107 28 3 47 104 76 
integer array after sort(): 3 28 47 76 104 107 
string array before sort(): Piglet Eeyore Pooh 
string array after sort(): Eeyore Piglet Pooh 
 **
 **/

int main()
{
    int ia[6] = { 107, 28, 3, 47, 104, 76 };
    cout << "integer array before sort(): "; 
    printElems( ia, ia+6 ); cout << endl;
    sort( ia, ia+6 );
    cout << "integer array after sort(): "; 
    printElems( ia, ia+6 ); cout << endl;

    string sa[3] = { "Piglet", "Eeyore", "Pooh" };
    cout << "string array before sort(): "; 
    printElems( sa, sa+3 ); cout << endl;
    sort( sa, sa+3 );
    cout << "string array after sort(): "; 
    printElems( sa, sa+3 ); cout << endl;
}
