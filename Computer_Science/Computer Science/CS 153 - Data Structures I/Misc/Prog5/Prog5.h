// Prog5.h : main header file for the PROG5 application
//

#if !defined(AFX_PROG5_H__EEB1567F_F18F_4455_AD2F_5CD9E9BCCA20__INCLUDED_)
#define AFX_PROG5_H__EEB1567F_F18F_4455_AD2F_5CD9E9BCCA20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg5App:
// See Prog5.cpp for the implementation of this class
//

class CProg5App : public CWinApp
{
public:
	CProg5App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg5App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg5App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG5_H__EEB1567F_F18F_4455_AD2F_5CD9E9BCCA20__INCLUDED_)
