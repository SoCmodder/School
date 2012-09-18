#include <algorithm>
#include <string>
#include <vector>
#include <utility>

#include <iostream.h>
#include <fstream.h>

#include <stddef.h>

typedef pair<short,short>           location;
typedef vector<location,allocator>  loc;
typedef vector<string,allocator>    text;
typedef pair<text*,loc*>            text_loc;

extern vector<string,allocator> *retrieve_text();
extern text_loc *separate_words( const vector<string,allocator>* );
extern void display_text_locations( text_loc* );
extern void filter_text( vector<string,allocator>*, string filter );
extern void suffix_text( vector<string,allocator>* );
extern void suffix_s( string& );

int main() 
{
	vector<string,allocator>   *text_file      = retrieve_text();
        text_loc 		   *text_locations = separate_words( text_file );

        string filt_elems( "\",.;:!?)(" );
        filter_text( text_locations->first, filt_elems );
        suffix_text( text_locations->first );	

	ostream_iterator< string > output( cout, "\n" );

	cout << "----------- about to generate text read --------------\n";
        copy( text_file->begin(), text_file->end(), output );

	cout << "-------- about to generate word and location data ----\n";
	display_text_locations( text_locations );

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

text_loc*
separate_words( const vector<string,allocator> *text_file )
{
        // ok: now have all the lines. wish to grab the
        // individual words: look for blanks:

        vector<string,allocator>   *words     = new vector<string,allocator>;
	vector<location,allocator> *locations = new vector<location,allocator>;

        for ( short line_pos = 0; line_pos < text_file->size(); line_pos++ )
        {
		short  word_pos = 0;
                string textline = (*text_file)[ line_pos ];

                cout << "textline: " << textline << endl;

                string::size_type eol = textline.length();
                string::size_type pos = 0, prev_pos = 0;

                while (( pos = textline.find_first_of( ' ', pos )) != string::npos )
                {
                        cout << "eol: "  << eol << " "
			     << "pos: "  << pos << " "
			     << "line: " << line_pos << " "
			     << "word: " << word_pos << " "
                             << "substring: " 
                             << textline.substr( prev_pos, pos-prev_pos ) 
			     << "\n";

                        words->push_back( textline.substr( prev_pos, pos - prev_pos ));
			locations->push_back( make_pair( line_pos, word_pos ));

                        word_pos++; pos++; prev_pos = pos;
                }

	        cout << "last word on line substring: " 
                     << textline.substr( prev_pos, pos-prev_pos ) 
		     << "\n";

                words->push_back( textline.substr( prev_pos, pos - prev_pos ));
		locations->push_back( make_pair( line_pos, word_pos ));
        }
	
        return new text_loc( words, locations );
}

void 
display_text_locations( text_loc *text_locations )
{
        vector<string,allocator>   *text_words     = text_locations->first;
        vector<location,allocator> *text_locs      = text_locations->second;

        register int elem_cnt = text_words->size();

        if ( elem_cnt != text_locs->size() )
        {
	     cerr << "oops! internal error: word and position vectors "
		  << "are of unequal size\n"
		  << "words: " << elem_cnt << " "
		  << "locs: "  << text_locs->size() 
		  << " -- bailing out!\n";
	     exit( -2 );
	}

        for ( int ix = 0; ix < elem_cnt; ix++ ) 
        {
		cout << "word: " << (*text_words)[ ix ] << "\t"
		     << "location: (" 
		     << (*text_locs)[ix].first  << ","
		     << (*text_locs)[ix].second << ")"
		     << "\n";
	}

        cout << endl;
}

void 
filter_text( vector<string,allocator> *words, string filter )
{
	vector<string,allocator>::iterator iter = words->begin();
	vector<string,allocator>::iterator iter_end = words->end();

        if ( ! filter.size() )
             filter.insert( 0, "\".," );

        cout << "filter elements: " << filter << endl;

	while ( iter != iter_end )
	{
		cout << "filter_text: " << *iter << endl; 

                string::size_type pos = 0;
                while (( pos = (*iter).find_first_of( filter, pos )) != string::npos )
                {
                        cout << "found! : pos: " 
			     << pos << "\t" 
			     << (*iter)[pos] << endl;

			// this is wrong: erases from pos to npos
                        // (*iter).erase(pos);
                        (*iter).erase(pos,1);

			cout << "after: " << *iter << endl;
                }

		cout << "finished with word: " << *iter << endl;

		iter++;
	}
}

void
suffix_text( vector<string,allocator> *words )
{
        vector<string,allocator>::iterator iter = words->begin();
        vector<string,allocator>::iterator iter_end = words->end();

        while ( iter != iter_end )
        {
                cout << "suffix_text: " << *iter << endl;

		// if 3 or less characters, let it be
		if ( (*iter).size() <= 3 ) {
		     iter++; 
		     continue;
                }

		if ( (*iter)[ (*iter).size()-1 ] == 's' )
		     suffix_s( *iter );

		// additional suffix handling goes here ...

                iter++;
        }
}

void
suffix_s( string &word )
{
	cout << "suffix_s -- word passed in: " << word << endl;

	string::size_type pos3 = word.size()-3;
	char ch2 = word[ pos3+1 ];

	// "ss" or "is" ending? return
	if ( ch2 == 's' || ch2 == 'i' )
	     return;

	// "ous" ending? return
	if ( ch2 == 'u' && word[ pos3 ] == 'o' )
	     return;

	// "ies" ending? replace with 'y'
	if ( ch2 == 'e' && word[ pos3 ] == 'i' )
	{
	     word.replace( pos3, 3, 1, 'y' );
	     cout << "suffix_s -- word returned: " << word << endl;

	     return; 
	}

	// erase ending 's'
	word.erase( pos3+2 );
	cout << "suffix_s -- word returned: " << word << endl;
}

