#include <iostream>
#include <sstream>

/**
 ** note: no available sstream implementation
 **       available at this time -- code has not
 **       been exercised
 **
 **/

int main()
{
	int    ival  = 1024;    
        int   *pival = &ival;

	double  dval  = 3.14159; 
        double *pdval = &dval;

	ostringstream format_message;

	// ok: converts values to a string representation
	format_message << "ival: "  << ival
	               << " ival address: " << pival << 'n'
	               << "dval: " << dval
	               << " dval address: " << pdval << endl;

	string msg = format_message.str();
	cout << " size of message string: " 
	     << msg.size()
	     << " message: " 
	     << msg << endl;
}
