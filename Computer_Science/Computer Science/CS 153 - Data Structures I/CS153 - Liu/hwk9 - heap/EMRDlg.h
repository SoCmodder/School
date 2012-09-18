// EMRDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "heap.h"
#include "afxcmn.h"


// CEMRDlg dialog
class CEMRDlg : public CDialog
{
// Construction
public:
	CEMRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EMR_DIALOG };

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
  CString medProblem;
  int priNum;
  CComboBox comboBox;
  HEAP eRoom;
  afx_msg void OnBnClickedADD();
  afx_msg void OnBnClickedTREAT();
  afx_msg void OnBnClickedCLEAR();
  afx_msg void OnBnClickedLIST();
  afx_msg void redisplayTreeControl( int index, HTREEITEM parent );
  CTreeCtrl treeControl;
};
