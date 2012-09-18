// HW4Dlg.h : header file
//

#if !defined(AFX_HW4DLG_H__245F9253_1823_11D6_BD72_00010227ED76__INCLUDED_)
#define AFX_HW4DLG_H__245F9253_1823_11D6_BD72_00010227ED76__INCLUDED_

#include "ListBox.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHW4Dlg dialog

class CHW4Dlg : public CDialog
{
// Construction
public:
	CHW4Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHW4Dlg)
	enum { IDD = IDD_HW4_DIALOG };
	CListBox	m_ListBox;
	CString	m_Messages;
	CString	m_Input;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW4Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHW4Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONInsert();
	afx_msg void OnBUTTONFind();
	afx_msg void OnBUTTONRemove();
	afx_msg void OnBUTTONFull();
	afx_msg void OnBUTTONEmpty();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ListBox ListBox;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW4DLG_H__245F9253_1823_11D6_BD72_00010227ED76__INCLUDED_)
