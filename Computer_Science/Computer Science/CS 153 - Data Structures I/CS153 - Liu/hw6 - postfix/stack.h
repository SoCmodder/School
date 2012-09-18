/* Programmer: Roberto Murillo
 * Instructor: Liu
 * Date: 2/26/06
 * Description: Contains the STACK class and its functions.
 */

#ifndef STACK_H
#define STACK_H

#include "list.h"

/********* STACK CLASS WITH A PARENT CLASS OF LINKLIST *********/
class stack : public LINKLIST
{
  public:
    /* Pushes passed item onto stack.
     * Pre: None.
     * Post: Item is added on top of the stack.
     */

    void push( const char itemToPush ) {insertAtHead( itemToPush );}
    /* Pops the top item off the stack.
     * Pre: Something is in the stack.
     * Post: Item is popped off the stack.
     */
    void pop() {removeHeadNode();}

    /* Checks to see what the top item on stack is.
     * Pre: None.
     * Post: Top item's character is returned.
     */
    char top() {return getHeadPtr()->getData();}
};
/********* STACK CLASS WITH A PARENT CLASS OF LINKLIST *********/

#endif
