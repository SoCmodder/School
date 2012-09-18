// prog12.h : main header file for the PROG12 application
//

#if !defined(AFX_PROG12_H__198676E4_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
#define AFX_PROG12_H__198676E4_C24D_11D4_AABF_00C0F05923A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CProg12App:
// See prog12.cpp for the implementation of this class
//

class CProg12App : public CWinApp
{
public:
	CProg12App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg12App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProg12App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG12_H__198676E4_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
