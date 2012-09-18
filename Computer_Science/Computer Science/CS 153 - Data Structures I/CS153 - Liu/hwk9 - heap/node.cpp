/* Roberto Murillo
 * node.cpp
 * Description: Contains the toString function for the node.
 */

#include "stdafx.h"
#include "node.h"

CString NODE::toString()const 
{ 
  // Creates a buffer to store the number in.
  char buffer[100000];
  sprintf( buffer, "%i", priority ); // Converts count to a string.
  CString PriorityAsString = buffer; // Puts count in a CString.
  
  return( description + " (" + PriorityAsString + ")"); 
}