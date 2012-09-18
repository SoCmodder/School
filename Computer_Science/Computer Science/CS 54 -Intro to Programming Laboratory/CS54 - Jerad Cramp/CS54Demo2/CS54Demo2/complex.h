#ifndef COMPLEX_H
#define COMPLEX_H

#include "stdafx.h"
#include <fstream>
using namespace std;

/********** CLASS **********/

class Complex
{
	int real;
	int img;

public:
	Complex();
	Complex( int rl, int ig );

	int getReal()const;
	int getImg()const;

	friend ostream& operator<<( ostream& os, const Complex& com );
};

/********** CLASS **********/

#endif
