#include <map>
#include <vector>
#include <iostream.h>
#include <string>

/*
Here is our transformation map: 

key: 'em         value: them
key: cuz         value: because
key: gratz       value: grateful
key: nah         value: no
key: pos         value: suppose
key: sez         value: says
key: tanx        value: thanks
key: wuz         value: was


Here is our original string vector:

nah I sez tanx cuz I wuz pos
to not cuz I wuz gratz 


Here is our transformed string vector:

no I says thanks because I was suppose
to not because I was grateful 


Finally, here are our statistics:

cuz was transformed 2 times
gratz was transformed 1 time
nah was transformed 1 time
pos was transformed 1 time
sez was transformed 1 time
tanx was transformed 1 time
wuz was transformed 2 times
*/

int main()
{
    map<string,string,less<string>,allocator> trans_map;
    typedef map<string,string,less<string>,allocator>::value_type valType;

    // a first expedient: hand-code the transformation map
    trans_map.insert( valType( "gratz", "grateful" ));
    trans_map.insert( valType( "'em",   "them"     ));
    trans_map.insert( valType( "cuz",   "because"  ));
    trans_map.insert( valType( "nah",   "no"       ));
    trans_map.insert( valType( "sez",   "says"     ));
    trans_map.insert( valType( "tanx",  "thanks"   ));
    trans_map.insert( valType( "wuz",   "was"      ));
    trans_map.insert( valType( "pos",   "suppose"  ));

    // ok: let's display it
    map<string,string,less<string>,allocator>::iterator it;

    cout << "Here is our transformation map: \n\n";
    for ( it = trans_map.begin(); it != trans_map.end(); ++it )
          cout << "key: "  << (*it).first   << "\t "
               << "value: " << (*it).second << "\n";
    cout << "\n\n";

    // a second expedient: hand-code the text ...
    string textarray[14]={ "nah", "I", "sez", "tanx", "cuz", "I", 
    	"wuz", "pos", "to", "not", "cuz", "I", "wuz", "gratz" };

    vector< string, allocator > text( textarray, textarray+14 );
    vector<string,allocator>::iterator iter;

    // ok: let's display it
    cout << "Here is our original string vector:\n\n";
    int cnt = 1;
    for ( iter = text.begin(); iter != text.end(); ++iter, ++cnt ) 
          cout <<  *iter << ( cnt % 8 ? " " : "\n" );

    cout << "\n\n\n";

    // a map to hold statistics -- build up dynamically
    map<string,int,less<string>,allocator> stats;
    typedef map<string,int,less<string>,allocator>::value_type statsValType;

    // ok: the actual mapwork -- heart of the program
    for ( iter = text.begin(); iter != text.end(); ++iter ) 
          if (( it = trans_map.find( *iter )) != trans_map.end() )
	  {
                if ( stats.count( *iter )) 
                     stats[ *iter ] += 1;
                else stats.insert( statsValType( *iter, 1 ));
                *iter = (*it).second;
          }

    // ok: display the transformed vector 
    cout << "Here is our transformed string vector:\n\n";
    cnt = 1;
    for (iter = text.begin(); iter != text.end(); ++iter, ++cnt ) 
           cout <<  *iter << ( cnt % 8 ? " " : "\n" );
    cout << "\n\n\n";

    // ok: now iterate over the statistics map 
    cout << "Finally, here are our statistics:\n\n";
    map<string,int,less<string>,allocator>::iterator siter;

    for ( siter = stats.begin(); siter != stats.end(); ++siter )
          cout << (*siter).first     << " "
               << "was transformed " 
               << (*siter).second    
               << ((*siter).second == 1 ? " time\n" : " times\n" );
}


