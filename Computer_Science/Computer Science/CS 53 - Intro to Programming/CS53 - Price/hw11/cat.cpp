/* programmer: Clayton Price          date: 11/26/05                  *
 * file: cat.cpp                                                      *
 * purpose: this file contains the function definitions of the member *
 *           functions of the cat class.                              */

#include "cat.h"
#include <iostream>
#include<string>

using namespace std;

// The speak function will output to the std out "meow".
// Pre: none.
// Post: "meow" output to std out (cout)

void cat::speak()const
{
  cout<<"meow";
  return;
}

// The op == () function will return true if both cats are dead or if both
//    are alive and identical in all other aspects
// Pre: none.
// Post: true returned if calling obj and passed obj both dead or if both
//       alive and all other attributes identical.
// NOTE: This is good example of really cooool code that is extremely hard
//       to read simply because I nested the ternary operator - a good
//       example of what I told you not to do.  But it works. Nicely.
//       Efficiently.

bool cat::operator == (const cat& rhs)const
{
  return m_isAlive != rhs.m_isAlive ? false : (!m_isAlive ? true :
         (m_name==rhs.m_name && m_age==rhs.m_age && m_wt==rhs.m_wt &&
          m_hasClaws==rhs.m_hasClaws && m_color==rhs.m_color));
}

// The op != () returns negation of op == ().
// Pre: none.
// Post: opposite of Post for == operator.

bool cat::operator != (const cat& rhs)const
{
  return !(*this == rhs);
}

// The op < () returns true if calling cat is dead and passed cat is
// alive, if both cats are alive and calling cat has no claws but passed
// cat does, if both cats are alive and both cats have or don't have claws
// and if the ratio of age to wt is less for calling cat than passed cat.
// Pre: none.
// Post: returns bool value described in function description.

bool cat::operator < (const cat& rhs)const
{
  bool lessthan = false;            //default if calling obj is dead and
                                    //other is
                                    // alive OR both alive and calling obj
                                    // has no claws
  if (!m_isAlive && rhs.m_isAlive)  // callin obj dead, other alive
    lessthan = true;
  else if (m_isAlive && rhs.m_isAlive)         // both alive
  {
    if ((!m_hasClaws && !rhs.m_hasClaws) || (m_hasClaws && rhs.m_hasClaws))
      lessthan = ((m_wt/m_age)<(rhs.m_wt/rhs.m_age));  // both w/ or w/o
                                                       // claws
    else if (!m_hasClaws && rhs.m_hasClaws)    // both alive, caller w/o
                                               // claws
      lessthan = true;
  }
  return lessthan;
}

// The operators <=, >, >= are defined in terms of < operator and ==
// operator.
// Pre: none.
// Post: returns bool value determined by the rules set out in the funct.
//    description for operator <.

bool cat::operator <= (const cat& rhs)const
{
  return (*this < rhs || *this == rhs);
}

bool cat::operator > (const cat& rhs)const
{
  return (!(*this < rhs) && *this != rhs);
}

bool cat::operator >= (const cat& rhs)const
{
  return !(*this<rhs);
}

// The op << () function will output a cat in specified format if called.
// Pre: none.
// Post: a cat is output to the screen in the specified format.
ostream& operator <<(ostream & o, const cat cat1)
{
  o << cat1.m_name << "(a " << cat1.m_color << " ";
  switch(cat1.m_type)
  {
    case 1:
      cout << "polecat";
      break;
    case 2:
      cout << "housecat";
      break;
    case 3:
      cout << "bobcat";
      break;
    case 4:
      cout << "panther";
      break;
    case 5:
      cout << "liger";
  }

    cout << "): " << "wt = " << cat1.m_wt << " age = " << cat1.m_age;
    if (cat1.m_hasClaws)
      o << " has claws and ";

    else
      o << " has no claws and ";

    if (cat1.m_isAlive)
      o << "is alive." << endl;

    else
      o << "is dead." << endl;

  return o;
}

// The op >> () function will extract a cat in specified format if called.
// Pre: none.
// Post: a cat is input to the calling object in the specified format.
istream& operator >>(istream & in, cat & cat1)
{
  in >> cat1.m_name;
  in >> cat1.m_age;
  in >> cat1.m_wt;
  in >> cat1.m_hasClaws;
  in >> cat1.m_isAlive;
  in >> cat1.m_color;
  in >> cat1.m_type;

  return in;
}
