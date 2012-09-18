//Filename: prog3.h
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 



#if !defined(AFX_PROG3_H__97E73F84_F5FE_11D4_BC2C_005004947316__INCLUDED_)
#define AFX_PROG3_H__97E73F84_F5FE_11D4_BC2C_005004947316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg3App:
// See prog3.cpp for the implementation of this class
//

class CProg3App : public CWinApp
{
public:
	CProg3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG3_H__97E73F84_F5FE_11D4_BC2C_005004947316__INCLUDED_)
