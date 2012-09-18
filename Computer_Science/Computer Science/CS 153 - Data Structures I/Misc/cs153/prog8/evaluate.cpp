// Assignment 8
// Erin Pringle and Joe Wingbermuehle
// This is the implementation for a set of functions to convert infix
// expression to postfix expression and solve them

#include "stdafx.h"
#include "Stack.h"
#include "evaluate.h"
#include <math.h>

// Check if a character is a valid operator
// PRE: ch is the character to check
//      OPS is a valid (0 terminated) Operator structure
// POST: returns the precedence if the char is valid,
//       otherwise returns 0
int isOperator(char ch) {
	for(int x=0;OPS[x].name;x++) {
		if(OPS[x].name==ch)
			return OPS[x].precedence;
	}
	return 0;
}

// Check if a character is a valid numeral
// PRE: ch is the character to check
// POST: returns 1 if valid, otherwise returns 0
bool isNumber(char ch) {
	if(ch>='0' && ch<='9')
		return 1;
	if(ch=='.')
		return 1;
	return 0;
}

// Check if a character is a left paren
// PRE: ch is the character to check
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns 1 if a left paren, otherwise returns 0
bool isLeftParen(char ch) {
	for(int x=0;PARENS[x].left;x++) {
		if(PARENS[x].left==ch)
			return 1;
	}
	return 0;
}

// Check if a character is a right paren
// PRE: ch is the character to check
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns 1 if a right paren, otherwise returns 0
bool isRightParen(char ch) {
	for(int x=0;PARENS[x].left;x++) {
		if(PARENS[x].right==ch)
			return 1;
	}
	return 0;
}

// Get the right equivalent of a given left paren
// PRE: left is a valid left paren
//      PARENS is a valid (0 terminated) Parenthesis structure
// POST: returns the right equivalent (if possible)
char getRightParen(char left) {
	for(int x=0;PARENS[x].left;x++) {
		if(PARENS[x].left==left)
			return PARENS[x].right;
	}
	return 0;	// Should not happen!
}

// Check if the parenthesis in an expression are balanced
// PRE: str points to the expression to check
// POST: returns 1 if balanced, otherwise returns 0
bool CheckParens(const char* str) {
	CStack stack;		// Stack used for balance checking
	char temp[2];		// String used to push the parens on the stack

	// Loop through pushing lefts and popping/comparing rights
	temp[1]=0;
	for(int x=0;str[x];x++) {
		*temp=str[x];
		if(isLeftParen(*temp)) {
			stack.push(temp);
		} else if(isRightParen(*temp)) {
			if(stack.empty() || getRightParen(stack.pop()[0])!=*temp)
				return 0;
		}
	}

	// If the stack isn't empty, parens aren't balanced
	if(stack.empty())
		return 1;
	else
		return 0;
}

// Insert zeros and parens into the expression to elimiate unary '-'
// PRE: expr is the expression to which to add parens and zeros
//      MAX_LENGTH is the max size of the expression
// POST: expr is the result. Note: this function is recursive
void InsertZeros(char *expr) {
	int x,y;			// Index variables
	bool isQuant=0;		// 1 if last element was a quantity
	bool madeChanges=0;	// 1 if changes were made (and we need to run again)

	// Loop through all the elements
	// Each iteration will make at most one insertion
	// Each insertion is 3 characters, so x must be <MAX_LENGTH+2
	for(x=0;expr[x]&&x<MAX_LENGTH+2;x++) {

		// set isQuant if a quantity
		if(isNumber(expr[x]) || isRightParen(expr[x]))
			isQuant=1;

		// Insert the parens and 0s (ei: '5--4' becomes '5-(0-4)')
		else if(expr[x]=='-' && !isQuant) {
			int length=strlen(expr);		// length of the expression
			int parenCount;					// level of parens

			// Make room for and insert the "(0"
			expr[length+2]=0;
			for(y=length;y>=x;y--) {
				expr[y+2]=expr[y];
			}
			expr[x++]='(';
			expr[x++]='0';

			// Find the end of the quantity
			++x; parenCount=0;
			for(;;) {
				if(isLeftParen(expr[x]))
					++parenCount;
				if(isRightParen(expr[x]))
					--parenCount;
				if(!isNumber(expr[x])&&parenCount<=0)
					break;
				++x;
			}

			// Make room for and insert the ")"
			length=strlen(expr);
			for(y=length;y>=x;y--) {
				expr[y+1]=expr[y];
			}
			expr[x++]=')';


			madeChanges=1;
		} else 
			isQuant=0;
	}

	// If changes were made, some unary -'s might be left
	if(madeChanges) InsertZeros(expr);
}

// Convert an infix expression to postfix
// PRE: expr is the infix expression to convert
//      output is a string for the output
// POST: output is the postfix expression, returns 1 on
//       success or 0 on error
bool SolveInfix(const char *input,char* output) {
	char op[2];					// "string" for the operator stack
	char expr[MAX_LENGTH+1];	// Modifible input string
	int length;					// The current length of the output string [+1]
	CStack opStack;				// Operation stack
	int x;						// Index variable for reading input
	bool foundError;			// 1 if error found, otherwise 0

	// 
	memcpy(expr,input,MAX_LENGTH*sizeof(char));
	InsertZeros(expr);

	// Initialize some variables
	op[1]=0;
	length=0;
	foundError=0;
	output[0]=0;

	// Read each character of the expression
	for(x=0;expr[x];x++) {
		*op=expr[x];

		// If we have a left paren, push it
		if(isLeftParen(*op)) {
			opStack.push(op);

		// If we have a number, push it
		} else if(isNumber(*op)) {
			do {
				output[length++]=expr[x++];
			} while(isNumber(expr[x]));
			output[length++]=' ';
			output[length]=0;
			--x;

		// If we have an operator, pop lower precedence operators and push it
		} else if(isOperator(*op)) {
			while(!opStack.empty()
				&& !isLeftParen(opStack.top()[0])
				&& isOperator(opStack.top()[0])<=isOperator(*op)) {
				if(!isOperator(opStack.top()[0])) foundError=1;
				output[length++]=opStack.pop()[0];
				output[length]=0;
			}
			opStack.push(op);

		// If we have a right paren, pop operators between the parens
		} else if(isRightParen(*op)) {
			for(;;) {
				if(opStack.empty()) break;
				*op=opStack.pop()[0];
				if(!*op || isLeftParen(*op)) break;
				if(!isOperator(*op)) {
					foundError=1;
					break;
				}
				output[length++]=*op;
			}
			output[length]=0;

		// If this happens, we have a syntax error (unless whitespace)
		} else {
			switch(*op) {
			case ' ':
			case '\t':
			case '\n':
				break;
			default:
				foundError=1;
				break;
			}
		}

		// No need to continue if we have errors
		if(foundError) break;
	}

	// Pop any remaining operations off the stack
	while(!opStack.empty()) {
		if(!isOperator(opStack.top()[0])) foundError=1;
		output[length++]=opStack.pop()[0];
		output[length]=0;
	}

	return !foundError;
}

// Solve a postfix expression
// PRE: expr is the postfix expression to solve
// POST: answer is the answer, returns 1 if
//       successful, otherwise returns 0
bool SolvePostfix(const char* expr,double &answer) {
	int x,y;					// Index variables
	double right,left;			// Right and left parts of the value
	char str[MAX_LENGTH+1];		// String for number to string conversion
	char ch;					// Temporary char to hold expr[x] etc
	CStack stack;				// The stack to hold the values

	// Loop through the postfix expression
	for(x=0;x<signed(strlen(expr));x++) {
		ch=expr[x];

		// If we have an operator, set up left/right
		if(isOperator(ch)) {
			right=atof(stack.pop());
			if(stack.empty()) {
				break;
			} else {
				left=atof(stack.pop());
			}
		}

		// Do an operation or push a number
		switch(ch) {
		case '+':
			sprintf(str,"%lf",left+right);
			stack.push(str);
			break;
		case '-':
			sprintf(str,"%lf",left-right);
			stack.push(str);
			break;
		case '*':
			sprintf(str,"%lf",left*right);
			stack.push(str);
			break;
		case '/':
			if(!right)
				break;
			sprintf(str,"%lf",left/right);
			stack.push(str);
			break;
		case '^':
			sprintf(str,"%lf",pow(left,right));
			stack.push(str);
			break;
		case ' ':		// Skip white space and various delimiters
		case ',':
		case '\t':
		case '\n':
			break;
		default:	// Number (hopefully)
			for(y=0;y<=MAX_LENGTH && expr[x];y++,x++) {
				if(!isNumber(expr[x])) {
					--x;		// Revisit this character
					break;
				}
				str[y]=expr[x];
			}
			if(!y) {	// Bad input
				return 0;
			}
			str[y]=0;
			stack.push(str);
			break;
		}
	}

	// If the stack is empty, no answer!
	if(stack.empty())
		return 0;
	else
		answer=atof(stack.pop());

	// If the stack is not empty, too few operations
	if(!stack.empty())
		return 0;

	return 1;
}
