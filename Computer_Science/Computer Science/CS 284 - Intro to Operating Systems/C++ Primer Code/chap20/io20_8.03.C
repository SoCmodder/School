#include <iostream>
#include <sstream>
#include <string>

/**
 ** note: no available sstream implementation
 **       available at this time -- code has not
 **       been exercised
 **
 **/

int main()
{
	int ival   = 1024;    
	int *pival = &ival;

	double dval   = 3.14159; 
	double *pdval = &dval;

	// creates a string in which each value is
	// is stored separated by a space
	ostringstream format_string;

	format_string << ival << " " 
		      << pival << " "
  		      << dval << " " 
		      << pdval << endl;

	// extracts the stored ascii values, 
	// placing them in turn in the four objects
	istringstream input_istring( format_string.str() );

	input_istring >> ival >> pival
  		      >> dval >> pdval;
}
