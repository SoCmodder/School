// Stack.cpp: implementation of the CStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "prog8.h"
#include "Stack.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Assignment 8
// Erin Pringle and Joe Wingbermuehle
// Implementation for the stack class

CStack::CStack() {

}

CStack::~CStack() {

}

void CStack::push(const char* str) {
	insertHead(str);
}

CString CStack::pop(void) {
	return removeHead();
}

CString CStack::top(void) {
	return getHead();
}
