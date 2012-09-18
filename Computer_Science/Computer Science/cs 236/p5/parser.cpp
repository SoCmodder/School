//Programmer: Derek Buchheit
//Instructor: Dr. Xia
//Class: CS236
//Filename: parser.cpp

#include "Err_Msg.h"
#include "parser.h"

using std::cout;
using std::endl;

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::parse(CToken_List list_input) 
{
   my_list = &list_input;
   my_list->set_at_start();
   program();
}

void Parser::program() 
{
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID || temp == QUIT || temp == CLEAR || temp == WHO
      || temp == SCANEOF)
   {
      stmt_list();
   }
   else
   {
      throw CSignal("Parse Error in program parsing function\n");
   }
}

void Parser::stmt_list() 
{
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID)
   {
      stmt();
      match(SEMICOL);
      stmt_list(); 
   }
   else if(temp == QUIT || temp == CLEAR || temp == WHO)
   {
      stmt();
   }
   else if(temp == SCANEOF)
   {
   }
   else
   {
      throw CSignal("Parse Error in stmt_list parsing function\n");
   }
}

void Parser::stmt()
{
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID)
   {
      assign();
   }
   else if(temp == QUIT || temp == CLEAR || temp == WHO)
   {
      command();
   }
   else if(temp == SCANEOF)
   {
   }
   else
   {
      throw CSignal("Parse Error in stmt parsing function\n");
   }
}

void Parser::assign() 
{
   int id_s_row, id_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID)
   {
      match(ID);
      match(ASSIGNOP);
      ar_expr(id_s_row, id_s_col);
   }
   else
   {
      throw CSignal("Parse Error in ar_expr parsing function\n");
   }
}

void Parser::ar_expr(int & ae_s_row, int & ae_s_col) 
{
   int t_s_row, t_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID || temp == FLOATLIT || temp == LPAREN 
     || temp == LBRACK)
   {
      term(t_s_row, t_s_col);
      term_tail(t_s_row, t_s_col, ae_s_row, ae_s_col);
   }
   else
   {
      throw CSignal("Parse Error in ar_expr parsing function\n");
   }
}

void Parser::term_tail(int tt1_i_row, int tt1_i_col, 
  int & tt1_s_row, int & tt1_s_col) 
{
   int t_s_row, t_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ADDOP || temp == SUBOP)
   {
      match(temp);
      term(t_s_row, t_s_col);
      if(tt1_i_row == t_s_row && tt1_i_col == t_s_col)
      {
         term_tail(t_s_row, t_s_col, tt1_s_row, tt1_s_col);
      }
      else
      {
         throw CSignal("Wrong number of row or columns for + or -\n");
      } 
   }
   else if(temp == RPAREN || temp == SEMICOL)
   {
      tt1_s_row = tt1_i_row;
      tt1_s_col = tt1_i_col;
   }
   else
   {
      throw CSignal("Parse Error in term_tail parsing function\n");
   }
}

void Parser::term(int & t_s_row, int & t_s_col) 
{
   int f_s_row, f_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID || temp == FLOATLIT || temp == LPAREN 
    || temp == LBRACK)
   {
      factor(f_s_row, f_s_col);
      factor_tail(f_s_row, f_s_col, t_s_row, t_s_col);      
   }
   else
   {
      throw CSignal("Parse Error in term parsing function\n");
   }
}

void Parser::factor_tail(int ft1_i_row, int ft1_i_col, 
  int & ft1_s_col, int & ft1_s_row) 
{
   int f_s_row, f_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ADDOP || temp == SUBOP || temp == RPAREN 
    || temp == SEMICOL)
   {
      ft1_s_row = ft1_i_row;
      ft1_s_col = ft1_i_col;
   }
   else if(temp == MULTOP)
   {
      match(MULTOP);
      factor(f_s_row, f_s_col);
      if(ft1_i_col == f_s_row)
      {
         factor_tail(ft1_i_row, f_s_col, ft1_s_row, ft1_s_col);
      }
      else
      {
         throw CSignal("Wrong number of row or columns for *");
      } 
   }
   else
   {
      throw CSignal("Parse Error in factor tail parsing function\n");
   }
}

void Parser::factor(int & f_s_row, int & f_s_col) 
{
   int m_s_row, m_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == ID)
   {
      match(ID);
   }
   else if(temp == FLOATLIT)
   {
      match(FLOATLIT);
      f_s_row = 1;
      f_s_col = 1;
   }
   else if(temp == LPAREN)
   {
      match(LPAREN);
      ar_expr(f_s_row, f_s_col);
      match(RPAREN);
   }
   else if(temp == LBRACK)
   {
      matrix(m_s_row, m_s_col);
   }
   else
   {
      throw CSignal("Parse Error in factor tail parsing function\n");
   }
}

void Parser::matrix(int & m_s_row, int & m_s_col) 
{
   int rt1_i_row=1;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == LBRACK)
   {
      match(LBRACK);
      row(m_s_col);
      row_tail(rt1_i_row, m_s_col, m_s_row);
      match(RBRACK);
   }
   else
   {
      throw CSignal("Parse Error in matrix parsing function\n");
   }
}

void Parser::row_tail(int rt1_i_row, int rt1_i_col, 
  int & rt1_s_row) 
{
   int r_s_col;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == RBRACK)
   {
      rt1_s_row = rt1_i_row;
   }
   else if(temp == SEMICOL)
   {
      match(SEMICOL);
      row(r_s_col);
      if(r_s_col == rt1_i_col)
      {
         rt1_i_row++;
         row_tail(rt1_i_row, r_s_col, rt1_s_row);
      }
      else 
      {
         throw CSignal("Wrong number of columns\n");
      }
   }
   else
   {
      throw CSignal("Parse Error in matrix parsing function\n");
   }
}

void Parser::row(int & r_s_col) 
{
   int lt1_i_col=1;
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == FLOATLIT)
   {
      match(FLOATLIT);
      literal_tail(lt1_i_col, r_s_col);
   }
   else
   {
      throw CSignal("Parse Error in row parsing function\n");
   }
}

void Parser::literal_tail(int lt1_i_col, int & lt1_s_col) 
{
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == RBRACK || temp == SEMICOL)
   {
      lt1_s_col = lt1_i_col;
   }
   else if(temp == COMMA)
   {
      match(COMMA);
      match(FLOATLIT);
      lt1_i_col++;
      literal_tail(lt1_i_col, lt1_s_col);
   } 
   else
   {
      throw CSignal("Parse Error in literal tail parsing function\n");
   }
}

void Parser::command() 
{
   enTokens temp;
   temp = my_list->get_current_token_type();
   if(temp == QUIT || temp == CLEAR || temp == WHO)
   {
      match(temp);
   }
   else
   {
      throw CSignal("Parse Error in command parsing function\n");
   }
}

void Parser::match(enTokens matched_token) 
{
   if(matched_token == my_list->get_current_token_type())
   {
      my_list->moveahead();
   }
   else
   {
      throw CSignal("Parse Error in matching function\n");
   }
}

