// HW6aDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HW6a.h"
#include "HW6aDlg.h"

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
// CHW6aDlg dialog

CHW6aDlg::CHW6aDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHW6aDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHW6aDlg)
	m_GPA = 0.0;
	m_Age = 0;
	m_Name = _T("");
	m_messages = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHW6aDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHW6aDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_EDIT_GPA, m_GPA);
	DDX_Text(pDX, IDC_EDIT_Age, m_Age);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_Text(pDX, IDC_EDIT4, m_messages);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHW6aDlg, CDialog)
	//{{AFX_MSG_MAP(CHW6aDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Insert, OnBUTTONInsert)
	ON_BN_CLICKED(IDC_BUTTON_Remove, OnBUTTONRemove)
	ON_BN_CLICKED(IDC_BUTTON_Find, OnBUTTONFind)
	ON_BN_CLICKED(IDC_BUTTON_Full, OnBUTTONFull)
	ON_BN_CLICKED(IDC_BUTTON_Empty, OnBUTTONEmpty)
	ON_BN_CLICKED(IDC_BUTTON_RemoveHead, OnBUTTONRemoveHead)
	ON_BN_CLICKED(IDC_BUTTON_RemoveTail, OnBUTTONRemoveTail)
	ON_BN_CLICKED(IDC_BUTTON_InsertHead, OnBUTTONInsertHead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHW6aDlg message handlers

BOOL CHW6aDlg::OnInitDialog()
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

void CHW6aDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHW6aDlg::OnPaint() 
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
HCURSOR CHW6aDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




// **PRE: ALL BUTTON FUNCTIONS; 
//  An object of type Student has been created

//This function inserts a new node into the list
//Pre: See Above**
//Post: Data is added to the listbox list of data
void CHW6aDlg::OnBUTTONInsert() 
{
	UpdateData (TRUE);
	m_messages = StudentList.insert (m_Name, m_Age, m_GPA);
	m_ListBox.ResetContent ();
	StudentList.Reset ();
	while (StudentList.EOL())
	{
		m_ListBox.AddString (StudentList.GetNext());
	}
	
	
	UpdateData (FALSE);
}
//This function removes all nodes matching the search criteria
//Pre: See Above**
//Post: Data matching the entry in the interface name field will be removed
void CHW6aDlg::OnBUTTONRemove() 
{
	UpdateData (TRUE);
	m_messages = StudentList.remove (m_Name);
	StudentList.Reset ();
	m_ListBox.ResetContent();
	while (StudentList.EOL())
	{
		m_ListBox.AddString (StudentList.GetNext());
	}
	
	UpdateData (FALSE);	
}
//This function returns the number of matches for the search criteria
//Pre: See Above**
//Post: The number of matches found on the data entered in the interface
//      GPA field will be dispayed in the messages field
void CHW6aDlg::OnBUTTONFind() 
{
	UpdateData (TRUE);
	m_messages = StudentList.find (m_GPA);
	UpdateData (FALSE);
}
// Indicates wether the list is full
//Pre: See Above**
//Post: The function will display in the interface message field true if the 
//      dynamic memory is full or false if there is more memory left
void CHW6aDlg::OnBUTTONFull() 
{
	UpdateData (TRUE);
	m_messages = StudentList.full ();
	UpdateData (FALSE);
}
//Indicates wether the list is empty
//Pre:See Above**
//Post: The function will display in the interface message field true if the 
//      list is empty or false if there is data in the list
void CHW6aDlg::OnBUTTONEmpty() 
{
	UpdateData (TRUE);
	m_messages = StudentList.empty ();
	UpdateData (FALSE);
}

void CHW6aDlg::OnBUTTONRemoveHead() 
{
	UpdateData (TRUE);
	m_messages = StudentList.removeHead ();
	StudentList.Reset ();
	m_ListBox.ResetContent();
	while (StudentList.EOL())
	{
		m_ListBox.AddString (StudentList.GetNext());
	}
	
	UpdateData (FALSE);	
}

void CHW6aDlg::OnBUTTONRemoveTail() 
{
	UpdateData (TRUE);
	m_messages = StudentList.removeTail ();
	StudentList.Reset ();
	m_ListBox.ResetContent();
	while (StudentList.EOL())
	{
		m_ListBox.AddString (StudentList.GetNext());
	}
	
	UpdateData (FALSE);	
}

void CHW6aDlg::OnBUTTONInsertHead() 
{
	UpdateData (TRUE);
	m_messages = StudentList.insertHead (m_Name, m_Age, m_GPA);
	m_ListBox.ResetContent ();
	StudentList.Reset ();
	while (StudentList.EOL())
	{
		m_ListBox.AddString (StudentList.GetNext());
	}
	
	
	UpdateData (FALSE);
}
