// Section 7.3.1
// $ CC ptrswap.cpp main3_1b.cpp

/*
  Before ptrswap():       pi: 10  pj: 20
  After ptrswap():        pi: 20  pj: 10
*/

#include <iostream>
using std::cout;
using std::endl;

// defined in ptrswap.cpp
void ptrswap( int *&v1, int *&v2 );

int main() {
	int i = 10;
	int j = 20;

	int *pi = &i;
	int *pj = &j;

	cout << "Before ptrswap():\tpi: "
	     << *pi << "\tpj: " << *pj << endl;

	ptrswap( pi, pj );
	cout << "After ptrswap():\tpi: "
	     << *pi << "\tpj: " << *pj << endl;

	return 0;
}
