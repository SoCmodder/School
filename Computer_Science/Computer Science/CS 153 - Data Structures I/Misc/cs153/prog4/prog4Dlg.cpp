// prog4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog4.h"
#include "prog4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProg4Dlg dialog

CProg4Dlg::CProg4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg4Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg4Dlg)
	m_value = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg4Dlg)
	DDX_Control(pDX, IDC_LIST_BAG, m_bag);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg4Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg4Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_ISFULL, OnButtonIsfull)
	ON_BN_CLICKED(IDC_BUTTON_EMPTY, OnButtonEmpty)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg4Dlg message handlers

BOOL CProg4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProg4Dlg::OnPaint() 
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
HCURSOR CProg4Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Assignment 4
// Erin Pringle and Joe Wingbermuehle
// This is a program to maintain a list of numbers in a "bag."

const int MAX_LENGTH=50;	// Max length for certain display strings

// Insert an item to the bag/list (called when the "Insert" button is pressed)
// PRE: m_value holds the value to insert
// POST: The value is inserted or an error message is given
void CProg4Dlg::OnButtonInsert() {
	if(UpdateData(TRUE)) {
		// Add the item and display the bag, if possible
		if(bag.insert(m_value)) {
			DisplayBag();
		} else {
			MessageBox("Error: Bag is full.",NULL,MB_OK);
		}
	}
	UpdateData(FALSE);
}

// Remove an item from the bag/list (called when the "Remove" button is pressed)
// PRE: m_value is the value to remove from the bag (only the first occurance will be removed)
// POST: The value is removed if it exists, otherwise an error message is given
void CProg4Dlg::OnButtonRemove() {
	if(UpdateData(TRUE)) {
		// Remove the item and display the bag, if possible
		if(bag.remove(m_value)) {
			DisplayBag();
		} else {
			MessageBox("Error: Item not found.",NULL,MB_OK);
		}
	}
	UpdateData(FALSE);
}

// Give a message indicating whether or not a value is in the bag (the "Find" button)
// PRE: m_value is the value to find
// POST: Gives a message telling the user if the value is in the bag
void CProg4Dlg::OnButtonFind() {
	char str[MAX_LENGTH+1];		// The string that will be displayed
	char temp[20];				// A string used for int-to-ascii conversion

	if(UpdateData(TRUE)) {
		// Create the message
		strcpy(str,"The number ");
		strcat(str,itoa(m_value,temp,10));
		if(bag.find(m_value)) {
			strcat(str," is in the bag.");
		} else {
			strcat(str," is not in the bag.");
		}
		// Display the message
		MessageBox(str,NULL,MB_OK);
	}
	UpdateData(FALSE);
}

// Display a message indicating whether or not the bag is full (the "Full?" button)
// PRE: None
// POST: Displays a message indicating whether or not the bag is full
void CProg4Dlg::OnButtonIsfull() {
	if(bag.isFull()) {
		MessageBox("The bag is full.",NULL,MB_OK);
	} else {
		MessageBox("The bag is not full.",NULL,MB_OK);
	}
}

// Display a message indicating whether or not the bag is empty (the "Empty?" button)
// PRE: none
// POST: Displays a message indicating whether or not the bag is empty
void CProg4Dlg::OnButtonEmpty() {
	if(bag.isEmpty()) {
		MessageBox("The bag is empty.",NULL,MB_OK);
	} else {
		MessageBox("The bag is not empty.",NULL,MB_OK);
	}
}

// Display the contents of the bag in the list box
// PRE: None
// POST: The contents (if any) of the bag are displayed in the list box
void CProg4Dlg::DisplayBag() {
	char str[20];			// String used for int-to-ascii conversion

	m_bag.ResetContent();	// Clear the contents of the list box

	// Display the values
	for(int x=0;x<bag.numberElements();x++) {
		m_bag.AddString(itoa(bag.element(x),str,10));
	}
}
