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
  link = NULL;
}

NODE::NODE( char initData, NODE* initLink )
{
  setLink( initLink );
  setData( initData );
}
/***** CONSTRUCTORS *****/

/***** ACCESSORS *****/
NODE* NODE::getLink()const
{
  return link;
}

char NODE::getData()const
{
  return data;
}
/***** ACCESSORS *****/

/***** MUTATORS *****/
void NODE::setLink( NODE* newLink )
{
  link = newLink;
}

void NODE::setData( const char newData )
{
  data = newData;
}
/***** MUTATORS *****/
