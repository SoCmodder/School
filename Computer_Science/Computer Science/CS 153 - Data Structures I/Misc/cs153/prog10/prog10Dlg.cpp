// prog10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog10.h"
#include "prog10Dlg.h"
#include "ctree.h"

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
// CProg10Dlg dialog

CProg10Dlg::CProg10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg10Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg10Dlg)
	m_input = 0;
	m_listSelect = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg10Dlg)
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_list);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	DDX_LBIndex(pDX, IDC_LIST_DISPLAY, m_listSelect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg10Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg10Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_PURGE, OnButtonPurge)
	ON_BN_CLICKED(IDC_RADIO_INORDER, OnRadioInorder)
	ON_BN_CLICKED(IDC_RADIO_POSTORDER, OnRadioPostorder)
	ON_BN_CLICKED(IDC_RADIO_PREORDER, OnRadioPreorder)
	ON_LBN_SELCHANGE(IDC_LIST_DISPLAY, OnSelchangeListDisplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg10Dlg message handlers

BOOL CProg10Dlg::OnInitDialog()
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

	m_displayOrder=0;
	this->CheckDlgButton(IDC_RADIO_INORDER,1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProg10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProg10Dlg::OnPaint() 
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
HCURSOR CProg10Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Program 10: Binary tree demonstration
// Erin Pringle and Joe Wingbermuehle
// This is a program to demonstrate a binary tree

// Determine if an item is in the tree
// PRE: m_input is the item to find, m_tree, is the tree in which to look
// POST: Displays a dialog to inform the user if the value is in the tree
void CProg10Dlg::OnButtonFind() {
	char str[50];		// string for displaying
	char temp[20];		// temporary string for int->string conversion

	if(UpdateData(TRUE)) {

		// Set up the beginning of the string
		strcpy(str,"The number ");
		itoa(m_input,temp,10);
		strcat(str,temp);

		// Is the item in the tree?
		if(m_tree.find(m_input)) {
			strcat(str," is in the tree.");
		} else {
			strcat(str," is not in the tree.");
		}

		MessageBox(str);
		UpdateData(FALSE);
	}
}

// Insert an item to the tree
// PRE: m_input is the item to insert, m_tree is the tree
// POST: inserts the item to the tree, or displays an error message
void CProg10Dlg::OnButtonInsert() {
	if(UpdateData(TRUE)) {

		// Insert if possible
		if(!m_tree.insert(m_input)) {
			MessageBox("Out of memory");
		}
		DisplayTree();
	}
}

// Remove an item from the tree
// PRE: m_input is the item to remove, m_tree is the tree
// POST: removes the item from the tree or displays an error message
void CProg10Dlg::OnButtonRemove() {
	if(UpdateData(TRUE)) {

		// Remove if possible
		if(!m_tree.remove(m_input)) {
			OnButtonFind();
		} else {
			DisplayTree();
		}
	}
}

// Remove all items from the tree
// PRE: m_tree is the tree to purge
// POST: all items are removed
void CProg10Dlg::OnButtonPurge() {
	m_tree.purge();
	DisplayTree();
}

// Display the tree in the listbox
// PRE: m_tree is the tree to display, m_list is the CListBox for display
//      m_displayOrder determines the order to display the tree
//      (0-in,1-pre,2-post)
// POST: the tree is displayed in the CListBox
void CProg10Dlg::DisplayTree() {
	UpdateData(TRUE);
	switch(m_displayOrder) {
	case 0:		// Inorder
		m_tree.displayInOrder(m_list);
		break;
	case 1:		// Preorder
		m_tree.displayPreOrder(m_list);
		break;
	case 2:		// Postorder
		m_tree.displayPostOrder(m_list);
		break;
	}
	UpdateData(FALSE);
}

// Change the display order to in order
// PRE: none
// POST: m_displayOrder is the new order (0)
void CProg10Dlg::OnRadioInorder() {
	m_displayOrder=0;
	DisplayTree();
}

// Change the display order to post order
// PRE: none
// POST: m_displayOrder is the new order (2)
void CProg10Dlg::OnRadioPostorder() {
	m_displayOrder=2;
	DisplayTree();
}

// Change the display order to pre order
// PRE: none
// POST: m_displayOrder is the new order (1)
void CProg10Dlg::OnRadioPreorder() {
	m_displayOrder=1;
	DisplayTree();
}

// Select an item in the list box
// PRE: m_list is the CListBox
// POST: m_input is the selected item
void CProg10Dlg::OnSelchangeListDisplay() {
	CString temp;		// CString for retrieving value from list
	UpdateData(TRUE);
	m_list.GetText(m_list.GetCurSel(),temp);
	m_input=atoi(temp);
	UpdateData(FALSE);
}
