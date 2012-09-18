// prog2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog2.h"
#include "prog2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProg2Dlg dialog

CProg2Dlg::CProg2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg2Dlg)
	m_streetInt = 0;
	m_streetStr = _T("");
	m_zip = 0;
	m_state = _T("");
	m_city = _T("");
	m_address = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg2Dlg)
	DDX_Text(pDX, IDC_EDIT_STREETINT, m_streetInt);
	DDX_Text(pDX, IDC_EDIT_STREETSTR, m_streetStr);
	DDX_Text(pDX, IDC_EDIT_ZIP, m_zip);
	DDX_Text(pDX, IDC_EDIT_STATE, m_state);
	DDX_Text(pDX, IDC_EDIT_CITY, m_city);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg2Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CAT, OnButtonCat)
	ON_BN_CLICKED(IDC_BUTTON_PARSE, OnButtonParse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg2Dlg message handlers

BOOL CProg2Dlg::OnInitDialog()
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

void CProg2Dlg::OnPaint() 
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
HCURSOR CProg2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Erin Pringle and Joe Wingbermuehle
// Assignment 2
// Concatenate and Parse an address

const int MAX_LENGTH=1024;	// Max characters in an address field

// Remove leading and trailing spaces
// PRE: s->string from which to remove spaces
// POST: excess spaces are removed from s and one is appended
void RemoveExcess(char *s) {
	int x;		// index variable
	int len;	// length of the string
	for(len=0;s[len];len++);	// len=string length
	while(s[0]==' ') {			// Remove leading spaces
		for(x=len;x;s[x--]=s[x-1]);
		--len;
	}
	while(s[len]==' ') {	// Remove Trailing spaces
		s[len]=0;
		--len;
	}
	s[len]=' ';
	s[len+1]=0;
}

// Concatenate the address (called when the Concatenate button is pressed)
// PRE: address is in the first 5 edit boxes
// POST: m_address is the concatenated address (displayed in an edit box)
void CProg2Dlg::OnButtonCat()
{
	char workStr[50];			// string used to convert from char* to int
	char output[MAX_LENGTH+1];	// string to hold the concatenated string
	UpdateData(TRUE);
	
	// get the value of the first address box
	itoa(m_streetInt,workStr,10);
	strcpy(output,workStr);
	RemoveExcess(output);			// Remove leading and trailing spaces

	// append the street name
	strcat(output,m_streetStr);
	RemoveExcess(output);

	// append the city
	strcat(output,m_city);
	RemoveExcess(output);

	// append the state
	strcat(output,m_state);
	RemoveExcess(output);

	// append the zip code
	itoa(m_zip,workStr,10);
	strcat(output,workStr);
	m_address=output;

	UpdateData(FALSE);
}

// Break apart an address into it's parts
// PRE: address is in the big edit box (m_address)
// POST: the 5 edit boxes for the parts of the address
//       have the address
void CProg2Dlg::OnButtonParse() 
{
	char workStr[MAX_LENGTH+1];		// temporary string for holding the full address
	char *s;		// pointer used to pass the appropriate parts of the string above
					// into atoi
	UpdateData(TRUE);

	// copy the address to workStr
	strcpy(workStr,m_address);

	// set m_streetInt if it exists in m_address
	s=strtok(workStr," ");
	if(s)
		m_streetInt=atoi(s);
	else
		m_streetInt=0;

	// get the street name
	m_streetStr=strtok(NULL," ");
	m_city=strtok(NULL," ");		// get the city name
	m_state=strtok(NULL," ");		// get the state name

	// get the zip code (if possible)
	s=strtok(NULL," ");
	if(s)
		m_zip=atoi(s);
	else
		m_zip=0;

	UpdateData(FALSE);
}
