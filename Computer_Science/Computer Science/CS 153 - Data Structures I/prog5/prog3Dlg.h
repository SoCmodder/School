//prog3Dlg.h : header file
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #5
//This program will insert, find, get, and remove integers from a doubly linked list.  
//Also it will tell if the list is empty or full.

#include"bag.h"
#if !defined(AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_)
#define AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg dialog


class CProg3Dlg : public CDialog
{
// Construction
public:
	void Display();
	CProg3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProg3Dlg)
	enum { IDD = IDD_PROG3_DIALOG };
	CListBox	m_OutputListing;
	int		m_input;
	CString	m_message;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProg3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProg3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBUTTONFind();
	afx_msg void OnBUTTONfull();
	afx_msg void OnBUTTONEmpty();
	afx_msg void OnBUTTONInsertHead();
	afx_msg void OnButtonInsertTail();
	afx_msg void OnBUTTONRemoveHead();
	afx_msg void OnBUTTONRemoveTail();
	afx_msg void OnBUTTONGetHead();
	afx_msg void OnBUTTONGetTail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    CBag my_bag;
    bool testbool;  //Used to store return value of functions.
    int testint;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROG3DLG_H__97E73F86_F5FE_11D4_BC2C_005004947316__INCLUDED_)
