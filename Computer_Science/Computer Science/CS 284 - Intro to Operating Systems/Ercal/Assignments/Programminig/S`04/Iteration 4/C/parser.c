/*
 * Author: Brian Sea
 * Date: 12/28/03
 *
 * This file implements the parser
 */

#include <stdlib.h>
#include <stdio.h>

/*
 * struct that holds a string
 *
 * s - actual contents of the string
 * len - the length of the string
 */
typedef struct string_t
{
    char *s;
    int len;
} String;

/*
 * Parser structure
 *
 * tokens - the tokens of the parser
 * numTokens - the number of tokens left in the parser 
 * delimiters - the delimiters used by the parser
 * specialDelimiters - the delimiters to keep as tokens in our list
 */
typedef struct parser_t
{
    String *tokens;
    int numTokens;
    int currToken;
    char *delimiters;
    char *specialDelimiters;
} Parser;

#define DEFAULT_DELIMITERS " ><&"
#define DLT_DELIMITS_SIZE 4

/*
 * Creates a new parser with defaults
 */
Parser *Parser_new()
{
   Parser *p = (Parser *)malloc( sizeof( Parser ) );
   p->numTokens = 0;
   p->currToken = 0;
   p->tokens = NULL;
   p->delimiters = (char *)malloc( (DLT_DELIMITS_SIZE + 1) * sizeof( char ) );
   p->specialDelimiters = (char *)malloc((DLT_DELIMITS_SIZE + 1)*sizeof(char));

   strncpy( p->specialDelimiters, DEFAULT_DELIMITERS, DLT_DELIMITS_SIZE );
   strncpy( p->delimiters, DEFAULT_DELIMITERS, DLT_DELIMITS_SIZE );

   return p;
}

/*
 * Free up the parser
 */
void Parser_free( Parser *p )
{
    if( !p )
    {
        return;
    }

    if( p->tokens )
    {
        /* Free up the tokens */
        while( p->numTokens > 0 )
        {
            free( p->tokens[ p->numTokens - 1 ].s );
            p->numTokens--;
        }
        free( p->tokens );
    }

    if( p->delimiters )
    {
        free( p->delimiters);
    }

    p = NULL;
}

/*
 * adds Delimiters to the parser
 */
void Parser_addDelimiters( Parser *p, char *delimits )
{
    int len = strlen( delimits );
    int lenD = strlen( p->delimiters );
    
    char *scanner = delimits;
    int count = 0;
    
    p->delimiters = realloc( p->delimiters, len + lenD + 1 );
    
    /*
     * Only add the delimiters the don't exist
     */
    while( *scanner != '\0' )
    {
        if( strchr( p->delimiters, *scanner ) == NULL )
        {
            strncat( p->delimiters, scanner, 1 );
            count++;
        }

        scanner++;
    }

    if( count != len )
    {
        p->delimiters = realloc( p->delimiters, len + count + 1 );
    }

    /* Must end strings with the /0 character */
    p->delimiters[len+count+1] = '\0';
}

/*
 * Set the delmiters
 */
void Parser_setDelimiters( Parser *p, char *delimits )
{
    int len = strlen( delimits );

    p->delimiters = realloc( p->delimiters, len + 1 );
    strncpy( p->delimiters, delimits, len + 1 );
}

/*
 * Sets the special delimiters of the parser
 * This function also tries to add the special delimiters to the overall
 * delimiters
 */
void Parser_setSpecialDelimiters( Parser *p, char *delimits )
{
    int len = strlen( delimits );

    p->specialDelimiters = realloc( p->specialDelimiters, len + 1 );
    strncpy( p->specialDelimiters, delimits, len + 1 );

    Parser_addDelimiters( p, delimits );
}

/*
 * Remove delimiters from the parser
 */
void Parser_removeDelimiters( Parser *p, char *delimits )
{
    int len = strlen( delimits );
    int lenD = strlen( p->delimiters );
    int lenP;

    char *scanner = delimits;
    char *placer;
    int count = 0;

    while( *scanner != '\0' )
    {
        /* The delimiter exists? */
        if( (placer = strchr( p->delimiters, *scanner)) != NULL )
        {
            lenP = strlen( placer );
            memmove( placer, placer+1, lenP - 1 );
            count++;
        }
    }

    p->delimiters = realloc( p->delimiters, len - count + 1 );
    p->delimiters[ len - count + 1] = '\0';
}

/*
 * Returns the delimiters of the parser
 */
char *Parser_getDelimiters( Parser *p )
{
    return p->delimiters;
}

/* 
 * Returns the number of tokens in the parser
 */
int Parser_numTokens( Parser *p )
{
    return p->numTokens;
}

/*
 * Strips out the spaces at the beginning and end of the string
 */
static char *stripOuterSpaces( char *String )
{
    char *begin = String;
    int len = strlen(String);
    char *end = &String[len-1];

    while( isspace(*begin) && begin != end )
    {
        begin++;
    }

    while( isspace(*end) && begin != end )
    {
        end--;
    }

    memmove( String, begin, end - begin  + 1 );
    String[end-begin + 1] = '\0';
}

/*
 * Parse out tokens
 */
int Parser_parse( Parser *p, char *string )
{
    char Buffer[512];
    char *begin = string;
    char *end;

    int len;
    int count = 0;
   
   /* Strip out the spaces */
   stripOuterSpaces( string );

   if( p->tokens == NULL )
   {
       p->tokens = malloc( sizeof(String) );
   }

   begin = string;

   while( (end = strpbrk( begin, p->delimiters )) != NULL )
   {

       /*
        * get past inner spaces 
        */
       if( (end - begin) < 1 )
       {
           /* 
            * We're dealing with a special delimiter.. keep it
            */
           if( strchr( p->specialDelimiters, *begin ) != NULL 
                   || strchr(p->delimiters, *begin) == NULL )
           {
                p->numTokens++;
                strncpy( Buffer, begin, 1 );
                Buffer[1] = '\0';
                len = strlen( Buffer );

                p->tokens = realloc( p->tokens, p->numTokens * sizeof( String ) );

                p->tokens[ p->numTokens - 1 ].s = malloc( sizeof(char) * len + 1 );
                strncpy( p->tokens[ p->numTokens - 1].s, Buffer, len + 1 );

           }

           begin = end + 1;
           continue;
       }

       /* 
        * New Token
        */
        p->numTokens++;
        strncpy( Buffer, begin, end-begin );
        Buffer[end-begin] = '\0';
        len = strlen( Buffer );

        p->tokens = realloc( p->tokens, p->numTokens * sizeof( String ) );

        p->tokens[ p->numTokens - 1 ].s = malloc( sizeof(char) * len + 1 );
        strncpy( p->tokens[ p->numTokens - 1].s, Buffer, len + 1 );
        begin = end;

       /*
        * The last character of the current token is NOT in the special
        * delimiters, so skip past to the next character
        */
      if( strchr( p->specialDelimiters, *end ) == NULL )
      {
        begin++;
      }
   }

   /*
    * Deal with the last token
    */
    
   len = strlen( begin );
   if( len > 0  && *begin != '\n')
   {
        p->numTokens++;
        p->tokens = realloc( p->tokens, p->numTokens * sizeof(String) );
        strncpy( Buffer, begin, len );
        Buffer[len] = '\0';
        
        p->tokens[ p->numTokens - 1 ].s = malloc( sizeof(char) * len + 1 );
        strncpy( p->tokens[ p->numTokens - 1].s, Buffer, len + 1 );
    }
                
}

/* 
 * Returns the next token in the list
 */
char *Parser_next( Parser *p )
{
    if( p->currToken >= p->numTokens )
    {
        return NULL;
    }

    p->currToken++;

    return p->tokens[ p->currToken - 1].s;
}

/*
 * Resets the parser back to the first token
 */

void Parser_reset( Parser *p )
{
    p->currToken = 0;
}

/*
 * Clears the token list from the parser
 */
void Parser_clear( Parser *p )
{
    if( p->tokens )
    {
        while( p->numTokens > 0 )
        {
            free( p->tokens[ p->numTokens - 1 ].s );
            p->numTokens--;
        }
        p->currToken = 0;
        free( p->tokens );
    }

    p->tokens=NULL;
}

int Parser_end( Parser *p )
{
    return (p->currToken >= p->numTokens) ? 1 : 0;
}
