//   File Name:    CToken.cpp
//   Function:     Define the token class member functions
//   Related Doc:  token.h contains the definition of the class
//   Author:       Franck Xia
//   Creation:     Oct. 10, 2001

#include "CToken.h"
#include <fstream>

CToken::CToken()
{
   sLex = "";
   tokType = U;
}

CToken::CToken( enTokens t, std::string s )
{
   sLex = s;
   tokType = t;
}
     

enTokens CToken::get_token_type() const
{
   return tokType;
}

std::string CToken::get_lex() const
{
   return sLex;
}

ostream & operator<<( ostream & display, CToken token )
{
   static char str_token_type[30][15];
   static char tt[15];
   static int c = 0;
   static std::ifstream token_file( "tokens_file.dat" );

   // the starting value of enTokens type is set to 0 
   while ( c < 30 && token_file >> tt  )
   {
      strcpy( str_token_type[c++], tt );
   } 

   // as a friend method, private data in CToken can be accessed dircetly

   display << "(" << str_token_type[token.tokType] << "," << token.sLex << ")";
   return display;
}
