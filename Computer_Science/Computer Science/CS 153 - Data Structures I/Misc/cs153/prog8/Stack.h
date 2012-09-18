// Stack.h: interface for the CStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__0FC5C37F_9CB5_11D4_ADE5_005056000000__INCLUDED_)
#define AFX_STACK_H__0FC5C37F_9CB5_11D4_ADE5_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Assignment 8
// Erin Pringle and Joe Wingbermuehle
// Stack class header (requires CDList)

#include "DList.h"

class CStack : private CDList {
public:
	CStack();

	virtual ~CStack();

	void push(const char* str);

	CString pop(void);

	CString top(void);

	CDList::empty;

	CDList::full;

};

#endif // !defined(AFX_STACK_H__0FC5C37F_9CB5_11D4_ADE5_005056000000__INCLUDED_)
