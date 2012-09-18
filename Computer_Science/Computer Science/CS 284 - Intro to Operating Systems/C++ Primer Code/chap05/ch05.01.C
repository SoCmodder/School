// #include <fstream>
#include <fstream.h>
#include <string>
#include <vector>

/*****
 *****
 Please enter name of file to open: infile
 original string: fa.disney.com
 original string: research.att.com
 original string: vnet.ibm.com
 transformed string: fa_disney_com
 transformed string: research_att_com
 transformed string: vnet_ibm_com
 *****
 *****/

int main()
{
	string fileName; 
	cout << "Please enter name of file to open: ";
	cin >> fileName;

	if ( fileName.empty() ) 
	{
     		// yes, extreme: but we have a point to illustrate
     		cerr << "fileName is empty. bailing out. bye!\n";
     		return -1;
	}

	ifstream inFile( fileName.c_str() ); 
	if ( !inFile ) {
		cerr << "unable to open file. bailing out. bye!\n";
     		return -2;
	}

	string inBuf;          
	vector< string > text; 

	while ( inFile >> inBuf ) 
	{
		cout << "original string: " << inBuf << endl;

		string::iterator iter = inBuf.begin(), 
				 endit = inBuf.end();

		for ( ; iter != endit; ++iter )
		{
              		// current compiler does not support this!
			// if (( char ch = *iter ) == '.' ) 
			char ch = *iter;;
              		if ( ch == '.' ) 
			   { ch = '_'; *iter = ch; }
		}

        	text.push_back( inBuf );
		
	}

	if ( text.empty() )
     		return 0;

	// one declaration statement, two definitions
	vector<string>::iterator iter = text.begin(),
                         	 iend = text.end();
	while ( iter != iend ) 
	{
        	cout << "transformed string: " << *iter  << '\n';
        	++iter;
	}

	return 0;
}

