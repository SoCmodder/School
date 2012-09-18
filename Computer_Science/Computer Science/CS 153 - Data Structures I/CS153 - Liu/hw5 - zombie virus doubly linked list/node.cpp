/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: node.cpp
 * desc: contains the functions for the node class.
 */

#include "stdafx.h"
#include "node.h"
using namespace std;

/***** CONSTRUCTORS *****/
NODE::NODE()
{
  setNext( NULL );
  setPrev( NULL );
}

NODE::NODE( PERSON initData, NODE* nextLink, NODE* prevLink )
{
  setNext( nextLink );
  setPrev( prevLink );
  setPerson( initData );
}
/***** CONSTRUCTORS *****/

/***** ACCESSORS *****/
NODE* NODE::getNext()const
{
  return next;
}

NODE* NODE::getPrev()const
{
  return prev;
}

PERSON NODE::getPerson()const
{
  return human;
}
/***** ACCESSORS *****/

/***** MUTATORS *****/
void NODE::setNext( NODE* newLink )
{
  next = newLink;
}

void NODE::setPrev( NODE* newLink )
{
  prev = newLink;
}

void NODE::setPerson( const PERSON human1 )
{
  human.setName( human1.getName() );
  human.setStatus( human1.getStatus() );
}
/***** MUTATORS *****/
