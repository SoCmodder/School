// Assignment 8
// Erin Pringle and Joe Wingbermuehle
// This is the header for a set of functions to convert infix
// expression to postfix expression and solve them

#ifndef EVALUATE_H
#define EVALUATE_H

// Max chars in an expression. This should be the same as max chars
// for the edit boxes.
const int MAX_LENGTH=1024;

// struct for operator precedence lookup
struct Operator {
	char name;
	int precedence;
};

const Operator OPS[]={
	{'+',3},
	{'-',3},
	{'*',2},
	{'/',2},
	{'^',1},
	0
};

// struct for looking up valid parens
struct Parenthesis {
	char left;
	char right;
};

const Parenthesis PARENS[]={
	{'(',')'},
	{'[',']'},
	{'{','}'},
	0
};

// Convert an infix expression to postfix
// PRE: expr is the infix expression to convert
//      output is a string for the output
// POST: output is the postfix expression, returns 1 on
//       success or 0 on error
bool SolveInfix(const char *input,char* output);

// Solve a postfix expression
// PRE: expr is the postfix expression to solve
// POST: answer is the answer, returns 1 if
//       successful, otherwise returns 0
bool SolvePostfix(const char* expr,double &answer);

// Check if a character is a valid operator
// PRE: ch is the character to check
//      OPS is a valid (0 terminated) Operator structure
// POST: returns the precedence if the char is valid,
//       otherwise returns 0
int isOperator(char ch);

// Check if a character is a valid numeral
// PRE: ch is the character to check
// POST: returns 1 if valid, otherwise returns 0
bool isNumber(char ch);

// Check if a character is a left paren
// PRE: ch is the character to check
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns 1 if a left paren, otherwise returns 0
bool isLeftParen(char ch);

// Check if a character is a right paren
// PRE: ch is the character to check
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns 1 if a right paren, otherwise returns 0
bool isRightParen(char ch);

// Get the right equivalent of a given left paren
// PRE: left is a valid left paren
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns the right equivalent (if possible)
char getRightParen(char left);

// Check if the parenthesis in an expression are balanced
// PRE: str points to the expression to check
// POST: returns 1 if balanced, otherwise returns 0
bool CheckParens(const char* str);

// Insert zeros and parens into the expression to elimiate unary '-'
// PRE: expr is the expression to which to add parens and zeros
//      MAX_LENGTH is the max size of the expression
// POST: expr is the result. Note: this function is recursive
void InsertZeros(char *expr);

#endif