/* programmer: robertoMurillo    date: 11/11/05 *
 * file: main_fnct.cpp           class: cs53    *
 * purpose: using classes.                      */

/********** DEFINITIONS **********/

#include <iostream>
#include <ostream>
#include "main.h"
using namespace std;

/********** CONSTRUCTORS **********/
// the default constructor has all default values.
// pre: none.
// post: fills a cat with the default values.
Cat::Cat()
{
  m_name = "cat";
  m_age = 1;
  m_weight = 10.0;
  m_hasClaws = true;
  m_isAlive = true;
  m_color = "kaliko";
}

// the user-defined constructor has all user-defined values.
// pre: none.
// post: all of the variables in the cat class are defined.
Cat::Cat( string name, int age, float weight, bool hasClaws, bool isAlive,
          string color )
{
  m_name = name;
  m_age = age;
  m_weight = weight;
  m_hasClaws = hasClaws;
  m_isAlive = isAlive;
  m_color = color;
}
/********** CONSTRUCTORS **********/

/********** ACCESSORS **********/
// getName() allows access to the cat's name.
// pre: m_name must be declared.
// post: returns the name of the cat as a string.
string Cat::getName()const
{
  return m_name;
}

// getAge() allows access to the cat's age.
// pre: m_age must be declared.
// post: the age of the cat is returned.
int Cat::getAge()const
{
  return m_age;
}

// getWeight() allows access to the weight of the cat.
// pre: m_weight must be declared.
// post: the weight is returned.
float Cat::getWeight()const
{
  return m_weight;
}

// getClaws() allows access to if the cat has claws or not.
// pre: m_hasClaws must be declared.
// post: whether the cat has claws or not is set to true or false.
// depending on if true or not, a string is output saying Yes or No.
string Cat::getClaws()const
{
  string string1;

  if ( m_hasClaws )
     string1 = "Yes.";

  else
    string1 = "No.";

  return string1;
}


string Cat::getAlive()const
{
  string string1;

  if ( m_isAlive )
    string1 = "Yes.";

  else
    string1 = "No.";

  return string1;
}

// getColor() allows access to the color of the cat.
// pre: m_color must be declared.
// post: the color of the cat is returned.
string Cat::getColor()const
{
  return m_color;
}
/********** ACCESSORS **********/

/********** MUTATORS **********/
// setName() sets the name to the string defined by the user.
// pre: a string must be sent to the function.
// post: sets m_name equal to the string entered by the user.
void Cat::setName( string name )
{
  m_name = name;

  return;
}

// setWeight() sets the weight equal to a float defined by the user.
// pre: a float must be sent to the function.
// post: sets m_weight equal to the float entered by the user.
void Cat::setWeight( float weight )
{
  m_weight = weight;

  return;
}

// setClaws() sets the claws equal to true or false.
// pre: true or false value must be sent to the function.
// post: sets m_hasClaws equal to true or false.
void Cat::setClaws ( bool claws )
{
  m_hasClaws = claws;

  return;
}

// setAge() sets the age to a number defined by the user.
// pre: an integer must be sent to the function.
// post: sets m_age equal to the age declared by the user.
void Cat::setAge ( int age )
{
  m_age = age;

  return;
}
/********** MUTATORS **********/
// speak() outputs the cat's meow.
// pre: none.
// post: outputs meow to the screen.
void Cat::speak()
{
  cout << "meow." << endl;

  return;
}

/********** OVERLOADED OPERATORS **********/
// operator < overloads the < operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the < operator is overloaded and is given a true or false
//       value.
bool operator <( const Cat& lhs, const Cat& rhs )
{
  bool lessThan = false;

  if ( lhs.m_isAlive == false && rhs.m_isAlive == true )
    lessThan = true;

  if ( lhs.m_isAlive == true && rhs.m_isAlive == true )
  {
    if ( lhs.m_hasClaws == false && rhs.m_hasClaws == true )
      lessThan = true;

    if ( lhs.m_hasClaws == rhs.m_hasClaws )
    {
      if ( (lhs.m_weight/lhs.m_age) < (rhs.m_weight/rhs.m_age) )
        lessThan = true;
    }
  }

  return lessThan;
}

// operator >= overloads the >= operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the >= operator is overloaded and given a value of true or
//       false.
bool operator >=( const Cat& lhs, const Cat& rhs )
{
  bool greatOrEqual = false;

  if ( !(lhs < rhs) )
    greatOrEqual = true;

  return greatOrEqual;
}

// operator >overloads the > operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the > operator is overloaded and is given a true or false
//       value.

bool operator >( const Cat& lhs, const Cat& rhs )
{
  bool greaterThan = false;

  if ( lhs.m_isAlive == true && rhs.m_isAlive == false )
    greaterThan = true;

  if ( lhs.m_isAlive == true && rhs.m_isAlive == true )
  {
    if ( lhs.m_hasClaws == true && rhs.m_hasClaws == false )
      greaterThan = true;

    if ( lhs.m_hasClaws == rhs.m_hasClaws )
    {
      if ( (lhs.m_weight/lhs.m_age) > (rhs.m_weight/rhs.m_age) )
        greaterThan = true;
    }
  }

  return greaterThan;
}

// operator <= overloads the <= operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the <= operator is overloaded and given a value of true or
//       false.
bool operator <=( const Cat& lhs, const Cat& rhs )
{
  bool lessOrEqual = false;

  if ( !(lhs > rhs) )
    lessOrEqual = true;

  return lessOrEqual;
}

// operator == overloads the == operator for the cat class.
// Pre: calling object must be declared as a cat.
// Post: the == operator is overloaded and given a value of true or
//       false.
bool operator ==( const Cat& lhs, const Cat& rhs )
{
  bool equalTo = false;

  if ( lhs.m_isAlive == false && rhs.m_isAlive == false )
    equalTo = true;

  if ( lhs.m_isAlive == true &&  rhs.m_isAlive == true )
  {
    if ( lhs.m_hasClaws == rhs.m_hasClaws )
    {
      if ( (lhs.m_weight/lhs.m_age) == (rhs.m_weight/rhs.m_age) )
        equalTo = true;
    }
  }

  return equalTo;
}

// operator != overloads the != operator for the cat class.
// pre: calling object must be declared as a cat.
// post: the != operator is overloaded and given a value of true or
//       false.
bool operator != ( const Cat& lhs, const Cat& rhs )
{
  bool notEqual = false;

  if ( !( (lhs == rhs) ) )
    notEqual = true;

  return notEqual;
}
/********** OVERLOADED OPERATORS **********/

/********** DEFINITIONS **********/

