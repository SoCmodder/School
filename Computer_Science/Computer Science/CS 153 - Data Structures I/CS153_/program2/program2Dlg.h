// program2Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cprogram2Dlg dialog
class Cprogram2Dlg : public CDialog
{
// Construction
public:
	Cprogram2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROGRAM2_DIALOG };

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
   int weight;
   CString description;
   CListBox trashBagListBox;
   afx_msg void Add_Button();
   afx_msg void Delete_Button();
   afx_msg void Empty_Button();

private:
	bag Bag;

};
