// prog7.h : main header file for the PROG7 application
//

#if !defined(AFX_PROG7_H__D09666F4_9960_11D4_ADD1_005056EC703B__INCLUDED_)
#define AFX_PROG7_H__D09666F4_9960_11D4_ADD1_005056EC703B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg7App:
// See prog7.cpp for the implementation of this class
//

class CProg7App : public CWinApp
{
public:
	CProg7App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg7App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg7App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG7_H__D09666F4_9960_11D4_ADD1_005056EC703B__INCLUDED_)
