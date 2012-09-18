//   File Name: Err_Msg.h
//   Function:  Define the class for exception message
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

class CSignal
{
   private:
      char message[80];
   public:
      CSignal( char* s );
      char* get_message() const;
};

