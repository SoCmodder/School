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

#include "Query.h"
#include "UserQuery.h"

class TextQuery {
public:
	TextQuery() { memset( this, 0, sizeof( TextQuery )); }

	static void filter_elements( string felems ) { filt_elems = felems; }

	void query_text();
	void display_map_text();
	void display_text_locations();
	void build_up_text() {
        	retrieve_text();
        	separate_words();
        	filter_text();
        	suffix_text();
        	strip_caps();
        	build_word_map();
	}

private:
	void retrieve_text();
	void separate_words();
	void filter_text();
	void strip_caps();
	void suffix_text();
	void suffix_s( string& );
	void build_word_map();
	void init_query_statics();
	void display_solution();

private:
	vector<string,allocator>   		    *lines_of_text;
	text_loc                   		    *text_locations;
	map<string,loc*,less<string>,allocator> *word_map;
	Query  					    *query;
	static string				     filt_elems;
	vector<int,allocator>			     line_cnt;
};

inline void
TextQuery::
init_query_statics()
{
	NotQuery::all_locs( text_locations->second );
	AndQuery::max_col( &line_cnt );
	UserQuery::word_map( word_map );
}

