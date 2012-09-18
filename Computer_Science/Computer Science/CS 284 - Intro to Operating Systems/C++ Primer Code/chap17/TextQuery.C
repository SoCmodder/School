#include "TextQuery.h"

string TextQuery::filt_elems( "\",.;:!?)(\\/" );

void
TextQuery::
// display_solution( ostream &os )
display_solution()
{
	cout << "\n"
	     << "Requested query: "
	     << *query << "\n\n";

	const set<short,less<short>,allocator> *solution = query->solution();
	
	if ( ! solution->size() ) {
	     cout << "\n\t" 
		  << "Sorry, no matching lines were found in text.\n"
		  << endl;
	}

	set<short,less<short>,allocator>::const_iterator 
		it = solution->begin(),
		end_it = solution->end();

	for ( ; it != end_it; ++it ) {
		int line = *it;
		// don't confound user with text lines starting at 0 ...
		cout << "( " << line+1 << " ) "
		     << (*lines_of_text)[line] << '\n';
	}

	cout << endl;
}

void
TextQuery::
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

	lines_of_text = new vector<string,allocator>;
	string textline;

	while ( getline( infile, textline, '\n' ))
		  lines_of_text->push_back( textline );
}

void
TextQuery::
separate_words()
{
	vector<string,allocator>   *words     = new vector<string,allocator>;
	vector<location,allocator> *locations = new vector<location,allocator>;

        for ( short line_pos = 0; line_pos < lines_of_text->size(); line_pos++ )
        {
		short  word_pos = 0;
                string textline = (*lines_of_text)[ line_pos ];

                string::size_type eol = textline.length();
                string::size_type pos = 0, prev_pos = 0;

                while (( pos = textline.find_first_of( ' ', pos )) 
                            != string::npos )
                {
                        words->push_back( 
                               textline.substr( prev_pos, pos - prev_pos ));
                        locations->push_back( make_pair( line_pos, word_pos ));

                        word_pos++; pos++; prev_pos = pos;
                }

                words->push_back( textline.substr( prev_pos, pos - prev_pos ));
                locations->push_back( make_pair( line_pos, word_pos ));

                // record size of each line
                line_cnt.push_back( word_pos );
        }
	
        text_locations = new text_loc( words, locations );
}

void 
TextQuery::
filter_text()
{
	if ( filt_elems.empty() )
	     return;

	vector<string,allocator> *words = text_locations->first;

	vector<string,allocator>::iterator iter = words->begin();
	vector<string,allocator>::iterator iter_end = words->end();

	while ( iter != iter_end )
	{
                string::size_type pos = 0;
                while (( pos = (*iter).find_first_of( filt_elems, pos )) 
                            != string::npos )
                       (*iter).erase(pos,1);
		iter++;
	}
}

void
TextQuery::
suffix_text()
{
        vector<string,allocator> *words = text_locations->first;

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
TextQuery::
suffix_s( string &word )
{
        string::size_type spos = 0;
        string::size_type pos3 = word.size()-3;

        // "ous", "ss", "is", "ius"
        string suffixes( "oussisius" );

        if ( ! word.compare( pos3, 3, suffixes, spos, 3 ) ||
             ! word.compare( pos3, 3, suffixes, spos+6, 3 ) ||
             ! word.compare( pos3+1, 2, suffixes, spos+2, 2 ) ||
             ! word.compare( pos3+1, 2, suffixes, spos+4, 2 ))
                return;

        string ies( "ies" );
        if ( ! word.compare( pos3, 3, ies ))
        {
             word.replace( pos3, 3, 1, 'y' );
             return;
        }

        string ses( "ses" );
        if ( ! word.compare( pos3, 3, ses ))
        {
             word.erase( pos3+1, 2 );
             return;
        }

        // erase ending 's'
        word.erase( pos3+2 );

        // watch out for "'s"
        if ( word[ pos3+1 ] == '\'' )
             word.erase( pos3+1 );
}

void
TextQuery::
strip_caps()
{
        vector<string,allocator> *words = text_locations->first;

        vector<string,allocator>::iterator iter = words->begin();
        vector<string,allocator>::iterator iter_end = words->end();

        string caps( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

        while ( iter != iter_end ) {
                string::size_type pos = 0;
                while (( pos = (*iter).find_first_of( caps, pos )) 
                            != string::npos )
                       (*iter)[ pos ] = tolower( (*iter)[pos] );
                ++iter;
        }
}


void
TextQuery::
build_word_map()
{
     word_map = new map< string, loc*, less<string>, allocator >;

     typedef map<string,loc*,less<string>,allocator>::value_type value_type;
     typedef set<string,less<string>,allocator>::difference_type diff_type;

     set<string,less<string>,allocator> exclusion_set;

     ifstream infile( "exclusion_set" );
     if ( !infile )
     {
          static string default_excluded_words[25] = {
            "the","and","but","that","then","are","been",
            "can","can't","cannot","could","did","for",
            "had","have","him","his","her","its","into",
            "were","which","when","with","would"
          };

          cerr << "warning! unable to open word exclusion file! -- "
               << "using default set\n";

          copy( default_excluded_words, default_excluded_words+25, 
                inserter( exclusion_set, exclusion_set.begin() ));
     }
     else {
          istream_iterator< string, diff_type > input_set( infile ), eos;
          copy( input_set, eos, 
                inserter( exclusion_set, exclusion_set.begin() ));
     }

     // iterate through the the words, entering the key/pair

     vector<string,allocator>   *text_words = text_locations->first;
     vector<location,allocator> *text_locs  = text_locations->second;

     register int elem_cnt = text_words->size();
     for ( int ix = 0; ix < elem_cnt; ++ix )
         {
                string textword = ( *text_words )[ ix ];

                // exclusion strategies
                // less than 3 character or in exclusion set
                if ( textword.size() < 3 ||
                     exclusion_set.count( textword ))
                        continue;

                if ( ! word_map->count((*text_words)[ix] ))
                {  // not present, add it:
                   loc *ploc = new vector<location,allocator>;
                   ploc->push_back( (*text_locs)[ix] );
                   word_map->insert( value_type( (*text_words)[ix], ploc ));
                }
                else (*word_map)[(*text_words)[ix]]->push_back( (*text_locs)[ix] );
         }
}

void 
TextQuery::
query_text() 
{
	string text;
	string caps( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

	vector<string, allocator> query_text;

	UserQuery user_query;
 	init_query_statics();
    
	do {
		query_text.clear();

 	cout << "Enter a query -- please separate each item "
			<< "by a space.\n"
		<< "Terminate query (or session) with a dot( . ).\n\n"
			<< "==> ";
	   
	   	while( cin  >> text ) 
   		{ 
		     if ( text == "." )
		          break;

		     // remove all capitalization ...
 		     string::size_type pos = 0;
     while (( pos = text.find_first_of( caps, pos )) 
				     != string::npos )
                          text[pos] = tolower( text[pos] );

		     query_text.push_back( text );
	   	}

	   	if ( ! query_text.empty() ) 
		{
	   		user_query.query( &query_text );
	   		query = user_query.eval();
	   		query->eval();
	   		display_solution();
	    		cout << endl;
		}
        }
	while ( ! query_text.empty() );
        cout << "Ok, bye!\n";
}

void
TextQuery::
display_map_text()
{
        typedef map<string,loc*,less<string>,allocator> map_text;
        map_text::iterator iter = word_map->begin(), iter_end = word_map->end();

        while ( iter != iter_end ) {
                cerr << "word: " << (*iter).first << " (";

                int           loc_cnt = 0;
                loc          *text_locs = (*iter).second;
                loc::iterator liter     = text_locs->begin(),
                              liter_end = text_locs->end();

                while ( liter != liter_end )
                {
                        if ( loc_cnt )
                             cerr << ",";
                        else ++loc_cnt;

                        cerr << "(" << (*liter).first
                             << "," << (*liter).second << ")";

                        ++liter;
                }

                cerr << ")\n";
                ++iter;
        }

        cerr << endl;
}

void
TextQuery::
display_text_locations()
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

/*
sample input text:
------------------

Alice Emma has long flowing red hair. Her Daddy says
when the wind blows through her hair, it looks almost alive,
like a fiery bird in flight. A beautiful fiery bird, he tells her,
magical but untamed. "Daddy, shush, there is no such thing,"
she tells him, at the same time wanting him to tell her more.
Shyly, she asks, "I mean, Daddy, is there?"

---------------------
sample query session:
---------------------

please enter file name: alice_emma

warning! unable to open word exclusion file! -- using default set

enter a word against which to search the text.
to quit, enter a single character ==>  alice

alice occurs 1 time:

        ( line 1 ) Alice Emma has long flowing red hair. Her Daddy says

enter a word against which to search the text.
to quit, enter a single character ==>  daddy

daddy occurs 3 times:

        ( line 1 ) Alice Emma has long flowing red hair. Her Daddy says
        ( line 4 ) magical but untamed. "Daddy, shush, there is no such thing,"
        ( line 6 ) Shyly, she asks, "I mean, Daddy, is there?"

enter a word against which to search the text.
to quit, enter a single character ==>  phoenix

Sorry. There are no entries for phoenix.

enter a word against which to search the text.
to quit, enter a single character ==>  .
Ok, bye!

----------------------------------------------------------
sample text map after: (a) stripping out punctuation,
(b) eliminating semantically neutral words such as `the`,
(c) suffixing, so that fixes and fix become fix, and
(d) removal of capitalization
-----------------------------------------------------------

word: alice ((0,0))
word: alive ((1,10))
word: almost ((1,9))
word: ask ((5,2))
word: beautiful ((2,7))
word: bird ((2,3),(2,9))
word: blow ((1,3))
word: daddy ((0,8),(3,3),(5,5))
word: emma ((0,1))
word: fiery ((2,2),(2,8))
word: flight ((2,5))
word: flowing ((0,4))
word: hair ((0,6),(1,6))
word: has ((0,2))
word: like ((2,0))
word: long ((0,3))
word: look ((1,8))
word: magical ((3,0))
word: mean ((5,4))
word: more ((4,12))
word: red ((0,5))
word: same ((4,5))
word: say ((0,9))
word: she ((4,0),(5,1))
word: shush ((3,4))
word: shyly ((5,0))
word: such ((3,8))
word: tell ((2,11),(4,1),(4,10))
word: there ((3,5),(5,7))
word: thing ((3,9))
word: through ((1,4))
word: time ((4,6))
word: untamed ((3,2))
word: wanting ((4,7))
word: wind ((1,2))

*/
