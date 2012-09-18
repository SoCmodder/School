// prog7Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog7.h"
#include "prog7Dlg.h"

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
// CProg7Dlg dialog

CProg7Dlg::CProg7Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg7Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg7Dlg)
	m_input = _T("");
	m_current = 0;
	m_selection = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg7Dlg)
	DDX_Control(pDX, IDC_LIST_BAG, m_list);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Text(pDX, IDC_EDIT_CURRENT, m_current);
	DDX_LBIndex(pDX, IDC_LIST_BAG, m_selection);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg7Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg7Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_INSERTAFTER, OnButtonInsertAfter)
	ON_BN_CLICKED(IDC_BUTTON_INSERTBEFORE, OnButtonInsertBefore)
	ON_BN_CLICKED(IDC_BUTTON_INSERTHEAD, OnButtonInsertHead)
	ON_BN_CLICKED(IDC_BUTTON_INSERTTAIL, OnButtonInsertTail)
	ON_BN_CLICKED(IDC_BUTTON_REMOVECURRENT, OnButtonRemoveCurrent)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEHEAD, OnButtonRemoveHead)
	ON_BN_CLICKED(IDC_BUTTON_REMOVETAIL, OnButtonRemoveTail)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	ON_BN_CLICKED(IDC_BUTTON_FULL, OnButtonFull)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_LBN_SELCHANGE(IDC_LIST_BAG, OnSelchangeListBag)
	ON_COMMAND(IDC_MENU_EXIT, OnMenuExit)
	ON_COMMAND(IDC_MENU_ABOUT, OnMenuAbout)
	ON_COMMAND(IDC_MENU_NEW, OnMenuNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg7Dlg message handlers

BOOL CProg7Dlg::OnInitDialog()
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

void CProg7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProg7Dlg::OnPaint() 
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
HCURSOR CProg7Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Assignment 7
// Erin Pringle and Joe Wingbermuehle
// This is a program to demonstrate the functions of a doubly linked list.

// Give a message saying whether m_input is in m_bag after the current position
// PRE: m_input is the string to find
// POST: gives a message saying whether or not the value is in the list after
//       the current position
void CProg7Dlg::OnButtonFind() {
	UpdateData(TRUE);
	char *beginning="The string \"";				// Beginning of the message
	char *negativeEnd="\" is not at or after the current position.";	// "not there" ending
	char *positiveEnd="\" is in the list.";			// "in list" ending

	// Make length the length of the largest possible output
	int length=strlen(beginning)+strlen(negativeEnd)+strlen(m_input);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_input is found
	strcpy(output,beginning);
	strcat(output,m_input);
	if(m_bag.find(m_input)) {
		strcat(output,positiveEnd);
	} else {
		strcat(output,negativeEnd);
	}

	MessageBox(output);
	UpdateData(FALSE);
	delete [] output;
}

// Insert an item after the current position
// PRE: m_input is the value to insert
// POST: the item is inserted to m_bag if possible
void CProg7Dlg::OnButtonInsertAfter() {
	UpdateData(TRUE);

	// Insert if possible, otherwise give error
	if(CheckInput() && !m_bag.insertAfter(m_input)) {
		MessageBox("Could not insert the item.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Insert an item before the current position
// PRE: m_input is the value to insert
// POST: the item is inserted to m_bag if possible
void CProg7Dlg::OnButtonInsertBefore() {
	UpdateData(TRUE);

	// Insert if possible, otherwise give error
	if(CheckInput() && !m_bag.insertBefore(m_input)) {
		MessageBox("Could not insert the item.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Insert an item (m_input) to the start of m_bag
// PRE: m_input is the string to insert.
// POST: m_input is inserted into m_bag if possible, otherwise an
//		 error message is displayed.
void CProg7Dlg::OnButtonInsertHead() {
	UpdateData(TRUE);

	// Insert if possible, else give error
	if(CheckInput() && !m_bag.insertHead(m_input)) {
		MessageBox("Could not insert value.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Append an item (m_input) to the end of m_bag
// PRE: m_input is the string to insert.
// POST: m_input is appended to m_bag if possible, otherwise an
//       error message is displayed.
void CProg7Dlg::OnButtonInsertTail() {
	UpdateData(TRUE);

	// Append if possible, else give error
	if(CheckInput() && !m_bag.insertTail(m_input)) {
		MessageBox("Could not insert value.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Remove the item at the current position if possible
// PRE: the current position is the item to remove
// POST: removes the item at the current position and resets
//		 the current position, if possible, or gives error
void CProg7Dlg::OnButtonRemoveCurrent() {
	UpdateData(TRUE);

	// Remove if possible, otherwise give error
	if(m_bag.removeCurrent()=="") {
		MessageBox("Could not remove the current item.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Remove the first item from m_bag if possible
// PRE: none
// POST: removes the first item from m_bag if possible,
//		 else gives an error
void CProg7Dlg::OnButtonRemoveHead() {
	UpdateData(TRUE);

	// Remove if possible, else give error
	if(m_bag.removeHead()=="") {
		MessageBox("Could not remove the first item.");
	}

	DisplayList();
	UpdateData(FALSE);	
}

// Remove the last item from m_bag if possible
// PRE: none
// POST: removes teh last item from m_bag if possible,
//       else gives an error
void CProg7Dlg::OnButtonRemoveTail() {
	UpdateData(TRUE);

	if(m_bag.removeTail()=="") {
		MessageBox("Could not remove the last item.");
	}

	DisplayList();
	UpdateData(FALSE);
}

// Reset the current index to 0
// PRE: none
// POST: the current index is set to 0, m_input & m_selection are updated
void CProg7Dlg::OnButtonReset() {
	UpdateData(TRUE);
	m_bag.reset();
	m_current=m_selection=m_bag.currentNumber();
	m_input=m_bag.getCurrent();
	UpdateData(FALSE);
}

// Display the list (m_bag) in the listbox
// PRE: m_bag is a valid CDList
// POST: Display the contents of m_bag in the listbox
void CProg7Dlg::DisplayList() {
	UpdateData(TRUE);

	m_list.ResetContent();
	m_bag.reset();

	// Insert the items to the list box
	while(!m_bag.EOL()) {
		m_list.AddString(m_bag.getCurrent());
		m_bag.getNext();
	}

	// Update the highlight and current index
	m_selection=m_current=m_bag.currentNumber();

	UpdateData(FALSE);
}

// Check if m_bag is empty
// PRE: none
// POST: Display a message showing whether or not m_bag is empty.
void CProg7Dlg::OnButtonEmpty() {
	char *beginning="The list is ";		// Beginning of the message
	char *negative="not ";				// "not" for if the bag is not empty
	char *ending="empty.";				// End of the message

	// Make length the length of the largest possible output
	int length=strlen(beginning)+strlen(negative)+strlen(ending);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_bag is empty
	strcpy(output,beginning);
	if(!m_bag.empty()) {
		strcat(output,negative);
	}
	strcat(output,ending);

	MessageBox(output,NULL,MB_OK);
	delete [] output;
}

// Check if m_bag is full
// PRE: none
// POST: Display a message showing whether or not m_bag is full.
void CProg7Dlg::OnButtonFull() {
	char *beginning="The list is ";		// Beginning of the message
	char *negative="not ";				// "not" in case m_bag is full
	char *ending="full.";				// End of the message

	// Make length the length of the largest possible ouput
	int length=strlen(beginning)+strlen(negative)+strlen(ending);

	// Allocate memory for the output
	char *output=new char[length+1];

	// Create the display string based on whether or not m_bag is full
	strcpy(output,beginning);
	if(!m_bag.full()) {
		strcat(output,negative);
	}
	strcat(output,ending);

	MessageBox(output,NULL,MB_OK);
	delete [] output;
}

// Remove an item (m_input) from m_bag, starting search from current
// PRE: m_input is the item to remove.
// POST: Removes the item from m_bag if possible, otherwise gives
//		 an error message.
void CProg7Dlg::OnButtonRemove() {
	UpdateData(TRUE);

	// Remove if possible, else give error
	if(!m_bag.remove(m_input)) {
		OnButtonFind();		// use OnButtonFind's error message
	}

	DisplayList();
	UpdateData(FALSE);
}

// Set the current position if possible
// PRE: m_current is the item to select
// POST: changes the current postion to m_current or gives an error
void CProg7Dlg::OnButtonSet() {
	UpdateData(TRUE);
	if(m_current<0 || m_current>=m_bag.numberElements()) {
		MessageBox("Index out of range.");
	} else {
		m_bag[m_current];
		m_selection=m_current;
	}
	UpdateData(FALSE);
}

// Set the current position to the highlighted item in the list
// PRE: m_selection is the item to select
// POST: updates m_current and changes the current position to m_selection
void CProg7Dlg::OnSelchangeListBag() {
	UpdateData(TRUE);
	m_current=m_selection;
	m_input=m_bag[m_current];
	UpdateData(FALSE);
}

// Exit the program
// PRE: none
// POST: quits the program
void CProg7Dlg::OnMenuExit() {
	CDialog::OnOK();
}

// Display the about dialog
// PRE: none
// POST: the about dialog is displayed
void CProg7Dlg::OnMenuAbout() {
	CAboutDlg dlg;
	dlg.DoModal();
}

// Clear the list
// PRE: none
// POST: all items are removed from the bag
void CProg7Dlg::OnMenuNew() {
	m_bag.purge();
	DisplayList();
}

// Make sure the input (m_input) is valid
// PRE: m_input is the value to check
// POST: returns 1 if valid, otherwise gives error and returns 0
bool CProg7Dlg::CheckInput() {
	if(!strlen(m_input)) {
		MessageBox("Invalid string.");
		return 0;
	}
	return 1;
}
