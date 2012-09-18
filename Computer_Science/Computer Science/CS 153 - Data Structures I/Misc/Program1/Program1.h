// Program1.h : main header file for the PROGRAM1 application
//

#if !defined(AFX_PROGRAM1_H__E373A83E_9621_4DD0_A96B_8E541B4B371B__INCLUDED_)
#define AFX_PROGRAM1_H__E373A83E_9621_4DD0_A96B_8E541B4B371B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProgram1App:
// See Program1.cpp for the implementation of this class
//

class CProgram1App : public CWinApp
{
public:
	CProgram1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgram1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProgram1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAM1_H__E373A83E_9621_4DD0_A96B_8E541B4B371B__INCLUDED_)
