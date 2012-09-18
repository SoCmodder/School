//********************************************************
//                                                       *
//  Instructor: Franck Xia                               *
//  Class:      CS236 Fall 2001                          *
//  Assignment: Program 6                                *
//  Programmer: It's you                                 *
//  File name:  driver.cpp                               *
//  Function:   driver program testing the parser        *
//                                                       *
//********************************************************                 

#define SUCCESSFUL 0

#include <iostream.h>
#include <list>
#include <string>
#include <fstream>

#include "Err_Msg.h"
#include "scanner.h"
#include "parser.h"


// The following part declare an array of record to keep a single character 
//   lexeme and the type of lexeme useful for the parser

const int CTL_CHAR_OFFSET = 32;

lexeme_type_t  lexeme_type[] =
{
 // the first field of each record is a chacater, the second one its enTokens code
 // all the characters appear in the ascii code value ascedent order.
 // as the first 32 ascii chacaters are controlled characters, they are not
 // included. to access an appropriate record of a character, we can use the ascii
 // value of the character - 32 as the index to this array. 
   { ' ', U },{'!',U},{'"',U},{'#',U},
   { '$', SCANEOF },{'%',U},{'&',U},{ '\'',U},
   { '(', LPAREN },
   { ')', RPAREN },
   { '*', MULTOP },
   { '+', ADDOP },
   { ',', COMMA },
   { '-', SUBOP },{'.',U},
   { '/', DIVOP },
   { '0', U }, {'1',U}, {'2',U}, {'3',U}, {'4',U},
   { '5', U }, {'6',U}, {'7',U}, {'8',U}, {'9',U}, 
   { ':', U },
   { ';', SEMICOL },
   { '<', LESS },
   { '=', ASSIGNOP  },
   { '>', GREAT },{'?',U},{'@',U },
   { 'A', U },{'B',U},{'C',U},{'D',U},{'E',U},{'F',U},{'G',U},
   { 'H',U},{'I',U},{'J',U},{'K',U},{'L',U},{'M',U},{'N',U},
   { 'O',U},{'P',U},{'Q',U},{'R',U},{'S',U},{'T',U},{'U',U},
   { 'V',U},{'W',U},{'X',U},{'Y',U},{'Z',U},
   { '[', LBRACK },{'\\',U},
   { ']', RBRACK },{'^',U},{'_',U},{'`',U},
   { 'a', U },{'b',U},{'c',U},{'d',U},{'e',U},{'f',U},{'g',U},
   { 'h', U },{'i',U},{'j',U},{'k',U},{'l',U},{'m',U},{'n',U},
   { 'o', U },{'p',U},{'q',U},{'r',U},{'s',U},{'t',U},{'u',U},
   { 'v', U },{'w',U},{'x',U},{'y',U},{'z',U},
   { '{', U },{'|',U},{'}',U},{'~',U}
};

int main() {

    std::list<std::string>  program_list;
    std::list<std::string>::const_iterator itrTest;
    CScanner                scanner;
    Parser		    parsing;
    
    program_list.push_back(std::string("a=b+3.14156 - 7.8182;$"));
    program_list.push_back(std::string("a=c*b-d;$"));
    program_list.push_back(std::string("a=c+b$"));
    program_list.push_back(std::string("if (a>6) then a=c*(b-d); else b=10; fi;$"));
    program_list.push_back(std::string("a=c+b*d;$"));
    program_list.push_back(std::string("a=(c+b)*d;$ "));
    program_list.push_back(std::string("if (a>6) then a=c*(b-d); fi;$"));
    program_list.push_back(std::string("if (a>6) then if (b < a) then a=c*(b-d); else b=10; fi;$"));
    program_list.push_back(std::string("if (a>6) then if (b < a) then a=c*(b-d); fi; else b=10; fi;$"));
    program_list.push_back(std::string("a=(c+b)*d;$"));
    program_list.push_back(std::string("if (a>6) then if (b < a) then a=c*(b-d); else b=10; fi; else c=b*2; fi;$"));
    program_list.push_back(std::string("a=(c+b)*d ; b=a-e*t;$"));
    program_list.push_back(std::string("a=1+b$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6];$"));
    
    program_list.push_back(std::string("b =[1.0e-1,4.2e-1;1.0e+2,1.0e-0];$"));
    program_list.push_back(std::string("y=[1,2,3];$"));  
    program_list.push_back(std::string("x1=[1;2;3;4];$"));
    program_list.push_back(std::string("1=[1;2;3;4];$"));
    program_list.push_back(std::string("h=]1;2;3;4];$"));
    program_list.push_back(std::string("h=[1,2;3,4]+[4,3;2,1];$"));
    program_list.push_back(std::string("h=[1,2;3,4]-[6,5,4;3,2,1];$"));
    program_list.push_back(std::string("h=[1,2;3,4]*[6,5,4;3,2,1];$"));
    program_list.push_back(std::string("o=[1;2;3;4]; $"));
    program_list.push_back(std::string("z=[1,2,3,4,5,6,7,8;1,2,3,4,5,6,7,8];$"));  
    program_list.push_back(std::string("t=[1,2,Abc;3,4,5];$"));
    program_list.push_back(std::string("xy=[1,2,3;1,2];$"));
    program_list.push_back(std::string("d=[];$"));
    program_list.push_back(std::string("e=[1.e2,.2];$"));
    program_list.push_back(std::string("=$[2.0]"));
    program_list.push_back(std::string("z=[1,,2];$"));
    program_list.push_back(std::string("u=[1;;2];$"));
    
    itrTest = program_list.begin();
    while(itrTest != program_list.end())
    {
       try
       { 
          cout << *itrTest << endl;
          scanner.generate_token_list(*itrTest);

       // now scanner should contain a list of lexemes ready for parsing
       
	  parsing.parse(scanner.get_token_list());
	  cout << "\nA New Program\n\n";
       }
       catch (CSignal e)
       {
	   cout << e.get_message() << endl;  // Get the message
       }
       itrTest++;
     }
    
    return (SUCCESSFUL);
}
