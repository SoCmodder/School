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
   node_stack = NULL;
}

Parser::~Parser()
{
}

void Parser::parse(CToken_List my_list) 
{
   prod_type prod;
   my_list.set_at_start();
   enTokens temp;
   CToken curr_token;

   push(p_eof);
   push(p_program);
   bool another = true;

   while(node_stack && another)
   {
      //Check to see if its the end of the list
      if(my_list.is_end_of_list() == true) 
      {
         cout <<"end of production\n";
         another = false;
      }
      else
      {
         curr_token = my_list.get_current_token();
      }
      if(node_stack->prod == p_eof)
      {
         cout << "end of production\n";
         another = false;
      }
      else if(node_stack->terminal == true) 
      {
         temp = node_stack->token;
         if(temp == curr_token.get_token_type()) 
         {
            pop();
            my_list.moveahead();
         } 
         else 
         {
            throw CSignal("Parsing Error\n");
         }
      } 
      else if(another)
      {
         prod = pop();
         switch(prod)
         {
         case p_program:
            program(curr_token);
            break;
         case p_stmt_list:
            stmt_list(curr_token);
            break;
         case p_stmt:
            stmt(curr_token);
            break;
         case p_assign:
            assign(curr_token);
            break;
         case p_ar_expr:
            ar_expr(curr_token);
            break;
         case p_term_tail:
            term_tail(curr_token);
            break;
         case p_term:
            term(curr_token);
            break;
         case p_factor_tail:
            factor_tail(curr_token);
            break;
         case p_factor:
            factor(curr_token);
            break;
         case p_matrix:
            matrix(curr_token);
            break;
         case p_row_tail:
            row_tail(curr_token);
            break;
         case p_row:
            row(curr_token);
            break;
         case p_literal_tail:
            literal_tail(curr_token);
            break;
         case p_command:
            command(curr_token);
            break;
         default:
            throw CSignal("no production rule found\n");
            break;
         }
      }
   }
}

void Parser::program(CToken &curr_token) 
{
   cout << "program\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID || temp == QUIT || temp == CLEAR || temp == WHO
      || temp == SCANEOF)
   {
      push(p_stmt_list);
   }
   else
   {
      throw CSignal("Parse Error in program parsing function\n");
   }
}

void Parser::stmt_list(CToken & curr_token) 
{
   cout << "stmt_list\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID)
   {
      push(p_stmt_list);
      match(SEMICOL);
      push(p_stmt); 
   }
   else if(temp == QUIT || temp == CLEAR || temp == WHO)
   {
      push(p_stmt);
   }
   else if(temp == SCANEOF)
   {
   }
   else
   {
      throw CSignal("Parse Error in stmt_list parsing function\n");
   }
}

void Parser::stmt(CToken & curr_token)
{
   cout << "stmt\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID)
   {
      push(p_assign);
   }
   else if(temp == QUIT || temp == CLEAR || temp == WHO)
   {
      push(p_command);
   }
   else if(temp == SCANEOF)
   {
   }
   else
   {
      throw CSignal("Parse Error in stmt parsing function\n");
   }
}

void Parser::assign(CToken & curr_token) 
{
   cout << "assign\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID)
   {
      push(p_ar_expr);
      match(ASSIGNOP);
      match(ID);
   }
   else
   {
      throw CSignal("Parse Error in ar_expr parsing function\n");
   }
}

void Parser::ar_expr(CToken & curr_token) 
{
   cout << "ar_expr\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID || temp == FLOATLIT || temp == LPAREN 
     || temp == LBRACK)
   {
      push(p_term_tail);
      push(p_term);
   }
   else
   {
      throw CSignal("Parse Error in ar_expr parsing function\n");
   }
}

void Parser::term_tail(CToken & curr_token) 
{
   cout << "term_tail\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ADDOP || temp == SUBOP)
   {
      push(p_term_tail);
      push(p_term);
      match(temp);
   }
   else if(temp == RPAREN || temp == SEMICOL)
   {
   }
   else
   {
      throw CSignal("Parse Error in term_tail parsing function\n");
   }
}

void Parser::term(CToken & curr_token) 
{
   cout << "term\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID || temp == FLOATLIT || temp == LPAREN 
    || temp == LBRACK)
   {
      push(p_factor_tail);
      push(p_factor);
   }
   else
   {
      throw CSignal("Parse Error in term parsing function\n");
   }
}

void Parser::factor_tail(CToken & curr_token) 
{
   cout << "factor_tail\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ADDOP || temp == SUBOP || temp == RPAREN 
    || temp == SEMICOL)
   {
   }
   else if(temp == MULTOP)
   {
      push(p_factor_tail);
      push(p_factor);
      match(MULTOP);
   }
   else
   {
      throw CSignal("Parse Error in factor tail parsing function\n");
   }
}

void Parser::factor(CToken & curr_token) 
{
   cout << "factor\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == ID)
   {
      match(ID);
   }
   else if(temp == FLOATLIT)
   {
      match(FLOATLIT);
   }
   else if(temp == LPAREN)
   {
      match(RPAREN);
      push(p_ar_expr);
      match(LPAREN);
   }
   else if(temp == LBRACK)
   {
      push(p_matrix);
   }
   else
   {
      throw CSignal("Parse Error in factor tail parsing function\n");
   }
}

void Parser::matrix(CToken & curr_token) 
{
   cout << "matrix\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == LBRACK)
   {
      match(RBRACK);
      push(p_row_tail);
      push(p_row);
      match(LBRACK);
   }
   else
   {
      throw CSignal("Parse Error in matrix parsing function\n");
   }
}

void Parser::row_tail(CToken & curr_token) 
{
   cout << "row_tail\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == RBRACK)
   {
   }
   else if(temp == SEMICOL)
   {
      push(p_row_tail);
      push(p_row);
      match(SEMICOL);
   }
   else
   {
      throw CSignal("Parse Error in matrix parsing function\n");
   }
}

void Parser::row(CToken & curr_token) 
{
   cout << "row\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == FLOATLIT)
   {
      push(p_literal_tail);
      match(FLOATLIT);
   }
   else
   {
      throw CSignal("Parse Error in row parsing function\n");
   }
}

void Parser::literal_tail(CToken & curr_token) 
{
   cout << "literal_tail\n";
   enTokens temp;
   temp = curr_token.get_token_type();
   if(temp == RBRACK || temp == SEMICOL)
   {
   }
   else if(temp == COMMA)
   {
      push(p_literal_tail);
      match(FLOATLIT);
      match(COMMA);
   } 
   else
   {
      throw CSignal("Parse Error in literal tail parsing function\n");
   }
}

void Parser::command(CToken & curr_token) 
{
   cout << "command\n";
   enTokens temp;
   temp = curr_token.get_token_type();
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
   node * my_node;
   my_node = new node;
   my_node->token = matched_token;
   my_node->terminal = true;
   my_node->next_node_ptr = node_stack;
   node_stack = my_node;
}

void Parser::push(prod_type production) 
{
   node *my_node;
   my_node = new node;
   my_node->prod = production;
   my_node->terminal = false;
   my_node->next_node_ptr = node_stack;
   node_stack = my_node;
}

Parser::prod_type Parser::pop() 
{
   prod_type production;
   node * node_ptr;
   production = node_stack->prod;
   node_ptr = node_stack->next_node_ptr;
   delete node_stack;
   node_stack = node_ptr;
   return production;
}


