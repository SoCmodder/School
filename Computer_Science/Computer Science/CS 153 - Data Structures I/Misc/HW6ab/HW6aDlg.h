// HW6aDlg.h : header file
//

#if !defined(AFX_HW6ADLG_H__0E4AB3FC_264E_11D6_BD85_00010227F346__INCLUDED_)
#define AFX_HW6ADLG_H__0E4AB3FC_264E_11D6_BD85_00010227F346__INCLUDED_

#include "Student.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHW6aDlg dialog

class CHW6aDlg : public CDialog
{
// Construction
public:
	CHW6aDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHW6aDlg)
	enum { IDD = IDD_HW6A_DIALOG };
	CListBox	m_ListBox;
	double	m_GPA;
	int		m_Age;
	CString	m_Name;
	CString	m_messages;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHW6aDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHW6aDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONInsert();
	afx_msg void OnBUTTONRemove();
	afx_msg void OnBUTTONFind();
	afx_msg void OnBUTTONFull();
	afx_msg void OnBUTTONEmpty();
	afx_msg void OnBUTTONInsertTail();
	afx_msg void OnBUTTONRemoveHead();
	afx_msg void OnBUTTONRemoveTail();
	afx_msg void OnBUTTONInsertHead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	Student StudentList;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HW6ADLG_H__0E4AB3FC_264E_11D6_BD85_00010227F346__INCLUDED_)
