// groceriesDlg.h : header file
//

#pragma once
#include "bag.h"
#include "afxwin.h"


// CgroceriesDlg dialog
class CgroceriesDlg : public CDialog
{
// Construction
public:
	CgroceriesDlg(CWnd* pParent = NULL);	// standard constructor
	Bag groceryBag; // creates the grocery bag used in the program.

// Dialog Data
	enum { IDD = IDD_GROCERIES_DIALOG };

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
	CListBox ListBox;
	double price;
	CString description;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
