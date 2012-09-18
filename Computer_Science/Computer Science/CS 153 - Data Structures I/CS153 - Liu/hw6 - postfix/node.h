/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: node.h
 * desc: contains the class definition for the node.
 */

#ifndef NODE_H
#define NODE_H

class NODE
{
  // Member variables
  char data;
  NODE *link;

  public:
    /* Default constructor.
     * Pre: None.
     * Post: Link is set to NULL
     */
    NODE();

    /* Overloaded constructor.
     * Pre: None.
     * Post: data passed is set to the NODE's data, and link 
     *       is pointed
     *       toward what initLink is pointing to.
     */
    NODE( char initData, NODE* initLink );
    
    /* Accesses the link variable.
     * Pre: None.
     * Post: Returns the link variable.
     */
    NODE* getLink()const;

    /* Accesses the data variable.
     * Pre: None.
     * Post: The Grocery Item is returned.
     */
    char getData()const;
    
    /* Mutator function.
     * Pre: None.
     * Post: The link variable is pointed toward what newLink is pointing at.
     */
    void setLink( NODE* newLink );

    /* Mutator function.
     * Pre: Non-negative number <10.
     * Post: Value from data passed are given to the NODE's item.
     */
    void setData( const char newData );
};

#endif

