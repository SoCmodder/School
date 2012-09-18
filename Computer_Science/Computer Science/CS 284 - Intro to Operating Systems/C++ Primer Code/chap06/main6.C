#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>

#include <iostream.h>
#include <fstream.h>

#include <stddef.h>
#include <ctype.h>

typedef pair<short,short>           location;
typedef vector<location,allocator>  loc;
typedef vector<string,allocator>    text;
typedef pair<text*,loc*>            text_loc;

extern vector<string,allocator> *retrieve_text();
extern text_loc *separate_words( const vector<string,allocator>* );
extern void filter_text( vector<string,allocator>*, string filter );
extern void strip_caps(  vector<string,allocator>* );
extern void suffix_text( vector<string,allocator>* );
extern void suffix_s( string& );

extern map< string, loc*, less<string>, allocator >*
       build_word_map( const text_loc *text_locations );

extern void query_text( vector<string,allocator>*, 
                        map<string,loc*,less<string>,allocator>* );

int main() 
{
	vector<string,allocator>   *text_file      = retrieve_text();
        text_loc 		   *text_locations = separate_words( text_file );

        string filt_elems( "\",.;:!?)(" );
        filter_text( text_locations->first, filt_elems );
        suffix_text( text_locations->first );	
	strip_caps(  text_locations->first );

	map<string,loc*,less<string>,allocator> *text_map = build_word_map( text_locations );
        query_text( text_file, text_map );

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
		if ( maxline.first < textline.length() )
		{
		     maxline.first = textline.length();
		     maxline.second = linenum;
		}

		lines_of_text->push_back( textline );
		linenum++;
	}

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

                string::size_type eol = textline.length();
                string::size_type pos = 0, prev_pos = 0;

                while (( pos = textline.find_first_of( ' ', pos )) != string::npos )
                {
                        words->push_back( textline.substr( prev_pos, pos - prev_pos ));
			locations->push_back( make_pair( line_pos, word_pos ));

                        word_pos++; pos++; prev_pos = pos;
                }

                words->push_back( textline.substr( prev_pos, pos - prev_pos ));
		locations->push_back( make_pair( line_pos, word_pos ));
        }
	
        return new text_loc( words, locations );
}

void 
filter_text( vector<string,allocator> *words, string filter )
{
	vector<string,allocator>::iterator iter = words->begin();
	vector<string,allocator>::iterator iter_end = words->end();

        if ( ! filter.size() )
             filter.insert( 0, "\".," );

	while ( iter != iter_end )
	{
                string::size_type pos = 0;
                while (( pos = (*iter).find_first_of( filter, pos )) != string::npos )
                       (*iter).erase(pos,1);
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
		// if 3 or less characters, let it be
		if ( (*iter).size() <= 3 ) { iter++; continue; }
		if ( (*iter)[ (*iter).size()-1 ] == 's' )
		       suffix_s( *iter );

		// additional suffix handling goes here ...

                iter++;
        }
}

void
suffix_s( string &word )
{
	string::size_type spos = 0;
	string::size_type pos3 = word.size()-3;

        // "ous", "ss", "is"
	string suffixes( "oussis" );

        if ( ! word.compare( pos3, 3, suffixes, spos, 3 ) ||
             ! word.compare( pos3+1, 2, suffixes, spos+2, 2 ) ||
             ! word.compare( pos3+1, 2, suffixes, spos+4, 2 ))
	       return;

	string ies( "ies" );
        if ( ! word.compare( pos3, 3, ies ))
	   { word.replace( pos3, 3, 1, 'y' ); return; }

	// erase ending 's'
	word.erase( pos3+2 );
}

void
strip_caps( vector<string,allocator> *words )
{
        vector<string,allocator>::iterator iter = words->begin();
        vector<string,allocator>::iterator iter_end = words->end();

	string caps( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

        while ( iter != iter_end ) {
                string::size_type pos = 0;
                while (( pos = (*iter).find_first_of( caps, pos )) != string::npos )
                       (*iter)[ pos ] = tolower( (*iter)[pos] );
                ++iter;
        }
}

map< string, loc*, less<string>, allocator >*
     build_word_map( const text_loc *text_locations )
{
     map< string, loc*, less<string>, allocator > *word_map = new map< string, loc*, less<string>, allocator >;
     typedef map<string,loc*, less<string>, allocator>::value_type value_type;

     // iterate through the the words, entering the key/pair

     vector<string,allocator>   *text_words = text_locations->first;
     vector<location,allocator> *text_locs  = text_locations->second;

     register int elem_cnt = text_words->size();
     for ( int ix = 0; ix < elem_cnt; ++ix )
           if ( ! word_map->count((*text_words)[ix] )) {  // not present, add it:
                  loc *ploc = new vector<location,allocator>;
                  ploc->push_back( (*text_locs)[ix] );
                  word_map->insert( value_type( (*text_words)[ix], ploc ));
           } else (*word_map)[(*text_words)[ix]]->push_back( (*text_locs)[ix] );

	return word_map;
}

void query_text( vector<string,allocator> *text_file, 
                 map<string,loc*,less<string>,allocator> *text_map )
{
	string query_text;
    
	do {
           cout << "enter a word against which to search the text.\n"
	        << "to quit, hit return\n";

	   cin >> query_text;

	   cout << "query read: " << query_text << " of size: " << query_text.size() << endl;

	   if ( query_text.empty() )
		break;

	   loc *ploc = (*text_map)[ query_text ];
	   if ( !ploc ) {
		cout << "Sorry. There are no entries for " 
		     << query_text << ".\n";
		continue;
	    }

	    set<short,less<short>,allocator> occurrence_lines;  
	    loc::iterator liter = ploc->begin(), liter_end = ploc->end();

            while ( liter != liter_end ) {
		    occurrence_lines.insert(occurrence_lines.end(), (*liter).first);
                    ++liter;
            }

	    register int size = occurrence_lines.size();
	    cout << "\n" << query_text 
		 << " occurs " << size << " times:\n\n";

	    set<short,less<short>,allocator>::iterator it=occurrence_lines.begin();
	    for ( ; it != occurrence_lines.end(); ++it ) {
		  int line = *it;
		  cout << "\t( line " << line 
		       << " ) "       << (*text_file)[line] << endl;
	    }

	    cout << endl;
        }
	while ( ! query_text.empty() );
        cout << "Ok, bye!\n";
}
