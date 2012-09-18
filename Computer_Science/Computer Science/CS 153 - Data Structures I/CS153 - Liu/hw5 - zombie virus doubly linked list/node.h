/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: node.h
 * desc: contains the class definition for the node.
 */

#ifndef NODE_H
#define NODE_H

#include "person.h"

class NODE
{
  // Member variables
  PERSON human;
  NODE *next;
  NODE *prev;

  public:
    /* Default constructor.
     * Pre: None.
     * Post: next and prev are set to NULL
     */
    NODE();

    /* Overloaded constructor.
     * Pre: None.
     * Post: person passed is set to the NODE's person, and next and prev are pointed
     *       toward what nextLink and prevLink are pointing to, respectively.
     */
    NODE( PERSON initData, NODE* nextLink, NODE* prevLink );
    
    /* Accesses the next variable.
     * Pre: None.
     * Post: Returns the next variable.
     */
    NODE* getNext()const;

    /* Accesses the prev variable.
     * Pre: None.
     * Post: Returns the prev variable.
     */
    NODE* getPrev()const;

    /* Accesses the person data.
     * Pre: None.
     * Post: The person is returned.
     */
    PERSON getPerson()const;
    
    /* Mutator function.
     * Pre: None.
     * Post: The next variable is pointed toward what newLink is pointing at.
     */
    void setNext( NODE* newLink );

    /* Mutator function.
     * Pre: None.
     * Post: The prev variable is pointed toward what newLink is pointing at.
     */
    void setPrev( NODE* newLink );

    /* Mutator function.
     * Pre: None.
     * Post: Values from person passed are given to the NODE's person.
     */
    void setPerson( const PERSON human1 );
};

#endif

