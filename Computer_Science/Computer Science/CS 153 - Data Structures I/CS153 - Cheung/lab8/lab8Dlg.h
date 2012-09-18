// lab8Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "tree.h"


// Clab8Dlg dialog
;class Clab8Dlg : public CDialog
{
// Construction
public:
	Clab8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LAB8_DIALOG };

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
	int input_number;
	CListBox output_box;
	afx_msg void OnBnClickedButton2();
	BST thetree;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
};
