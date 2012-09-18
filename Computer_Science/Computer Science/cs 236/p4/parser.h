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
      void parse(CToken_List my_list);
      //Precondition: The list of what to parse is passed in
      //Postcondition: The input is checked for syntax errors
      //and is parsed. 
      Parser(); //Constructor
      ~Parser(); //Destructor
   private:
      //These are the  possible non-terminals that we are parsing
      enum prod_type
      {
         p_program, 
         p_stmt_list,
         p_stmt,
         p_assign,
         p_ar_expr,
         p_term_tail,
         p_term,
         p_factor_tail,
         p_factor,
         p_matrix,
         p_row_tail,
         p_row,
         p_literal_tail,
         p_command,
         p_eof
      };
    
      //These functions make the appropriate parsing 
      void program(CToken&); 
      void stmt_list(CToken&);
      void stmt(CToken&);
      void assign(CToken&);
      void ar_expr(CToken&);
      void term_tail(CToken&);
      void term(CToken&);
      void factor_tail(CToken&);
      void factor(CToken&);
      void matrix(CToken&);
      void row_tail(CToken&);
      void row(CToken&);
      void literal_tail(CToken&);
      void command(CToken&);

      //These nodes are linked in a stack and hold the
      //non-terminals and terminals that we are parsing
      struct node
      {
         enTokens token;
         prod_type prod;
         node * next_node_ptr;
         bool terminal;
      };
      node * node_stack;
    
      void match(enTokens matched_token);
      //Precondition: the matched token is passed in
      //Postcondition: the matched token is placed in a
      //node and placed on the stack
      void push(prod_type production);
      //Precondition: The desired non-terminal is passed in
      //Postcondition: The non-terminal is added to a node
      //and placed on a stack. 
      prod_type pop();
      //Precondition: none
      //Postcondition: The top node is removed from the stack, and
      //is non-terminal type is returned. 
};
#endif
