//   File Name: CToken.h
//   Function:  Define the token class
//   Interface: The class has only two public interface methods
//               1. get_lex() returns the lexeme
//               2. get_token_type() returns the token type of the lexeme
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#include <iostream>
#include <string>
#include "enTokens.h"
using std::ostream;

class CToken
{
   public:
      CToken();
      CToken( enTokens, std::string );   
      enTokens  get_token_type() const;
      std::string get_lex() const;
      
   private:
      std::string sLex;
      enTokens   tokType;
      friend ostream & operator<<( ostream & os, CToken t );
};
