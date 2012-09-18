/* Roberto Murillo
 * patient.cpp
 * Description: Contains the toString function for the PATIENT.
 */

#include "stdafx.h"
#include "node.h"

CString PATIENT::toString()const 
{ 
  // Creates a buffer to store the number in.
  char buffer[100000];
  sprintf( buffer, "%i", priority ); // Converts priority to a string.
  CString PriorityAsString = buffer; // Puts priority in a CString.
  
  return( description + " (" + PriorityAsString + ")"); 
}