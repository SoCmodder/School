#include <string>
#include <fstream>
#include <sstream>

/**
 ** note: no available sstream implementation
 **       available at this time -- code has not
 **       been exercised
 **
 **/

string read_file_into_string()
{
	ifstream ifile( "alice_emma" );
	ostringstream buf;
	char ch;
	while ( buf && ifile.get( ch ))
 	        buf.put( ch );
	return buf.str();
}

int main()
{
	string text = read_file_into_string();

	// marks the position of each newline within text
	vector< string::size_type > lines_of_text;

	string::size_type pos = 0;
	while ( pos != string::npos )
	{
		pos = text.find( 'n' pos );
		lines_of_text.push_back( pos );
	}

	// ...
}





