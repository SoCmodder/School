// treeDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "BSTree.h"

// CtreeDlg dialog
class CtreeDlg : public CDialog
{
// Construction
public:
	CtreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TREE_DIALOG };

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
  CString name;
  BSTree tree;
  afx_msg void redisplayTreeControl( NODE* root1, HTREEITEM parent );
  afx_msg void OnBnClickedINSERT();
  afx_msg void OnBnClickedDELETE();
  afx_msg void OnBnClickedFIND();
  afx_msg void OnBnClickedCLEAR();
  afx_msg void OnBnClickedPREORDER();
  afx_msg void OnBnClickedINORDER();
  afx_msg void OnBnClickedPOSTORDER();
  CTreeCtrl treeControl;
  CEdit orderControl;
  CString resultBox;
};
