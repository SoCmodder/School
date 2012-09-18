//  File Name:  scanner.cpp
//  Function:   Define CScanner class
//  Author:     Mark Turner & Derek Buchheit
//  Creation:   Nov. 3, 2003
#include "scanner.h"
#include "signal.h"
#include "Err_Msg.h"
#include "iostream.h"
#include <string>
using std::cout;
using std::endl;


//Needed because they are declared in driver.cpp
extern lexeme_type_t lexeme_type[];
extern const int CTL_CHAR_OFFSET = 32;


CScanner::CScanner()
{
	//Initialize m_IToken
	m_IToken.clear();

	//Set sizes of lexeme and m_strCommand
	lexeme.resize(MAX_LEX_SIZE);
	m_strCommand.resize(MAX_STT_LENGTH);
	next_pos_in_cmd=0;
	no_char_in_cmd=0;
}

void CScanner::generate_token_list( std::string program )
{
	// initailized token list
	m_IToken.clear();

	next_char_type = BLANK;
	next_pos_in_cmd = 0;
	no_char_in_cmd = program.length();
	m_strCommand = program;

	while((no_char_in_cmd-1)>=next_pos_in_cmd)
	{
		//  start a new lexeme
		lex_type = U; //undetermined lex type
		next_pos_in_lex = 0;//start at the beginning
		lexeme.resize(MAX_LEX_SIZE); //start the new lexeme at full size

		// Use lex to get the next lexeme
		lex();
		lexeme.resize(next_pos_in_lex); //get rid of all extra space
		m_IToken.insert( lex_type, lexeme );
	}

	if((next_pos_in_cmd==no_char_in_cmd)/*&&(ENDCODE!=next_char_type)*/)
	{
		m_IToken.insert(SCANEOF,"$"); //add a $ to the end
	}
}

CToken_List CScanner::get_token_list() const
{
	return (m_IToken);
}

void CScanner::get_char_set_type()
{
	if((no_char_in_cmd-1)>=next_pos_in_cmd)
	{
		// increment to next character
		next_char = m_strCommand[next_pos_in_cmd++];

		if(next_char>='0'&&next_char<='9')
			next_char_type = DIGIT;
		else if(next_char=='.')
			next_char_type = DOT;
		else if((next_char>='a'&&next_char<='z')||(next_char>='A'&&next_char<='Z'))
			next_char_type = LETTER;
		else if(next_char=='_')
			next_char_type = UNDERSCORE;
		else if( next_char == ' ' )
			next_char_type = BLANK;
		else if( next_char == '$' )
			next_char_type = ENDCODE;
		//else if(next_char == '\n')
		//	next_char_type = ENDLINE;
		else
			next_char_type = GENERAL;
   }
   else
   {
		throw CSignal("End of command");
	}

}

void CScanner::add_char()
{
	lexeme[next_pos_in_lex++] = next_char;
	//Adds the terminating character
	lexeme[next_pos_in_lex] = '\0';
}

void CScanner::lex()
{
	lexeme[0]='\0';
	next_pos_in_lex=0;
	int decimal=0;     //Tracks how many decimal points are in a float number
	//Move ahead of any whitespace
	while(next_char_type==BLANK )
	{
		get_char_set_type();
	}

	switch(next_char_type)
	{
		case LETTER: //This character is a letter
		add_char();
		if((no_char_in_cmd-1)>=next_pos_in_cmd) //If there is more in string
		{
			get_char_set_type();
			while((next_char_type==LETTER||next_char_type == DIGIT||next_char_type==UNDERSCORE)
			     &&((no_char_in_cmd-1)>=next_pos_in_cmd))
			{
				add_char();
				get_char_set_type();
			}
		}
		lookup();
		break;

		case ENDCODE:
		add_char();
		lex_type = SCANEOF;
		if((no_char_in_cmd-1)>=next_pos_in_cmd)
		{
			get_char_set_type();
		}
		break;

		case DIGIT: //This character is a digit
		add_char();
		if((no_char_in_cmd-1)>=next_pos_in_cmd)
		{
			get_char_set_type();
			//While there is more in the string, and the next character is a digit or decimal point
			while(((no_char_in_cmd-1)>=next_pos_in_cmd)&&(next_char_type==DIGIT||next_char_type==DOT))
			{
				if(next_char_type==DOT)
				{
					if(decimal==0)
						decimal=1;
					else    //More than one decimal point
						throw CSignal("Too many decimals.");
				}
				add_char();
				get_char_set_type();
			}
		}
		lex_type = FLOATLIT;
		break;

		default:
		add_char();
		lex_type = lexeme_type[(int)next_char-CTL_CHAR_OFFSET].lex_type;
		if((no_char_in_cmd-1)>=next_pos_in_cmd )
			get_char_set_type();
	}
}

//Since the keywords are not IDs we must look up what lex type they are in order to get the correct end result
void CScanner::lookup()
{
	if(!strcmp("if",lexeme.c_str()))//if it is an if key word
	{
		lex_type=IF;//set the lex type to IF
	}
	else if(!strcmp("then",lexeme.c_str()))
	{
		lex_type = THEN;
	}
	else if(!strcmp("else",lexeme.c_str()))
	{
		lex_type = ELSE;
	}
	else if(!strcmp("fi",lexeme.c_str()))
	{
		lex_type = FI;
	}
	else //otherwise it is an ID
		lex_type = ID; //set the lex type to ID
}
