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

NODE::NODE( GroceryItem initData, NODE* initLink )
{
  link = initLink;

  item.setPrice( initData.getPrice() );
  item.setDescription( initData.getDescription() );
}
/***** CONSTRUCTORS *****/

/***** ACCESSORS *****/
NODE* NODE::getLink()const
{
  return link;
}

GroceryItem NODE::getItem()const
{
  return item;
}
/***** ACCESSORS *****/

/***** MUTATORS *****/
void NODE::setLink( NODE* newLink )
{
  link = newLink;
}

void NODE::setItem( const GroceryItem item1 )
{
  item.setDescription( item1.getDescription() );
  item.setPrice( item1.getPrice() );
}
/***** MUTATORS *****/
