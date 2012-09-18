//Programmer: Derek Buchheit
//Instructor: Dr. Xia
//Course: CS236
//Filename: Parser.h

#ifndef PARSER_H
#define PARSER_H

#include "CToken_List.h"

class Parser
{
   public:
      void parse(CToken_List list_input);
      //Precondition: The list of what to parse is passed in
      //Postcondition: The input is checked for syntax errors
      //and is parsed. 
      Parser(); //Constructor
      ~Parser(); //Destructor
   private:
      //These functions make the appropriate parsing 
      void program(); 
      void stmt_list();
      void stmt();
      void assign();
      void ar_expr(int & ae_s_row, int & ae_s_col);
      void term_tail(int tt1_i_row, int tt1_i_col, 
        int & tt1_s_row, int & tt1_s_col);
      void term(int & t_s_row, int & t_s_col);
      void factor_tail(int ft1_i_row, int ft1_i_col, 
        int & ft1_s_row, int & ft1_s_col);
      void factor(int & f_s_row, int & f_s_col);
      void matrix(int & m_s_row, int & m_s_col);
      void row_tail(int rt1_i_row, int rt1_i_col, 
        int & rt1_s_row);
      void row(int & r_s_col);
      void literal_tail(int lt1_i_col, int & lt1_s_col);
      void command();

      void match(enTokens matched_token);
      //Precondition: the matched token is passed in
      //Postcondition: the matched token is placed in a
      //node and placed on the stack
      CToken_List * my_list;
};
#endif
