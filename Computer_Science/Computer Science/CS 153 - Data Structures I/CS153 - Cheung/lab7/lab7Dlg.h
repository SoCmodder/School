// lab7Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Clab7Dlg dialog
class Clab7Dlg : public CDialog
{
// Construction
public:
	
	Clab7Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB7_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox chessbox;
	int inputsize;
	afx_msg void OnBnClickedButton1();
};
