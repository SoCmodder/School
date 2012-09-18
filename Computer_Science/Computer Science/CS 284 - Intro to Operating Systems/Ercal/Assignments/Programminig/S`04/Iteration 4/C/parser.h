/*
 * Author: Brian Sea
 * Date: 12/28/03
 *
 * This file implements the parser for our shell.  This is done in an
 * object-oriented fashion!!  
 *
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string.h>
/*
 * Opaque Parser structure
 *
 * NOTE:  You cannot create this struct, you have to use a pointer to it
 */
typedef struct parser_t Parser;

/*
 * Initializes a parser
 *
 * returns:
 * NULL on failure
 *
 * A new parser object is returned on success
 */
Parser *Parser_new();

/*
 * Frees up the parser
 *
 * p is set to NULL
 */
void Parser_free( Parser *p );

/*
 * Sets the parser's, p, to the delmiters pointed to by delimits
 */
void Parser_setDelimiters( Parser *p, char *delmits );

/*
 * Set the parser's SPECIAL delimiters.  These characters are saved in
 * the token list of the parser. 
 */
void Parser_setSpecialDelimiters( Parser *p, char *delimits );

/*
 * Adds delimiters to the parser
 */
void Parser_addDelimiters( Parser *p, char *delimits );

/*
 * Removes delimiters from the parser
 */
void Parser_removeDelimiters( Parser *p, char *delmits );

/* 
 * Returns the delimiters of the parser, p
 */
char *Parser_getDelimiters( Parser *p );

/*
 * Returns the number of tokens left in the Parser
 */
int Parser_numTokens( Parser *p );

/*
 * Parses the String into tokens and stores those tokens into the Parser
 *
 * returns the number of tokens parsed
 */
int Parser_parse( Parser *p, char *String );

/*
 * Returns the next token in the parser.
 *
 * Returns NULL if no more tokens exist
 *
 * NOTE:  If you change the data at this pointer then you change the ACTUAL
 * data.
 */
char *Parser_next( Parser *p );

/*
 * Clears the token list from the parser
 */
void Parser_clear( Parser *p );

/*
 * Resets the parser back to the first token
 *
 * This DOES NOT clear the list out of the parser!
 */
void Parser_reset( Parser *p );

/*
 * Are we at the end of the parser's list?
 *
 * returns:
 *  0 if not at the end
 *  1 if we are
 */
int Parser_end( Parser *p );



#endif
