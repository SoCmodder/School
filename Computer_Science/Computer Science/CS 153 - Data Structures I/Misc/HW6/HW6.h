// HW6.h : main header file for the HW6 application
//

#if !defined(AFX_HW6_H__C180885E_24B5_11D6_BD74_00010227EF2D__INCLUDED_)
#define AFX_HW6_H__C180885E_24B5_11D6_BD74_00010227EF2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHW6App:
// See HW6.cpp for the implementation of this class
//

class CHW6App : public CWinApp
{
public:
	CHW6App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW6App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHW6App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW6_H__C180885E_24B5_11D6_BD74_00010227EF2D__INCLUDED_)
