// CS54Demo2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "complex.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Complex com( 1, -4 );

	cout << "complex number: " << com << endl;

	system( "PAUSE" );
	return 0;
}

