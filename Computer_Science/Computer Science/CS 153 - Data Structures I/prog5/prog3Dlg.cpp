// prog3Dlg.cpp : implementation file
//
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #5
//This program will insert, find, get, and remove integers from a doubly linked list.  
//Also it will tell if the list is empty or full.

#include "stdafx.h"
#include "prog3.h"
#include "prog3Dlg.h"
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
// CProg3Dlg dialog

CProg3Dlg::CProg3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg3Dlg)
	m_input = 0;
	m_message = _T("");
	testbool = false;
    //}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg3Dlg)
	DDX_Control(pDX, IDC_LIST_OutputListing, m_OutputListing);
	DDX_Text(pDX, IDC_EDIT_Input, m_input);
	DDX_Text(pDX, IDC_EDIT_message, m_message);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg3Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Find, OnBUTTONFind)
	ON_BN_CLICKED(IDC_BUTTON_full, OnBUTTONfull)
	ON_BN_CLICKED(IDC_BUTTON_Empty, OnBUTTONEmpty)
	ON_BN_CLICKED(IDC_BUTTON_Insert_Head, OnBUTTONInsertHead)
	ON_BN_CLICKED(IDC_BUTTON_Insert_Tail, OnButtonInsertTail)
	ON_BN_CLICKED(IDC_BUTTON_Remove_Head, OnBUTTONRemoveHead)
	ON_BN_CLICKED(IDC_BUTTON_Remove_Tail, OnBUTTONRemoveTail)
	ON_BN_CLICKED(IDC_BUTTON_Get_Head, OnBUTTONGetHead)
	ON_BN_CLICKED(IDC_BUTTON_Get_Tail, OnBUTTONGetTail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg message handlers

BOOL CProg3Dlg::OnInitDialog()
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

void CProg3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProg3Dlg::OnPaint() 
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
HCURSOR CProg3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CProg3Dlg::OnBUTTONFind() 
{
    UpdateData(TRUE);
    testbool = my_bag.Find(m_input);
    if (testbool == true)
    {
        m_message = "Found ";
    }
    else
    {
        m_message = "Not Found ";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONfull() 
{
    testbool = my_bag.isFull();
    if (testbool == true)
    {
        m_message = "Bag is Full ";
    }
    else
    {
        m_message = "Bag is not Full ";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONEmpty() 
{
    testbool = my_bag.isEmpty();
    if (testbool == true)
    {
        m_message = "Bag is Empty ";
    }
    else
    {
        m_message = "Bag is not Empty ";
    }
    UpdateData(FALSE);   	
}

void CProg3Dlg::Display()
{
    int iTemp;
    char tempchar[20];
    m_OutputListing.ResetContent();
    my_bag.reset();
    while (!my_bag.EOC())
    {
        iTemp = my_bag.GetNext();
        itoa (iTemp, tempchar, 10);
        m_OutputListing.AddString(tempchar);
    }
}

void CProg3Dlg::OnBUTTONInsertHead() 
{
	
    UpdateData(TRUE);
    testbool = my_bag.InsertHead(m_input);
    if (testbool == true)
    {
        Display();
        m_message = "Inserted ";
    }
    else
    {
        m_message="Bag is full. ";
    }
    UpdateData(FALSE);
}



void CProg3Dlg::OnButtonInsertTail() 
{
    UpdateData(TRUE);
    testbool = my_bag.InsertTail(m_input);
    if (testbool == true)
    {
        Display();
        m_message = "Inserted ";
    }
    else
    {
        m_message = "Bag is Full ";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONRemoveHead()
//If a 0 is removed by this function then an error message will be outputted. 
//However, the number still will be correctly removed.  
{
    UpdateData(TRUE);
    testint = my_bag.RemoveHead();
    Display();
    if (testint != 0)
    {
        m_message="Removed";
    }
    else
    {
        m_message="Not Found! Unable to Remove! ";
    }
    UpdateData(FALSE);
}


void CProg3Dlg::OnBUTTONRemoveTail() 
//If a 0 is removed by this function then an error message will be outputted. 
//However, the number still will be correctly removed.  
{
    UpdateData(TRUE);
    testint = my_bag.RemoveTail();
    Display();
    if (testint != 0)
    {
        m_message="Removed";
    }
    else
    {
        m_message="Not Found! Unable to Remove! ";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONGetHead() 
{
    
    if (my_bag.isEmpty())
    {
        m_message = "Cannot Get Head, Bag is Empty ";
    }
    else
    {
        testint = my_bag.GetHead();
        m_input = testint;
        m_message = "Head Gotten ";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONGetTail() 
{
    
    if (my_bag.isEmpty())
    {
        m_message = "Cannot Get Tail, Bag is Empty ";
    }
    else
    {
        testint = my_bag.GetTail();
        m_input = testint;
        m_message = "Tail Gotten ";
    }
    UpdateData(FALSE);	
}
