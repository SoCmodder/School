//Filename: cs234prog2comment.cpp
//Programmer: Derek Buchheit

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

	char input;  //Will use $t0 register
	int func_choice; //Will use $t1 register

	cout << "Which function do you want? " //Put this in data segment
		 << "1. isspace "
		 << "2. m_toupper "
		 << "3. m_atoi\n";
	cin >> func_choice; //put in $t1
	if (func_choice == 1) //use bne $t1, 1
	{
		input = '\n';  //$t0, value that we will use to test m_isspace 
		cout << m_isspace(input); //jal m_isspace, output result
	}
	else if(func_choice == 2) //use bne $t1, 2
	{
		cout << "Enter letter ";
		cin >> input; //store in $t0
		cout << m_toupper(input);//jal m_toupper, output result
	}
	else
	{
        char *cinput; 
		int result;
		cinput = "-123";      // What we will test m_atoi with
		result = m_atoi(cinput);
		cout <<"result is: " << result;
	}
	cout << endl;
	return 0;
}

bool m_isspace(char chtest) //$v0 = return value, $a0 = chtest
{
	//li $v0, 0
	if (chtest == 0x20 || chtest == 0x0a || chtest == 0x0c || chtest == 0x0d)
	//used hex numbers to make conversion to assembly easier, use 4 different bne checks
		return true; //li $v0, 1
	else //after_if:
		return false; //return $v0, will be set to true or false already
}

char m_toupper(int ch_convert) //$v0 = return value, $a0 = ch_convert
{
	//In ASM we will pass in a pointer to the character. Then change it. 
	ch_convert = ch_convert - 32; //converts to uppercase addi $v0, $a0, -32
	return ch_convert;  //jr ra
}

int m_atoi( const char * conv ) //conv = $s0
{ 
    // The current character. 
    int  cCurr ;  //t0
    // The total. 
    int iTotal ; //$t1
    // Holds the '-' sign. 
    int  iIsNeg ; //$t2

    // go past any whitespace. 
    while (m_isspace ( *conv ) )//We will need to call m_isspace, 
		//then test the return value in a different step. Must use the stack
    { 
        conv++ ; //addi $t0, 1
    } 

    // Get the current character. 
    cCurr = *conv++ ; //Will use a load word and then an add
    // Save the negative sign. 
    iIsNeg = cCurr ; //move $t3, $t1
    if ( ( '-' == cCurr ) || ( '+' == cCurr ) ) //Use 2bne statements
    { 
        // We have a sign, so skip it. 
        cCurr = *conv++ ; //move $t1, $t0, then addi $t0, 1
    } 
    //aftersign label

    // Initialize the total. 
    iTotal = 0 ; //li $t1, 0

    // Continue adding while there are still characters
    //convert:
	while (cCurr != '\0' )//beq $t0, '\0', after_convert
    { 
        // Converts to int and, adds this number to the total. 
        iTotal = 10 * iTotal + ( cCurr - '0' ) ; //perform cCurr-'0', 
		//then 10 * total use mul, then add new number to total 
        // Do the next character. 
        cCurr = *conv++ ; //move $t1, $t0, then addi $t0, 1
    } 
	//after_convert:

    // If we have a negative sign, convert the value. 
    if ( '-' == iIsNeg ) //bne $t2, 0x2d, pos 
    { 
        return ( -iTotal ) ; //sub $v0, $0, $t1
    }                        //jr $ra
    else //pos:
    { 
        return ( iTotal ) ; //move $v0, $t1
    }						//jr $ra
} 
