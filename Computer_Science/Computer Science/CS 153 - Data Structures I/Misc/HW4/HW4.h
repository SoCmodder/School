// HW4.h : main header file for the HW4 application
//

#if !defined(AFX_HW4_H__245F9251_1823_11D6_BD72_00010227ED76__INCLUDED_)
#define AFX_HW4_H__245F9251_1823_11D6_BD72_00010227ED76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHW4App:
// See HW4.cpp for the implementation of this class
//

class CHW4App : public CWinApp
{
public:
	CHW4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHW4App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW4_H__245F9251_1823_11D6_BD72_00010227ED76__INCLUDED_)
