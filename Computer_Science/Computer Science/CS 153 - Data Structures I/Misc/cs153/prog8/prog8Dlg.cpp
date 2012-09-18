// prog8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog8.h"
#include "prog8Dlg.h"
#include "evaluate.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg8Dlg dialog

CProg8Dlg::CProg8Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg8Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg8Dlg)
	m_alg = _T("");
	m_answer = 0.0;
	m_rpn = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg8Dlg)
	DDX_Text(pDX, IDC_EDIT_ALG, m_alg);
	DDV_MaxChars(pDX, m_alg, 1024);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_answer);
	DDX_Text(pDX, IDC_EDIT_RPN, m_rpn);
	DDV_MaxChars(pDX, m_rpn, 1024);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg8Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg8Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SOLVEALG, OnButtonSolveAlg)
	ON_BN_CLICKED(IDC_BUTTON_SOLVERPN, OnButtonSolveRPN)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg8Dlg message handlers

BOOL CProg8Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProg8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProg8Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProg8Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



// Solve the algebraic expression in m_alg
// PRE: m_alg is the algebraic expression to solve
// POST: Displays the result in m_rpn and m_answer
//       or displays an error message
void CProg8Dlg::OnButtonSolveAlg() {
	char output[MAX_LENGTH+1];
	UpdateData(TRUE);

	// Error if parenthesis are unbalanced
	if(!CheckParens(m_alg)) {
		m_rpn="";
		m_answer=0;
		UpdateData(FALSE);
		MessageBox("Unbalanced parenthesis.");

	// Attempt to solve
	} else if(SolveInfix(m_alg,output)) {
		m_rpn=output;
		UpdateData(FALSE);

	// Give error message if could not solve
	} else {
		m_rpn="";
		m_answer=0;
		UpdateData(FALSE);
		MessageBox("Syntax error.");
	}
}

// Solve the RPN expression in m_rpn
// PRE: m_rpn is the RPN expression to solve
// POST: Displays the result in m_answer or
//       displays an error message
void CProg8Dlg::OnButtonSolveRPN() {
	UpdateData(TRUE);

	// Attempt to solve, give error message on error
	if(!SolvePostfix(m_rpn,m_answer)) {
		MessageBox("Invalid RPN expression.");
		m_answer=0;
	}
	UpdateData(FALSE);
}

