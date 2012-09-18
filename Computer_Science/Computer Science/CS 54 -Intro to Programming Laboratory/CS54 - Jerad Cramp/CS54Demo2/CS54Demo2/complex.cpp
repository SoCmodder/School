#include "stdafx.h"
#include "complex.h"
#include <iostream>
using namespace std;

Complex::Complex()
{
	real = 0;
	img = 0;
}

Complex::Complex(int rl, int ig)
{
	real = rl;
	img = ig;
}

int Complex::getReal()const
{
	return real;
}

int Complex::getImg()const
{
	return img;
}

ostream& operator<<( ostream& os, const Complex& com )
{
	os << com.real;
	if( com.img >= 0) { os << "+"; }
	os << com.img << "i";
	return os;
}