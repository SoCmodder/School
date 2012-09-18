//   File Name: enTokens.h
//   Function:  Define the enumeration types for tokens
//              and struct for single character lexeme with token type
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001
//    Change:   Oct. 10, 2003
//      add token types for keywords: IF, THEN, ELSE, and FI

#ifndef EN_TOKENS_H
#define EN_TOKENS_H


enum enTokens
{
   ADDOP = 0,
   MULTOP,
   SUBOP,
   DIVOP,
   ASSIGNOP,
   FLOATLIT,
   ID,
   LPAREN,
   RPAREN,
   LBRACK,
   RBRACK,
   PERIOD,
   SEMICOL,
   COMMA,
   LESS,
   EQUAL,
   GREAT,
   QUEST,
   QUIT,
   CLEAR,
   WHO,
   SCANEOF,
   IF,        // added
   THEN,      // added
   ELSE,      // added
   FI,        // added
   U
};

// type for record with single chracter lexeme and its token type

typedef struct
{
   char     lexeme;
   enTokens lex_type;
}  lexeme_type_t;


#endif
