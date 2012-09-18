// prog11Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog11.h"
#include "prog11Dlg.h"
#include "CBST.h"
#include "cdata.h"

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
// CProg11Dlg dialog

CProg11Dlg::CProg11Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg11Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg11Dlg)
	m_listSelect = -1;
	m_input = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg11Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg11Dlg)
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_list);
	DDX_LBIndex(pDX, IDC_LIST_DISPLAY, m_listSelect);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg11Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg11Dlg)
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
// CProg11Dlg message handlers

BOOL CProg11Dlg::OnInitDialog()
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

	m_displayOrder=INORDER;
	this->CheckDlgButton(IDC_RADIO_INORDER,1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProg11Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProg11Dlg::OnPaint() 
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
HCURSOR CProg11Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Program 11: Binary tree demonstration
// Erin Pringle and Joe Wingbermuehle
// This is a program to demonstrate a binary tree

// Determine if an item is in the tree
// PRE: m_input is the item to find, m_tree, is the tree in which to look
// POST: Displays a dialog to inform the user if the value is in the tree
void CProg11Dlg::OnButtonFind() {
	CString str;		// string for displaying

	if(UpdateData(TRUE)) {

		// Set up the beginning of the string
		str="The value \""+m_input;

		CData input(m_input);

		// Is the item in the tree?
		if(m_tree.Find(input)) {
			str+="\" is in the tree.";
		} else {
			str+="\" is not in the tree.";
		}

		MessageBox(str);
		UpdateData(FALSE);
	}
}

// Insert an item to the tree
// PRE: m_input is the item to insert, m_tree is the tree
// POST: inserts the item to the tree, or displays an error message
void CProg11Dlg::OnButtonInsert() {
	if(UpdateData(TRUE)) {

		CData *input;	// CData object to insert

		// Insert if possible
		if(!strlen(m_input)) {
			MessageBox("You didn't enter anything!");
		} else {
			bool memoryError=false;
			try {
				input=new CData(m_input);
				if(!m_tree.Insert(*input)) {
					memoryError=true;
				}
			}
			catch(...) {
				memoryError=true;
			}

			// Give error message on error
			if(memoryError) {
				delete input;
				MessageBox("Out of memory");
			}
		}
		DisplayTree();
	}
}

// Remove an item from the tree
// PRE: m_input is the item to remove, m_tree is the tree
// POST: removes the item from the tree or displays an error message
void CProg11Dlg::OnButtonRemove() {
	if(UpdateData(TRUE)) {

		CData input(m_input);

		// Remove if possible
		if(!m_tree.Remove(input)) {
			OnButtonFind();
		} else {
			DisplayTree();
		}
	}
}

// Remove all items from the tree
// PRE: m_tree is the tree to purge
// POST: all items are removed
void CProg11Dlg::OnButtonPurge() {
	m_tree.Purge();
	DisplayTree();
}

// Display the tree in the listbox
// PRE: m_tree is the tree to display, m_list is the CListBox for display
//      m_displayOrder determines the order to display the tree
// POST: the tree is displayed in the CListBox
void CProg11Dlg::DisplayTree() {
	m_list.ResetContent();

	// select which order to display
	switch(m_displayOrder) {
	case INORDER:		// Inorder
		m_tree.DisplayInOrder(m_list);
		break;
	case PREORDER:		// Preorder
		m_tree.DisplayPreOrder(m_list);
		break;
	case POSTORDER:		// Postorder
		m_tree.DisplayPostOrder(m_list);
		break;
	}
	UpdateData(FALSE);
}

// Change the display order to in order
// PRE: none
// POST: m_displayOrder is the new order
void CProg11Dlg::OnRadioInorder() {
	m_displayOrder=INORDER;
	DisplayTree();
}

// Change the display order to post order
// PRE: none
// POST: m_displayOrder is the new order
void CProg11Dlg::OnRadioPostorder() {
	m_displayOrder=POSTORDER;
	DisplayTree();
}

// Change the display order to pre order
// PRE: none
// POST: m_displayOrder is the new order
void CProg11Dlg::OnRadioPreorder() {
	m_displayOrder=PREORDER;
	DisplayTree();
}

// Select an item in the list box
// PRE: m_list is the CListBox
// POST: m_input is the selected item
void CProg11Dlg::OnSelchangeListDisplay() {
	UpdateData(TRUE);
	m_list.GetText(m_list.GetCurSel(),m_input);
	UpdateData(FALSE);
}
