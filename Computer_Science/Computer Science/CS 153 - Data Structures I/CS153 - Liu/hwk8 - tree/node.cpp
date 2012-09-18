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
  sprintf( buffer, "%i", count ); // Converts count to a string.
  CString CountAsString = buffer; // Puts count in a CString.
  
  return( data + " (" + CountAsString + ")"); 
}