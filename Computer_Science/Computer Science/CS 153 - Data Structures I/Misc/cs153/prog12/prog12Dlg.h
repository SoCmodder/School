// prog12Dlg.h : header file
//

#if !defined(AFX_PROG12DLG_H__198676E6_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
#define AFX_PROG12DLG_H__198676E6_C24D_11D4_AABF_00C0F05923A6__INCLUDED_

#include "Hash.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg12Dlg dialog

class CProg12Dlg : public CDialog
{
// Construction
public:
	CProg12Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg12Dlg)
	enum { IDD = IDD_PROG12_DIALOG };
	CListBox	m_list;
	CString	m_input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg12Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg12Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonQuery();
	afx_msg void OnButtonBuild();
	afx_msg void OnButtonInitialize();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonSummerize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CHash m_hash;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG12DLG_H__198676E6_C24D_11D4_AABF_00C0F05923A6__INCLUDED_)
