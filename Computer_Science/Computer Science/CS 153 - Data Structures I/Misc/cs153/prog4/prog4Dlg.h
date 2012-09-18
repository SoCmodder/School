// prog4Dlg.h : header file
//

#if !defined(AFX_PROG4DLG_H__1EC94D4C_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
#define AFX_PROG4DLG_H__1EC94D4C_85BF_11D4_A46D_006097D2E7B9__INCLUDED_

#include "Bag.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg4Dlg dialog

class CProg4Dlg : public CDialog
{
// Construction
public:
	CProg4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg4Dlg)
	enum { IDD = IDD_PROG4_DIALOG };
	CListBox	m_bag;
	int		m_value;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonIsfull();
	afx_msg void OnButtonEmpty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DisplayBag(void);
	CBag bag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG4DLG_H__1EC94D4C_85BF_11D4_A46D_006097D2E7B9__INCLUDED_)
