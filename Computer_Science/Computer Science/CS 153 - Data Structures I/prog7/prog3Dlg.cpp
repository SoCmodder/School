// prog3Dlg.cpp : implementation file
//
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #7
//This program will insert, find, get, and remove CStrings from a doubly linked list.  
//Also it will tell if the list is empty or full.

#include "stdafx.h"
#include "prog3.h"
#include "prog3Dlg.h"
#include "DNode.h"
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
	m_message = _T("");
	testbool = false;
	m_input = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg3Dlg)
	DDX_Control(pDX, IDC_LIST_OutputListing, m_OutputListing);
	DDX_Text(pDX, IDC_EDIT_message, m_message);
	DDX_Text(pDX, IDC_EDIT_Input, m_input);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg3Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Empty, OnBUTTONEmpty)
	ON_BN_CLICKED(IDC_BUTTON_Insert_Head, OnBUTTONInsertHead)
	ON_BN_CLICKED(IDC_BUTTON_Get_Head, OnBUTTONGetHead)
	ON_BN_CLICKED(IDC_BUTTON_Get_Tail, OnBUTTONGetTail)
	ON_BN_CLICKED(IDC_BUTTON_full, OnBUTTONfull)
	ON_BN_CLICKED(IDC_BUTTON_Find, OnBUTTONFind)
	ON_BN_CLICKED(IDC_BUTTON_Insert_Tail, OnBUTTONInsertTail)
	ON_BN_CLICKED(IDC_BUTTON_Remove_Head, OnBUTTONRemoveHead)
	ON_BN_CLICKED(IDC_BUTTON_Remove_Tail, OnBUTTONRemoveTail)
	ON_BN_CLICKED(IDC_Button_Remove, OnButtonRemove)
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
    DNode* p_temp;
    p_temp = new DNode;
    p_temp ->cs_val= m_input;
    testbool = my_bag.Find(p_temp);
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
    CString cTemp;
    m_OutputListing.ResetContent();
    my_bag.reset();
    while (!my_bag.EOC())
    {
        cTemp = ((DNode *)my_bag.GetNext())->cs_val;
        m_OutputListing.AddString(cTemp);
    }
}

void CProg3Dlg::OnBUTTONInsertHead() 
{
	
    UpdateData(TRUE);
    DNode * p_temp;
    p_temp = new DNode;
    p_temp -> cs_val = m_input;
    testbool = my_bag.InsertHead(p_temp);
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



void CProg3Dlg::OnBUTTONInsertTail() 
{
    UpdateData(TRUE);
    DNode * p_temp;
    p_temp = new DNode;
    p_temp -> cs_val = m_input;
    testbool = my_bag.InsertTail(p_temp);
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
{
    UpdateData(TRUE);
    CString temp;
    temp = my_bag.RemoveHead();
    Display();
    if (temp != "false")
    {
        m_message="Removed " + temp;
    }
    else
    {
        m_message="Cannot Remove Head";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONRemoveTail() 
  
{
    UpdateData(TRUE);
    CString temp;
    temp = my_bag.RemoveTail();
    Display();
    if (temp != "false")
    {
        m_message="Removed " + temp;
    }
    else
    {
        m_message="Cannot Remove Tail";
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONGetHead() 
{
    Node * p_temp;
    if (my_bag.isEmpty())
    {
        m_message = "Cannot Get Head, Bag is Empty ";
    }
    else
    {
        m_message = "Head is ";
        p_temp = my_bag.GetHead();
        m_message += (((DNode*)p_temp) ->cs_val);
    }
    UpdateData(FALSE);
}

void CProg3Dlg::OnBUTTONGetTail() 
{
    Node * p_temp;
    if (my_bag.isEmpty())
    {
        m_message = "Cannot Get Tail, Bag is Empty ";
    }
    else
    {
        m_message = "Tail is ";
        p_temp = my_bag.GetTail();
        m_message += (((DNode*)p_temp) ->cs_val);
        
    }
    UpdateData(FALSE);	
}



void CProg3Dlg::OnButtonRemove() 
{
    UpdateData(TRUE);
	DNode * p_temp;
    p_temp = new DNode;
    p_temp -> cs_val = m_input;
    m_message = my_bag.Remove(p_temp);
	Display();
    UpdateData(FALSE);
}
