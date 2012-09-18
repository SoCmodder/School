// pegsDlg.h : header file
//

#if !defined(AFX_PEGSDLG_H__3D5FCD56_A52E_11D4_ADF3_005056000000__INCLUDED_)
#define AFX_PEGSDLG_H__3D5FCD56_A52E_11D4_ADF3_005056000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "game.h"

/////////////////////////////////////////////////////////////////////////////
// CPegsDlg dialog

const char SOLVE_STRING[]="*** SOLVE ***";
const char ICON_FILE[]="pegs.exe";
const int ICON_PEG=1;
const int ICON_EMPTY=2;
const int ICON_MOVING=3;
const int ICON_UNUSED=4;
const int iconSize=32;

class CPegsDlg : public CDialog
{
// Construction
public:
	CWnd* m_hWnd;
	CPegsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPegsDlg)
	enum { IDD = IDD_PEGS_DIALOG };
	CListBox	m_moveList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPegsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPegsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuAbout();
	afx_msg void OnButtonSolve();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonHint();
	afx_msg void OnRadioSize5();
	afx_msg void OnRadioSize6();
	afx_msg void OnButtonUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void CheckGameOver();
	void DrawBoard();
	void DisplayMove(int from,int to);
	void OnClickPiece();
	CStatic m_spaces[MAX_BOARD_SIZE];
	int m_moveTo;
	int m_moveFrom;
	int m_empty;
	int m_moveStatus;
	int m_numberPegs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PEGSDLG_H__3D5FCD56_A52E_11D4_ADF3_005056000000__INCLUDED_)
