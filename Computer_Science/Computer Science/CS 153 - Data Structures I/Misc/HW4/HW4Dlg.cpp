// HW4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "HW4.h"
#include "HW4Dlg.h"

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
// CHW4Dlg dialog

CHW4Dlg::CHW4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHW4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHW4Dlg)
	m_Messages = _T("");
	m_Input = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHW4Dlg)
	DDX_Control(pDX, IDC_LIST_ListBox, m_ListBox);
	DDX_Text(pDX, IDC_EDIT_Messages, m_Messages);
	DDX_Text(pDX, IDC_EDIT_Input, m_Input);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHW4Dlg, CDialog)
	//{{AFX_MSG_MAP(CHW4Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Insert, OnBUTTONInsert)
	ON_BN_CLICKED(IDC_BUTTON_Find, OnBUTTONFind)
	ON_BN_CLICKED(IDC_BUTTON_Remove, OnBUTTONRemove)
	ON_BN_CLICKED(IDC_BUTTON_Full, OnBUTTONFull)
	ON_BN_CLICKED(IDC_BUTTON_Empty, OnBUTTONEmpty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHW4Dlg message handlers

BOOL CHW4Dlg::OnInitDialog()
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

void CHW4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHW4Dlg::OnPaint() 
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
HCURSOR CHW4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}





void CHW4Dlg::OnBUTTONInsert()	// Inserts the user CString into ListBox 
{
	UpdateData (TRUE);
	if (m_Input != "")
	{		
		m_Messages = ListBox.insert (m_Input);
		ListBox.display (m_ListBox);
	}
	else
	{
		m_Messages = "Hey thats not nice, DON'T DO THAT!!!";
	}
	UpdateData (FALSE);

	
}

void CHW4Dlg::OnBUTTONFind()	// Tells if the user CString is already in the ListBox
{
	UpdateData (TRUE);
	m_Messages = ListBox.find (m_Input);
	UpdateData (FALSE);
}

void CHW4Dlg::OnBUTTONRemove()	// Removes the user CString from the ListBox
{
	UpdateData (TRUE);
	if (m_Input != "")
	{
		m_Messages = ListBox.remove (m_Input);
		ListBox.display (m_ListBox);
	}
	else
	{
		m_Messages = "Enter a value";
	}
	UpdateData (FALSE);	

}

void CHW4Dlg::OnBUTTONFull()	// Returns if the ListBox is full or not
{
	UpdateData (TRUE);
	m_Messages = ListBox.full ();
	UpdateData (FALSE);

}

void CHW4Dlg::OnBUTTONEmpty()	// Returns if the ListBox is empty or not
{
	UpdateData (TRUE);
	m_Messages = ListBox.empty ();
	UpdateData (FALSE);

}
