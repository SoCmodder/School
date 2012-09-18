#include "stdafx.h"

#include "listclass.h"



class Stack : private List

{

public:



	CString Pop();
	//Precondition: None
	//Postcondition: The top memeber of the stack is deleted and
	//its value is returned

    bool Push(const char *UserInput);
	//Precondition: None
	//Postcondition: Userinput is inserted on top of the stack.

    CString Top();
	//Precondition: None
	//Postcondition: The value at the top of the stack is
	//returned, but the stack remains unchanged.

	bool IsEmpty();
	//Precondition: None
	//Postcondition: Returns a true if the stack is empty, otherwise
	//returns false.

	bool IsFull();
	//Precondition: None
	//Postcondition: Returns a true if the stack is empty, otherwise
	//returns false.

};



#endif



	