//  File Name:  scanner.h
//  Function:   Define CScanner class
//  Author:     Franck Xia
//  Creation:   Nov. 3, 2001
//  Modified:   Nov. 10, 2002

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "enChar.h"
#include "CToken_List.h"

const int MAX_LEX_SIZE = 30;
const int MAX_STT_LENGTH = 80;

class CScanner
{
   public:
      CScanner();
      void generate_token_list( std::string );
      CToken_List get_token_list() const;

   private:
      std::string m_strCommand;
      CToken_List m_IToken;
      std::string lexeme;
      enTokens lex_type;
      char next_char;
      enChar next_char_type;
      int next_pos_in_lex;
      int next_pos_in_cmd;
      int no_char_in_cmd;

      void get_char_set_type();
      void add_char();
      void lex();
      void lookup();         // determine keyword token types
};

#endif
