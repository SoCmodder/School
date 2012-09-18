//Filename: cs234prog3comment.cpp
//Programmer: Derek Buchheit

#include <iostream.h>

float m_log(float fNum);
//Precondition: A floating point number >0 is passed in.
//Postcondition: An estimated ln of the number is returned
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
	//Store this menu in the data section
	cout << "Which function do you want?\n1. m_log\n2. m_exp\n"
		 << "3. m_log10\n4. m_pow\n";
	cin >> menu; //Use syscall to get input
	if(menu==1) //log_choice: use bne
	{		
		cout << "What number do you want to take the natural log of? ";
		cin >> input;
		result = m_log(input);
		cout << "Result is: "<< result <<endl;
	}

	else if(menu==2) //exp_choice: use bne
	{

		cout << "What number do you want to take the exponential of? ";
	    cin >> input;
	    result = m_exp(input);
		cout << "Result is: "<< result <<endl;
	}

	else if(menu==3) //log10_choice: use bne
	{
		cout << "What number so you want to take the log10 of? ";
		cin >> input;
		result = m_log10(input);
		cout << "Result is: " << result << endl;
	}

	else //pow_choice: use bne
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
	float total=0, fVal=0, temp; 
	int coeff=1, power;
	for(int counter = 0; counter < 60; counter++) //put label here
	{
		fVal = ((fNum - 1)/(fNum + 1));//divide into 3 different instructions
		temp = fVal; //Use add.s 
		power = coeff;//Use add.s 
		while(power > 1) //Use ble? to check with a label here
		{
			fVal = fVal * temp; //mul.s 
			power--;
		}
		fVal = (1/coeff) * fVal; //Split into 2 operations
		total = total + fVal; //add.s
		coeff = coeff + 2;//add.s
	}
	total = total * 2;
	return (total);
}

float m_exp(float fNum)
{
    int denominator, temp_ctr;
    float total=0.0, numerator; //$f4 = total
    //set counter $f5 to 0
	for(int counter = 0; counter < 10; counter++) //put label here
	{
		temp_ctr=1; // use li to initialize variables
		numerator = 1;
		denominator = 1;
		while (temp_ctr <= counter) //put another label here
		{
			numerator = numerator * fNum; //Eventually raises to correct power
			denominator = denominator * temp_ctr;//Eventually performs factorial
			temp_ctr++;
		}
		total = total + (numerator/denominator);//divide into multiple steps
	//add 1 to counter here
	}
	return total;
}

float m_log10(float fNum)
{
	return (m_log(fNum)/m_log(10));
	//Must use stack to store values and divide into multiple steps
}

float m_pow(float fBase, float fExp)
{
	return(m_exp(fExp*m_log(fBase)));
	//Must use stack, and divide into several different steps
}
