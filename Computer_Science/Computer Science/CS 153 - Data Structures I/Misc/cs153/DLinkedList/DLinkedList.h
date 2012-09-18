// DLinkedList.h : main header file for the DLINKEDLIST application
//

#if !defined(AFX_DLINKEDLIST_H__9D94FB34_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
#define AFX_DLINKEDLIST_H__9D94FB34_90C8_11D4_ADCA_005056EC703B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDLinkedListApp:
// See DLinkedList.cpp for the implementation of this class
//

class CDLinkedListApp : public CWinApp
{
public:
	CDLinkedListApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLinkedListApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDLinkedListApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLINKEDLIST_H__9D94FB34_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
