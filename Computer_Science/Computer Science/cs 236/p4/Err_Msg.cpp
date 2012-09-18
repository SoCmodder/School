//   File Name: Err_Msg.cpp
//   Function:  Implement the class for exception message
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#include "Err_Msg.h"
#include <string.h>

CSignal::CSignal( char* s )
{
   strcpy( message, s );
}
      
char* CSignal::get_message() const
{
   return (char*)message;
}

