/* programmer: robertoMurillo   date: 11/05/05 *
 * file: question.cpp           class: cs53    *
 * purpose: main file for question program.    */

#include <iostream>
#include <fstream>
#include "question.h"
using namespace std;

int main()
{
  char question[SIZE]; // where the question is inserted into.
  char answer[SIZE]; // where the answer is inserted

  welcome(); // welcome message

  do
  {
  get_question(question, SIZE); // asks user to enter question
  show_question(question); // repeats their question

  present_answer(answer, strlen(question)); // pulls an answer from
                                                     // file
  create_log(question, answer); // logs both question and answer
  } while ( runAgain() ); // program runs while they want to ask another
                          // question.

  return 0;
}
