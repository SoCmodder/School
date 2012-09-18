#include <algorithm>
#include <string>
#include <vector>
#include <utility>

#include <iostream.h>
#include <fstream.h>

#include <stddef.h>

extern vector<string,allocator> *retrieve_text();

int main() 
{
	vector<string,allocator> *text_file = retrieve_text();


	cout << "----------- about to generate text read --------------\n";
	ostream_iterator< string > output( cout, "\n" );
        copy( text_file->begin(), text_file->end(), output );

	return 0;
}

vector<string,allocator>*
retrieve_text()
{
	string file_name;
	
	cout << "please enter file name: ";
	cin  >> file_name;

	ifstream infile( file_name.c_str(), ios::in );
	if ( !infile ) {
		cerr << "oops! unable to open file "
		     << file_name << " -- bailing out!\n";
		exit( -1 );
	}
	else cout << "\n";

	vector<string,allocator> *lines_of_text = new vector<string,allocator>;
        string textline;

        typedef pair<string::size_type, int> stats;
        stats maxline;
	int   linenum = 0;

        while ( getline( infile, textline, '\n' ))
	{
		cout << "line read: " << textline << "\n";

		if ( maxline.first < textline.length() )
		{
		     maxline.first = textline.length();
		     maxline.second = linenum;
		}

		lines_of_text->push_back( textline );
		linenum++;
	}

	cout << "\n";
        cout << "number of lines: " 
             << lines_of_text->size() << "\n";

	cout << "maximum length: "  
	     << maxline.first << "\n";

        cout << "longest line: "    
	     << (*lines_of_text)[ maxline.second ] << "\n";
	
	return lines_of_text;
}

/*
dumbo[107] ~/d.stdlib => a.out
please enter file name: alice_emma

line read: Alice Emma has long flowing red hair. Her Daddy says
line read: when the wind blows through her hair, it looks almost alive,
line read: like a fiery bird in flight. A beautiful fiery bird, he tells her,
line read: magical but untamed. "Daddy, shush, there is no such thing,"
line read: she tells him, at the same time wanting him to tell her more.
line read: Shyly, she asks, "I mean, Daddy, is there?"

number of lines: 6
maximum length: 66
longest line: like a fiery bird in flight. A beautiful fiery bird, he tells her,
----------- about to generate text read --------------
Alice Emma has long flowing red hair. Her Daddy says
when the wind blows through her hair, it looks almost alive,
like a fiery bird in flight. A beautiful fiery bird, he tells her,
magical but untamed. "Daddy, shush, there is no such thing,"
she tells him, at the same time wanting him to tell her more.
Shyly, she asks, "I mean, Daddy, is there?"
*/
