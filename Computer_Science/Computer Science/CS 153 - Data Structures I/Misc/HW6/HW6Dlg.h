// HW6Dlg.h : header file
//

#if !defined(AFX_HW6DLG_H__C1808860_24B5_11D6_BD74_00010227EF2D__INCLUDED_)
#define AFX_HW6DLG_H__C1808860_24B5_11D6_BD74_00010227EF2D__INCLUDED_

#include "Student.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHW6Dlg dialog

class CHW6Dlg : public CDialog
{
// Construction
public:
	CHW6Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHW6Dlg)
	enum { IDD = IDD_HW6_DIALOG };
	CListBox	m_ListBox;
	int		m_Age;
	double	m_GPA;
	CString	m_Name;
	CString	m_messages;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW6Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHW6Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonFull();
	afx_msg void OnButtonEmpty();
	afx_msg void OnButtonRemove();
	afx_msg void OnBUTTONINSERTStudent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Student StudentList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW6DLG_H__C1808860_24B5_11D6_BD74_00010227EF2D__INCLUDED_)
