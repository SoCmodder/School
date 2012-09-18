// prog12Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog12.h"
#include "prog12Dlg.h"

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
// CProg12Dlg dialog

CProg12Dlg::CProg12Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg12Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg12Dlg)
	m_input = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg12Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg12Dlg)
	DDX_Control(pDX, IDC_LIST_SUMMERY, m_list);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg12Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg12Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_QUERY, OnButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_BUILD, OnButtonBuild)
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE, OnButtonInitialize)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_SUMMERIZE, OnButtonSummerize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg12Dlg message handlers

BOOL CProg12Dlg::OnInitDialog()
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

void CProg12Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProg12Dlg::OnPaint() 
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
HCURSOR CProg12Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Program 12 (Hash Table)
// Ering Pringle and Joe Wingbermuehle
// This is a program to implement a hash table on disk

// Determine is a string is in the hash table
// PRE: m_input is the string to check
//      m_hash is the hash table
// POST: Displays a message stating whether or not the string is in the table
void CProg12Dlg::OnButtonQuery() {
	UpdateData(TRUE);
	if(m_hash.Query(m_input)) {
		MessageBox("Found");
	} else {
		MessageBox("Not Found");
	}
}

// Build the hash table
// PRE: m_hash is the hash table
//      m_list is the listbox in which to display info
// POST: build the table and display status
void CProg12Dlg::OnButtonBuild() {
	m_list.ResetContent();
	if(!m_hash.Build()) {
		MessageBox("Could not build hash table.");
		m_list.AddString("Error");
	} else {
		m_list.AddString("Build Complete");
	}
	UpdateData();
}

// Intialize the hash table
// PRE: m_hash is the hash table
// POST: m_hash is emptied/initialized
void CProg12Dlg::OnButtonInitialize() {
	m_hash.Initialize();
}

// Insert a string to the hash table
// PRE: m_input is the string to insert
//      m_hash is the hash table
// POST: inserts the string if possible, or displays an error
void CProg12Dlg::OnButtonInsert() {
	if(UpdateData(TRUE)) {

		if(!strlen(m_input)) {
			MessageBox("You didn't enter anything.");
		} else if(!m_hash.Insert(m_input)) {
			MessageBox("Error inserting string.");
		}

		UpdateData(FALSE);
	}
}

// Remove a string from the hash (if possible)
// PRE: m_input is the string to remove
//      m_hash is the hash table from which to remove
// POST: removes the string if possible or displays an error
void CProg12Dlg::OnButtonRemove() {
	if(UpdateData(TRUE)) {
		if(!m_hash.Remove(m_input)) {
			MessageBox("Error: Could not remove string.");
		}
		UpdateData(FALSE);
	}
}

// Display a summery of the hash table
// PRE: m_list is the listbox in which to put the summery
//      m_hash is the hash table
// POST: displays a summery of m_hash in m_list
void CProg12Dlg::OnButtonSummerize() {
	char temp[50];		// string for int->string conversion
	CString str;		// CString for creating display strings

	m_list.ResetContent();

	// Display the number of empty home positions
	itoa(m_hash.CountEmpty(),temp,10);
	str="Empty slots: ";
	str+=temp;
	m_list.AddString(str);

	// Display the number of overflow slots
	itoa(m_hash.CountOverflow(),temp,10);
	str="Overflow: ";
	str+=temp;
	m_list.AddString(str);

	// Display the number of words
	itoa(m_hash.CountWords(),temp,10);
	str="Words: ";
	str+=temp;
	m_list.AddString(str);

	// Dislay the length of the longest chain
	itoa(m_hash.CountLongest(),temp,10);
	str="Longest Chain: ";
	str+=temp;
	m_list.AddString(str);

	// Display the word to start the longest chain
	str="     begun by: ";
	str+=m_hash.GetLongest();
	m_list.AddString(str);

	// Display the number of holes in the overflow area
	itoa(m_hash.CountHoles(),temp,10);
	str="Overflow holes: ";
	str+=temp;
	m_list.AddString(str);
}


