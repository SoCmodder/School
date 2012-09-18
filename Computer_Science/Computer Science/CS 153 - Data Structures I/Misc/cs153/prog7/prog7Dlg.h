// prog7Dlg.h : header file
//

#if !defined(AFX_PROG7DLG_H__D09666F6_9960_11D4_ADD1_005056EC703B__INCLUDED_)
#define AFX_PROG7DLG_H__D09666F6_9960_11D4_ADD1_005056EC703B__INCLUDED_

#include "DList.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg7Dlg dialog

class CProg7Dlg : public CDialog
{
// Construction
public:
	CProg7Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg7Dlg)
	enum { IDD = IDD_PROG7_DIALOG };
	CListBox	m_list;
	CString	m_input;
	int		m_current;
	int		m_selection;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg7Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg7Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonInsertAfter();
	afx_msg void OnButtonInsertBefore();
	afx_msg void OnButtonInsertHead();
	afx_msg void OnButtonInsertTail();
	afx_msg void OnButtonRemoveCurrent();
	afx_msg void OnButtonRemoveHead();
	afx_msg void OnButtonRemoveTail();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonEmpty();
	afx_msg void OnButtonFull();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonSet();
	afx_msg void OnSelchangeListBag();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool CheckInput(void);
	void DisplayList(void);
	CDList m_bag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG7DLG_H__D09666F6_9960_11D4_ADD1_005056EC703B__INCLUDED_)
