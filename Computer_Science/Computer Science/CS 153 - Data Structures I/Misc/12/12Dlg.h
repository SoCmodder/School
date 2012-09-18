// 12Dlg.h : header file
//

#if !defined(AFX_12DLG_H__5B49C693_69D2_41EF_A12B_BE47CE854F67__INCLUDED_)
#define AFX_12DLG_H__5B49C693_69D2_41EF_A12B_BE47CE854F67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy12Dlg dialog

class CMy12Dlg : public CDialog
{
// Construction
public:
	CMy12Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy12Dlg)
	enum { IDD = IDD_MY12_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy12Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy12Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_12DLG_H__5B49C693_69D2_41EF_A12B_BE47CE854F67__INCLUDED_)
