/* programmer: robertoMurillo   date: 11/05/05 *
 * file: question.h             class: cs53    *
 * purpose: header file for question program.  */

#ifndef QUESTION_H
#define QUESTION_H

/*************** CONSTANTS ***************/

const int SIZE = 150;

/*************** CONSTANTS ***************/

/*************** PROTOTYPES ***************/

// welcome message
// pre: none
// post: outputs a welcome message to the screen
void welcome();

// asks the user for a question
// pre: an array named question with a SIZE must be declared
// post: array turned into NTCA and filled with the question asked
void get_question( char question1[ ], const int SIZE );

// shows the user their question
// pre: question array must have been filled
// post: outputs the user's question to the screen
void show_question( const char question1[ ] );

// asks the user if they want to enter another question
// pre: none
// post: a message asking user if they want to run program again is
//       output to the screen and set to either true or false.
bool runAgain();

// calculates an answer depending on the question asked
// pre: question array must be filled, answer array must've been declared
// post: chooses an answer based on how many characters are in the
// question, modded by the number of answers, and is output to the screen
void present_answer( char answer[ ], const int length );

// logs both the question and answer
// pre: the question and answer arrays must be filled.
// post: the question and answer arrays are output to the log file
//       created by the ofstream.
void create_log( const char question1[ ], const char answer[ ] );

// itoa function because the c++ itoa function wouldnt work
// copied from http://www.jb.man.ac.uk/~slowe/cpp/itoa.html
char* itoa( int value, char* result, int base );

/*************** PROTOTYPES ***************/

#endif
