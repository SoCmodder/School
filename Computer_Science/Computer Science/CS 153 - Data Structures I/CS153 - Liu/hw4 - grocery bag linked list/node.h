/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: node.h
 * desc: contains the class definition for the node.
 */

#ifndef NODE_H
#define NODE_H

#include "grocery.h"

class NODE
{
  // Member variables
  GroceryItem item;
  NODE *link;

  public:
    /* Default constructor.
     * Pre: None.
     * Post: Link is set to NULL
     */
    NODE();

    /* Overloaded constructor.
     * Pre: None.
     * Post: Grocery Item passed is set to the NODE's Grocery Item, and link is pointed
     *       toward what initLink is pointing to.
     */
    NODE( GroceryItem initData, NODE* initLink );
    
    /* Accesses the link variable.
     * Pre: None.
     * Post: Returns the link variable.
     */
    NODE* getLink()const;

    /* Accesses the Grocery Item variable.
     * Pre: None.
     * Post: The Grocery Item is returned.
     */
    GroceryItem getItem()const;
    
    /* Mutator function.
     * Pre: None.
     * Post: The link variable is pointed toward what newLink is pointing at.
     */
    void setLink( NODE* newLink );

    /* Mutator function.
     * Pre: Price is non-negative and description is entered.
     * Post: Values from Grocery Item passed are given to the NODE's item.
     */
    void setItem( const GroceryItem item1 );
};

#endif

