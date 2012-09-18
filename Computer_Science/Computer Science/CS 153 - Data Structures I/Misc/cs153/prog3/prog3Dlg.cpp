// prog3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "prog3.h"
#include "prog3Dlg.h"
#include "Vect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg dialog

CProg3Dlg::CProg3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProg3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProg3Dlg)
	m_input1 = _T("");
	m_input2 = _T("");
	m_answer = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg3Dlg)
	DDX_Text(pDX, IDC_EDIT_INPUT1, m_input1);
	DDV_MaxChars(pDX, m_input1, 256);
	DDX_Text(pDX, IDC_EDIT_INPUT2, m_input2);
	DDV_MaxChars(pDX, m_input2, 256);
	DDX_Text(pDX, IDC_EDIT_ANSWER, m_answer);
	DDV_MaxChars(pDX, m_answer, 256);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg3Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg3Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLUS, OnButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, OnButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_PRODUCT, OnButtonProduct)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProg3Dlg message handlers

BOOL CProg3Dlg::OnInitDialog()
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

// Add the vectors in the first two edit boxes and put the result in the third.
// This is run when the user clicks the "+" button.
// PRE: The first two edit boxes hold the vectors to be added.
// POST: The third edit box holds the answer (or nothing if there was an error in input).
void CProg3Dlg::OnButtonPlus() {
	UpdateData(TRUE);
	CVect input1=m_input1;		// Create CVects for the inputs
	CVect input2=m_input2;

	// Check for errors
	if(Vertify(input1,input2,this)) {
		CVect ans;
		ans=input1+input2;			// Do the addition
		m_answer=ans.toString();	// Display the answer
	} else {
		m_answer="";
	}
	UpdateData(FALSE);
}

// Subtract the vectors in the first two edit boxes and put the result in the third.
// This is run when the user clicks the "-" button.
// PRE: The first two edit boxes hold the vectors to be subtracted (INPUT1-INPUT2).
// POST: The third edit box holds the answer (or nothing if there was an error in input).
void CProg3Dlg::OnButtonMinus() {
	UpdateData(TRUE);
	CVect input1=m_input1;		// Create CVects for the inputs
	CVect input2=m_input2;

	// Check for errors
	if(Vertify(input1,input2,this)) {
		CVect ans;
		ans=input1-input2;			// Do the subtraction
		m_answer=ans.toString();	// Display the answer
	} else {
		m_answer="";
	}
	UpdateData(FALSE);
}

// Find the dot product of the vectors in the first two edit boxes and place the result in the third.
// This is run when the user clicks the "*" button.
// PRE: The first two edit boxes hold the vectors of which to take the dot product.
// POST: The third edit box holds the answer (or nothing if there was an error in input).
void CProg3Dlg::OnButtonProduct() {
	UpdateData(TRUE);
	CVect input1=m_input1;
	CVect input2=m_input2;		// Create CVects for the inputs

	// Check for errors
	if(Vertify(input1,input2,this)) {
		CVect ans;
		ans=input1*input2;			// Calculate the dot product
		m_answer=ans.toString();	// Display the answer
	} else {
		m_answer="";
	}
	UpdateData(FALSE);
}

int CProg3Dlg::Vertify(const CVect &a, const CVect &b, CWnd* w) const {
	if(a.length()==b.length()) {
		if(a.length()) {
			return 1;
		} else {
			w->MessageBox("Error: Vector size is zero.",NULL,MB_OK);
			return 0;
		}
	} else {
		w->MessageBox("Error: Vector sizes do not match.",NULL,MB_OK);
		return 0;
	}
}
