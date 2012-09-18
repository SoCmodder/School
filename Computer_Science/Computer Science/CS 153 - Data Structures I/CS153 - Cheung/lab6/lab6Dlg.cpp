/*
File: lab6Dlg.cpp
Author: Brent Powers
Description: Controls the program
Date: 3-10-05
*/

// lab6Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab6.h"
#include "lab6Dlg.h"
#include "converter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
stack thestack;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Clab6Dlg dialog



Clab6Dlg::Clab6Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Clab6Dlg::IDD, pParent)
	, ifix(_T(""))
	, pfix(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ifix);
	DDV_MaxChars(pDX, ifix, 40);
	DDX_Text(pDX, IDC_EDIT2, pfix);
}

BEGIN_MESSAGE_MAP(Clab6Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// Clab6Dlg message handlers

BOOL Clab6Dlg::OnInitDialog()
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

void Clab6Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab6Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Clab6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
Function: convert button
Description: when button clicked it runs the convert function
Precondition: Good infix expression entered in the gui
Postcondition: a pfix expression is generated
*/
void Clab6Dlg::OnBnClickedButton1()//convert button
{
	if(UpdateData(TRUE))//send data from box to program
	{
		convert(ifix,pfix);//runn the converter program
		UpdateData(FALSE);//send that shit back to the GUI
	}

}
/*
Function: void convert(CString readin, CString& readout)
Description: Converts a InFix expressiont to PostFix, if not a valid input then lets user know
PreCondition: correctly entered infix expression with no irregular charactors and balanced ()
PostCondition: a valid postfix expression or error message that bad input
*/
void Clab6Dlg::convert(CString readin, CString& readout)
{
	thestack.empty();//reset the stack and shit
	char output[50]="";
   	char single=' ';//evaluation charactor
	int count=0;//count
	int counter2=0;
	int counter3=0;
	int parencount=0;
	while(single!='\0')
	{
		single=readin[count];
		if (((single >= 'a') && (single <= 'z')) ||//if letter or number inputted
           ((single >= 'A') && (single <= 'Z')) ||
           ((single >= '0') && (single <= '9')))
		{
			output[counter2]=single;//send to output
			counter2++;
		}else if (single == '(')//if open parentesses
		{
			thestack.push(single);//pust to the stack
			counter3++;//augments counters
			parencount++;
		}else if ((single=='*')||(single=='/')||(single=='+')||(single=='-'))//if opperator
		{
			if(thestack.top()=='(')//top of array is (
			{
				thestack.push(single);
			}else if(((single=='*')&&(thestack.top()=='+'))||//case that operators are 
				((single=='*')&&(thestack.top()=='-'))||//in order of presidence
				((single=='/')&&(thestack.top()=='+'))||
				((single=='/')&&(thestack.top()=='-')))
			{
				thestack.push(single);
				counter3++;
			}else if (((single=='+')&&(thestack.top()=='+'))||//not in proper presidence
				((single=='+')&&(thestack.top()=='-'))||
				((single=='-')&&(thestack.top()=='-'))||
				((single=='+')&&(thestack.top()=='+'))||
				((single=='-')&&(thestack.top()=='+'))||
				((single=='*')&&(thestack.top()=='*'))||
				((single=='*')&&(thestack.top()=='/'))||
				((single=='/')&&(thestack.top()=='/'))||
				((single=='/')&&(thestack.top()=='*'))||
				((single=='+')&&(thestack.top()=='*'))||
				((single=='+')&&(thestack.top()=='/'))||
				((single=='-')&&(thestack.top()=='/'))||
				((single=='-')&&(thestack.top()=='*')))				
			{
				do{
					output[counter2]=thestack.pop();//a pop then a push
					counter3--;
					counter2++;
				}while(((single=='+')&&(thestack.top()=='+'))||//not in proper presidence
				((single=='+')&&(thestack.top()=='-'))||
				((single=='-')&&(thestack.top()=='-'))||
				((single=='+')&&(thestack.top()=='+'))||
				((single=='-')&&(thestack.top()=='+'))||
				((single=='*')&&(thestack.top()=='*'))||
				((single=='*')&&(thestack.top()=='/'))||
				((single=='/')&&(thestack.top()=='/'))||
				((single=='/')&&(thestack.top()=='*'))||
				((single=='+')&&(thestack.top()=='*'))||
				((single=='+')&&(thestack.top()=='/'))||
				((single=='-')&&(thestack.top()=='/'))||
				((single=='-')&&(thestack.top()=='*')));
				thestack.push(single);
				counter3++;
			}
			
			else//everything else just push it
			{
				thestack.push(single);
				counter3++;
			}
		}else if (single==')')//close parentesise
		{
			if(parencount<1)
			{
				MessageBox("Un-ballanced infix expression, please correct");
				readout="Infix unballanced";
				return;
			}

			parencount--;
			while(thestack.top()!='(')//continue outputting untill parent balanced
			{
				output[counter2]=thestack.pop();
				counter2++;//counter fun
				counter3--;
			}
			char temp=thestack.pop();
			
		}else//if no charactor matches the above if statements, then it is bad
		{
			MessageBox("Invalid charactor located in infix");
			readout="Invalid input in infix";
			return;
		}
		count++;
		single=readin[count];
	}
	while(counter3>=1) //output all left in the stack
	{
		output[counter2]=thestack.pop();
		counter2++;
		counter3--;
	}
	readout=output;
	if(parencount!=0)//checking for ballanced parrentheseis
	{
        MessageBox("Un-ballanced infix expression, please correct");
		readout="Infix unballanced";
	}	

}