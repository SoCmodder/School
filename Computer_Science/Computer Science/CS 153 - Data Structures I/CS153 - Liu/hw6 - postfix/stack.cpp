/* Programmer: Roberto Murillo
 * Instructor: Liu
 * Date: 2/26/06
 * Description: Contains the STACK function definitions.
 */

#include "stack.h"

void stack::push( const NODE* itemToPush )
{
  insertAtHead( itemToPush ); // Inserts at the top of the stack.
}

NODE* stack::pop()
{
  removeHeadNode(); // Pulls off the top item from the stack.
}

NODE* stack::peek()
{
  getHeadPtr(); // Returns the top item of the stack.
}