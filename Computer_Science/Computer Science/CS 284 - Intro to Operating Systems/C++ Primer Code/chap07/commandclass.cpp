#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <cstdlib>
using std::exit;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <ctype.h>
#include <assert.h>
 
class CommandOpt {
public:
    CommandOpt() : _limit( -1 ), _debug_on( false ) {}
    int parse_options( int argc, char *argv[] );
 
    string out_file() { return _out_file; }
    bool   debug_on() { return _debug_on; }
    int    files()    { return _file_names.size(); }
 
    string& operator[]( int ix ) {
        assert( ix < _file_names.size() );
        return _file_names[ ix ];
    }
 
private:
    inline void usage( int exit_value = 0 );
 
    bool _debug_on;
    int _limit;
    string _out_file;
    vector<string> _file_names;
 
    static const char *const program_name;
    static const char *const program_version;
};
 
int main( int argc, char* argv[] )
{
    CommandOpt comopt;
    if ( int option_status = comopt.parse_options( argc, argv ))
         return option_status;
 
    if ( ! comopt.out_file().empty() )
           cout << "User-specified output file: "
                << comopt.out_file() << endl;
 
    cout << (comopt.files() == 1 ? "File " : "Files ")
             << "to be processed are the following:\n";
 
    for ( int ix = 0; ix < comopt.files(); ++ix )
          cout << "\t" << comopt[ ix ] << endl;
}
 
const char *const CommandOpt::program_name = "comline_class";
const char *const CommandOpt::program_version = "version 0.01 (08/07/97)";
 
inline void
CommandOpt::
usage( int exit_value )
{
    cerr << "usage:\n"
         << program_name << " "
         << "[-d] [-h] [-v] \n\t"
         << "[-o output_file] [-l limit] \n\t"
         << "file_name\n\t[file_name [file_name [ ... ]]]\n\n"
         << "where [] indicates optional option:\n\n\t"
         << "-h: help.\n\t\tgenerates this message and exits\n\n\t"
         << "-v: version.\n\t\tprints version information and exits\n\n\t"
         << "-d: debug.\n\t\tturns debugging on\n\n\t"
         << "-l limit\n\t\tlimit must be a non-negative integer\n\n\t"
         << "-o ofile\n\t\tfile within which to write out results\n\t\t"
         << "by default, results written to standard output\n\n"
         << "file_name\n\t\tthe name of the actual file to process\n\t\t"
         << "at least one file_name is required --\n\t\t"
         << "any number may be specified\n\n"
         << "examples:\n\t\t"
         << "$command chapter7.doc\n\t\t"
         << "$command -d -l 1024 -o test_7_8 chapter7.doc chapter8.doc\n\n";
 
    exit( exit_value );
}
 
int
CommandOpt::
parse_options( int argc, char* argv[] )
{
        register char *pchar;
 
        bool ofile_on = false;
        bool limit_on = false;
 
        cout << "illustration of handling command line arguments:\n"
             << "argc: " << argc << endl;
 
        for ( int ix = 1; ix < argc; ++ix )
        {
                cout << "argv[ " << ix << " ]: "
                     << argv[ ix ] << endl;
 
                switch ( *( pchar = argv[ ix ] ))
                {
                    case '-':
                    {
                        cout << "case \'-\' found\n";
 
                        while ( *++pchar )
                        {
                                cout << "swith on char following hyphen: "
                                     << *pchar << endl;
 
                                switch( *pchar )
                                {
                                case 'd':
                                        cout << "-d found: debugging turned on\n";
 
                                        _debug_on = true;
                                        break;
 
                                case 'v':
                                        cout << "-v found: version info displayed\n";
 
                                        cout << program_name
                                             << " ::  "
                                             << program_version
                                             << endl;
 
                                        return 1;
 
                                case 'h':
                                        cout << "-h found: help information\n";
 
                                        // no break necessary: usage() exits
                                        usage();
 
                                case 'o':
                                        cout << "-o found: output file\n";
 
                                        ofile_on = true;
                                        break;
 
                                case 'l':
                                        cout << "-l found: resource limit\n";
 
                                        limit_on = true;
                                        break;
 
                                default:
                                        cerr << program_name
                                             << " : error : unrecognized option: "
                                             << pchar << "\n\n";
 
                                        // no break necessary: usage() exits
                                        usage( -1 );
                                }
                        }
                        break;
                    }
 
                    default: // either a file name
                        cout << "default non-hypen argument: "
                             << pchar << endl;
 
                        if ( ofile_on ) {
                             ofile_on = false;
                             _out_file = pchar;
                        }
                        else
                        if ( limit_on ) {
                             limit_on = false;
                             _limit = atoi( pchar );
                             if ( _limit < 0 ) {
                                  cerr << program_name
                                       << " : error : negative value for limit.\n\n";
 
                                  usage( -2 );
                             }
                        }
                        else _file_names.push_back( string( pchar ));
                        break;
                }
        }
 
        if ( _file_names.empty() ) {
             cerr << program_name
                  << " : error : no file specified for processing.\n\n";
 
             usage( -3 );
        }
 
        return 0;
}
 
