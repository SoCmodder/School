//Filename: cs234prog2.cpp
//Programmer: Derek Buchheit
//This program can call upon 3 different functions, to check if whitespace, 
//convert to uppercase, or convert ascii to integer

#include <iostream.h>
#include <string>

using namespace std;

int main()
{
	bool m_isspace(char chtest);
	//Precondition: Must pass in a single char value
	//Postcondition: Returns true if Whitespace, false if not
	char m_toupper(int ch_convert);
	//Precondition: Pass in a lowercase character
	//Postcondition: lowercase character is converted to uppercase and outputted
	int  m_atoi(const char * conv);
	//Precondition: Pass in a pointer to an ascii character string
	//Postcondition: Ascii string is converted to an integer and outputted

	char input;
	int func_choice;//Stores which function to perform

	cout << "Which function do you want? "
		 << "1. isspace "
		 << "2. m_toupper "
		 << "3. m_atoi\n";
	cin >> func_choice;
	if (func_choice == 1)
	{
		input = 'a';  //Value that we will uses to test m_isspace 
		cout << m_isspace(input);
	}
	else if(func_choice == 2)
	{
		cout << "Enter letter ";
		cin >> input;
		cout << m_toupper(input);
	}
	else
	{
        char *cinput; 
		int result;
		cinput = "123";      // What we will test m_atoi with
		result = m_atoi(cinput);
		cout <<"result is:" << result;
	}
	cout << endl;
	return 0;
}

bool m_isspace(char chtest)
{
	if (chtest == 0x20 || chtest == 0x0a || chtest == 0x0c || chtest == 0x0d)
	//used hex numbers to make conversion to assembly easier
		return true;
	else
		return false;
}

char m_toupper(int ch_convert)
{
	ch_convert = ch_convert - 32; //converts to uppercase
	return ch_convert;
}

int m_atoi( const char * conv ) 
{ 
    // The current character. 
    int  cCurr ; 
    // The total. 
    int iTotal ; 
    // Holds the '-' sign. 
    int  iIsNeg ; 

    // go past any whitespace. 
    while (m_isspace ( *conv ) ) 
    { 
        conv++ ; 
    } 

    // Get the current character. 
    cCurr = *conv++ ; 
    // Save the negative sign if needed. 
    iIsNeg = cCurr ; 
    if ( ( '-' == cCurr ) || ( '+' == cCurr ) ) 
    { 
        // We have a sign, so go past it. 
        cCurr = *conv++ ; 
    } 

    // Initialize the total. 
    iTotal = 0 ; 

    // Continue adding while there are still characters
    while (cCurr != '\0' ) 
    { 
        //Converts the number to an integer and adds to total
        iTotal = 10 * iTotal + ( cCurr - '0' ) ; 
        // Do the next character. 
        cCurr = *conv++ ; 
    } 

    // If we have a negative sign, convert the value. 
    if ( '-' == iIsNeg ) 
    { 
        return ( -iTotal ) ; 
    } 
    else 
    { 
        return ( iTotal ) ; 
    } 
} 
