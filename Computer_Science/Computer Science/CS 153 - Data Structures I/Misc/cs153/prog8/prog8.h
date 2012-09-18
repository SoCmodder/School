// prog8.h : main header file for the PROG8 application
//

#if !defined(AFX_PROG8_H__0FC5C374_9CB5_11D4_ADE5_005056000000__INCLUDED_)
#define AFX_PROG8_H__0FC5C374_9CB5_11D4_ADE5_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg8App:
// See prog8.cpp for the implementation of this class
//

class CProg8App : public CWinApp
{
public:
	CProg8App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg8App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG8_H__0FC5C374_9CB5_11D4_ADE5_005056000000__INCLUDED_)
