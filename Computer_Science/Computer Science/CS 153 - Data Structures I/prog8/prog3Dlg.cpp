//Filename: prog3Dlg.cpp
//Programmers: Derek Buchheit, Pei-Te Chung
//Program Assignment #8
//This program will convert a mathmatical infix expression to postfix form. 
//It was also evaluate the answer. 


#include <string.h>
#include "Stack.h"
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
	m_conv_input = _T("");
	m_eval_input = _T("");
	m_result = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProg3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProg3Dlg)
	DDX_Text(pDX, IDC_EDIT_Convert, m_conv_input);
	DDX_Text(pDX, IDC_EDIT_Evaluate, m_eval_input);
	DDX_Text(pDX, IDC_EDIT_Result, m_result);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProg3Dlg, CDialog)
	//{{AFX_MSG_MAP(CProg3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Convert, OnBUTTONConvert)
	ON_BN_CLICKED(IDC_BUTTON_Evaluate, OnBUTTONEvaluate)
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


void CProg3Dlg::OnBUTTONConvert() 
{
    if(UpdateData(TRUE) && Error_Balanced())

	{

		char * temp = new char[m_conv_input.GetLength() +1]; //Stores the string for strtok

		char * NoSpaces = new char[m_conv_input.GetLength() +1];//stores the tokened string

		char * token = NULL; //holds the value returned by strtok

		const char Seps[] = " ";//The seperations that strtok looks for

		CString  input;//Used to hold the current value

		int count = 0; //A counter variable to access the array

		

        m_eval_input.Empty(); //Empty the postfix box.

		

		strcpy(NoSpaces,"");//Initialize no spaces to null

		strcpy(temp,m_conv_input);//copy contents of Infix to temp

		token = strtok(temp,Seps);



		while(token != NULL)//Removes spaces from the infix expression

		{

			strcat(NoSpaces,token);

			token = strtok(NULL,Seps);

			

		}

				

		while(NoSpaces[count] != '\0')//Searches through the tokenized array

		{

			input = NoSpaces[count];//Assisgns Input to current value

			

			if(input == "(")//Determine if left parenthesis and add it to stack

			{

                my_stack.Push(input);

				count++;

			}

			else if(input == "*" || input == "/")//Determine if operation

			{

				if(my_stack.Top() == "+" || my_stack.Top() == "-")//determine if higher precidence

				{

					my_stack.Push(input);

					m_eval_input = m_eval_input + " ";

					count++;

				}

				else if(my_stack.Top() == "(")//Determine if left parenthesis

				{

					my_stack.Push(input);

					m_eval_input = m_eval_input+ " ";

					count++;

				}

				else if(!my_stack.isEmpty())//Determine if stack is empty

				{

					m_eval_input = m_eval_input + my_stack.Pop();

					m_eval_input = m_eval_input + " ";

				}

				else//Stack is empty

				{

					my_stack.Push(input);

					m_eval_input = m_eval_input + " ";

					count++;

				}

			}

			else if(input == "+" || input == "-")//Determine if input is an operation

			{

				if(my_stack.Top() != "(" && !my_stack.isEmpty())//determine if parenthesis

				{

					m_eval_input = m_eval_input + " ";

					m_eval_input = m_eval_input + my_stack.Pop();					

				}

				else//Parenthesis found, pop and discard

				{

					my_stack.Push(input);

					m_eval_input = m_eval_input + " ";

					count++;

				}

			}

			else if(input == ")")//Determine if right parenthesis

			{

				if(my_stack.Top() != "(")//Determine when left parenthesis is found

				{

                    m_eval_input = m_eval_input + " ";

					m_eval_input = m_eval_input + my_stack.Pop();

				}

				else//Parenthesis found

				{

					my_stack.Pop();

					count++;

				}

			}

			else//Input is a number or letter

			{

				m_eval_input = m_eval_input + input;

				count++;

			}

		

			

		}

		while(!my_stack.isEmpty())//Pop remaining operations

		{

			m_eval_input = m_eval_input + " " + my_stack.Pop();

		}



		UpdateData(FALSE);

		delete  [] temp;//delete allocated memory

		delete  [] NoSpaces;

	}

	else//Infix expression is invalid

	{

		m_eval_input = "";

		MessageBox("The Infix expression MUST be a valid expression!","Error",MB_OK);

		UpdateData(FALSE);



	}



}

void CProg3Dlg::OnBUTTONEvaluate() 

{



	if(UpdateData(TRUE))

	{

		int num1, num2;//stores numbers converted from ascii

		char * token;//stores tokened values

		const char Seps[] = { " " };//Holds seperation values

		char * temp = new char[m_eval_input.GetLength() +1];//holds Postfix expression

		char result[100];//stores return value



		strcpy(temp,m_eval_input);//Copy postfix expression to temp



		token = strtok(temp,Seps);



		while(token != NULL)//tokenize array

		{

			if(strcmp(token,"+") == 0 && !my_stack.isEmpty())//determine if operation

			{

				num1 = atoi(my_stack.Pop());

				num2 = atoi(my_stack.Pop());

				itoa((num1+num2),result,10);

				my_stack.Push(result);

			}

			else if(strcmp(token,"-") == 0 && !my_stack.isEmpty())//determine if operation

			{

				num2 = atoi(my_stack.Pop());

				num1 = atoi(my_stack.Pop());

				itoa((num1-num2),result,10);

				my_stack.Push(result);

			}

			else if(strcmp(token,"*") == 0 && !my_stack.isEmpty())//determine if operation

			{

				num1 = atoi(my_stack.Pop());

				num2 = atoi(my_stack.Pop());

				itoa((num1*num2),result,10);

				my_stack.Push(result);

			}

			else if(strcmp(token,"/") == 0 && !my_stack.isEmpty())//determine if operation

			{

				num2 = atoi(my_stack.Pop());

				num1 = atoi(my_stack.Pop());

				if(num2 != 0)

				{

					itoa((num1/num2),result,10);

					my_stack.Push(result);

				}

				else

				{

					my_stack.Push("");

					MessageBox("Can not divide by zero!","Error",MB_OK);

					break;

				}



			}

			else//Not an operation, so push number on stack

			{

				my_stack.Push(token);

			}

			

			token = strtok(NULL,Seps);//Get a new token value

		}

		m_result = my_stack.Pop();//Store result in evaluate



		



		while(!my_stack.isEmpty())//The expression was invalid and the stack is emptied.

		{

			my_stack.Pop();

		}



		delete [] temp;//delete allocated memory

		UpdateData(FALSE);

	}



}

bool CProg3Dlg::Error_Balanced()

{

	char * temp = new char[m_conv_input.GetLength() + 1];//stores Infix value

	int place = 0;//counter for array

	int count = 0;//counter for parenthesis





	strcpy(temp,m_conv_input);



	while(temp[place] != '\0')//determine when end of array is reached

	{

		if(temp[place] == '(')//left parenthesis found, add one to count

			count++;

		else if(temp[place] == ')')//right parenthesis found, subtract one from count

			count--;



		place++;

	}

	

	delete [] temp;//delete allocated memory



	if(count == 0)//determine if balanced parenthesis

	{

		return TRUE;

	}

	else

	{

		return FALSE;

	}



}
