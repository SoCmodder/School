#include <stdafx.h>
#include "stuff.h"
#include <iostream>
using namespace std;

lastproject::lastproject()
{
	used=0;
    numbers = new int[90];
	int count=0;
	for(int i=71;i<=249;i=i+2)
	{
		numbers[count]=i;
		count++;
	}
}

lastproject::~lastproject()
{
	delete []number;
}

void lastproject::sum()
{
	int sum=0;
	for(int i=0;i<=89;i++)
	{
		sum=sum+numbers[i];
	}
	cout<<endl<<sum<<endl;
}

	