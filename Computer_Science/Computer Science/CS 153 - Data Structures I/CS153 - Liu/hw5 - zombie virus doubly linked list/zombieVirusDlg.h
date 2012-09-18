// zombieVirusDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "LINKLIST.h"

// CzombieVirusDlg dialog
class CzombieVirusDlg : public CDialog
{
// Construction
public:
	CzombieVirusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ZOMBIEVIRUS_DIALOG };

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
  LINKLIST alive;
  LINKLIST cemetary;
  CString name;
  CListBox aliveListBox;
  CListBox cemetaryListBox;
  afx_msg void OnBnClickedADD();
  afx_msg void OnBnClickedVaccinate();
  afx_msg void OnBnClickedZombify();
  afx_msg void OnBnClickedarmageddon();
  afx_msg void OnBnClickedZombieAttack();
  afx_msg void OnBnClickedkillZombies();
};
