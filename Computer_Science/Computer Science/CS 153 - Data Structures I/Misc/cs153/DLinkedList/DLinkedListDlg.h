// DLinkedListDlg.h : header file
//

#if !defined(AFX_DLINKEDLISTDLG_H__9D94FB36_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
#define AFX_DLINKEDLISTDLG_H__9D94FB36_90C8_11D4_ADCA_005056EC703B__INCLUDED_

#include "DList.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDLinkedListDlg dialog

class CDLinkedListDlg : public CDialog
{
// Construction
public:
	CDLinkedListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDLinkedListDlg)
	enum { IDD = IDD_DLINKEDLIST_DIALOG };
	CListBox	m_list;
	CString	m_input;
	CString	m_fileName;
	int		m_selection;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLinkedListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDLinkedListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonEmpty();
	afx_msg void OnButtonFull();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnSelchangeListDisp();
	afx_msg void OnButtonAppend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_modified;
	void DisplayList(void);
	CDList m_bag;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLINKEDLISTDLG_H__9D94FB36_90C8_11D4_ADCA_005056EC703B__INCLUDED_)
