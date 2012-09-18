//Filename: cs234prog3.cpp
//Programmer: Derek Buchheit

#include <iostream.h>

float m_log(float fNum);
//Precondition: A floating point number >0 is passed in.
//Postcondition: An estimated natural log of the number is returned
float m_exp(float fNum);
//Precondition: Any floating point number is passed in. 
//Postcondition: The estimated exponential of the number is returned. 
float m_log10(float fNum);
//Precondtion: Any floating point number >0 is passed in. 
//Postcondition: The estimated log base 10 of the number is returned. 
float m_pow(float fBase, float fExp);
//Precondition: The base number, and the exponent are passed in
//Postcondition: The estimated value of the base raised to the inputted power
//is returned. 

int main()
{
	float input, result, pow;
	int menu;
	cout << "Which function do you want?\n1. m_log\n2. m_exp\n"
		 << "3. m_log10\n4. m_pow\n";
	cin >> menu;
	if(menu==1) //m_log
	{		
		cout << "What number do you want to take the natural log of? ";
		cin >> input;
		result = m_log(input);
		cout << "Result is: "<< result <<endl;
	}

	else if(menu==2) //m_exp
	{

		cout << "What number do you want to take the exponential of? ";
	    cin >> input;
	    result = m_exp(input);
		cout << "Result is: "<< result <<endl;
	}

	else if(menu==3) //m_log10
	{
		cout << "What number so you want to take the log10 of? ";
		cin >> input;
		result = m_log10(input);
		cout << "Result is: " << result << endl;
	}

	else //m_pow
	{
		cout << "Enter the base number: ";
		cin >> input;
		cout << "What power do you want to raise it to? ";
		cin >> pow;
		result = m_pow(input, pow);
		cout << "Result is: " << result << endl;
	}
	return 0;
}

float m_log(float fNum)
{
	float total=0, fVal=0, temp, coeff=1, power;
	for(int counter = 0; counter < 60; counter++)
	{
		fVal = ((fNum - 1)/(fNum + 1));
		temp = fVal;
		power = coeff;
		while(power > 1) //Raises part in parenthesis to correct power
		{
			fVal = fVal * temp;
			power--;
		}
		fVal = (1/coeff) * fVal; //Multiplies by the leading fraction
		total = total + fVal;
		coeff = coeff + 2;
	}
	total = total * 2;
	return (total);
}

float m_exp(float fNum)
{
    int denominator, temp_ctr;
    float total=0.0, numerator;
    for(int counter = 0; counter < 10; counter++)
	{
		temp_ctr=1;
		numerator = 1;
		denominator = 1;
		while (temp_ctr <= counter) //Calculates the Numerator and Denominator
		{
			numerator = numerator * fNum; //Eventually raises to correct power
			denominator = denominator * temp_ctr;//Eventually performs factorial
			temp_ctr++;
		}
		total = total + (numerator/denominator);
	}
	return total;
}

float m_log10(float fNum)
{
	return (m_log(fNum)/m_log(10));
}

float m_pow(float fBase, float fExp)
{
	return(m_exp(fExp*m_log(fBase)));
}
