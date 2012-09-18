// virusDlg.cpp : implementation file
//Author: Brent Powers
//Date: 2-17-05

#include "stdafx.h"
#include "virus.h"
#include "virusDlg.h"
#include "virusprime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About


virus thevirus;
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


// CvirusDlg dialog



CvirusDlg::CvirusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvirusDlg::IDD, pParent)
	, input_name(_T(""))
	, input_age(0)
	, input_vacinated(FALSE)
	, obox(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_name);
	DDV_MaxChars(pDX, input_name, 40);
	DDX_Text(pDX, IDC_EDIT2, input_age);
	DDV_MinMaxInt(pDX, input_age, 0, 200);
	DDX_Check(pDX, IDC_CHECK1, input_vacinated);
	DDX_Control(pDX, IDC_LIST1, live_box);
	DDX_Control(pDX, IDC_LIST2, dead_box);
	DDX_Text(pDX, IDC_EDIT3, obox);
}

BEGIN_MESSAGE_MAP(CvirusDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
END_MESSAGE_MAP()


// CvirusDlg message handlers

BOOL CvirusDlg::OnInitDialog()
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

void CvirusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CvirusDlg::OnPaint() 
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
HCURSOR CvirusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*
Function: add

Description: Function to  add a new node to the linked list

PreCondition: data is changes, and there is a valid input for all variables

PostCondition: people are entered into the linked list and then displayed in the live box

*/
void CvirusDlg::OnBnClickedButton1()//add buttong
{
	if(UpdateData(TRUE))//things are updated
	{
		if(input_name=="")//if not user is told
		{
			obox="Please Enter a Valid Input";
		}
		if(input_name!="")
		{
			thevirus.insert(input_name,input_age,input_vacinated);//users are inserted
			display(live_box);//changes are displayed
			input_name="";//reseting the input boxes
			input_age=0;
            obox="Person added successfully";//output successfull add
			input_vacinated=FALSE;
		}}
	UpdateData(FALSE);//update the screen
}
/*
Function infect

Description: if the user exists it infects that user and then infects every person after that one that isn't themselves vaccinated.

Precondition: Valid inputs are given in the input boxes

Postcondition: Infected people are moved to the dead box

*/

void CvirusDlg::OnBnClickedButton2()//infect button
{
	if (UpdateData(TRUE))
	{
		if(input_name=="")//check for some input
		{
			obox="Please Enter a Valid Input";
		}
		if(input_name!="")
		{
			thevirus.infect(obox,dead_box,input_name);//infects the people
			display(live_box);//displays the changes
			input_name="";//resets values
			input_age=0;
			input_vacinated=FALSE;
		}
	}
	UpdateData(FALSE);//update screen
}
/*
Function: vacinate

Description: this function takes only valid input from the user and sends the persons name to the vacinate function, then it reports back on the success of the vaccinatoin

PreCondition: valid input for the name

PostCondition: the vacination status for a person has been changed
*/		


void CvirusDlg::OnBnClickedButton3()//vaccinate button
{
	if (UpdateData(TRUE))
	{
		if(input_name=="")//no blank entry
		{
			obox="Please Enter a Valid Input";
		}
		if(input_name!="")//if stuff entered
		{
			thevirus.vacinate(input_name,obox);//actually vaccination process
			display(live_box);//update the living box
			input_name="";//reset boxs
			input_age=0;
			input_vacinated=FALSE;
		}
	
	}
	
	UpdateData(FALSE);//send to gui
    }
/*
Function: armageddon

Description: this function initializes the armageddon function and then updates the user on results and then displays the updated boxs

Precondition: none

Postcondition: All people in live box are transfered to dead box


*/
void CvirusDlg::OnBnClickedButton4()//armageddon buttong
{
	thevirus.clear(dead_box,obox);//kill function
	display(live_box);
	UpdateData(FALSE);//send to gui
}
/*
Function: display

Description: this function goes through the linked list and displays each nodes data in the live box with a certain format

PreCondition: the list must be correctly linked, and everything must point to the right spots

PostCondition: All the info is outoutted to the live box.
*/

void CvirusDlg::display(CListBox& lbox)
{
	lbox.ResetContent();//reset box
	node* temp=thevirus.get_next();
	CString vacine="";
	char convert[20]="";
	while(!thevirus.EOL())
	{
		if(temp->vacinated==TRUE)//stuff for vaccinated
			{
				vacine="Yes";
			}else
			{
				vacine="No";//stuff for not vaccinated
			}
		_itoa(temp->age, convert, 10);//putting strings together
		lbox.AddString("Name: "+temp->name+" Age: "+convert);
		lbox.AddString("Vaccinated: "+vacine);//puttin stuff together
		lbox.AddString("********************");
		temp=thevirus.get_next();
	}
}
/*
Function: get next

Description: this function goes to the place where the current pointer points and displays that data and moves the pointer to the next node.

PreCondtion: valid linking of nodes

PostCondition: the info is printed out to the user on the person where the pointer current is pointing and then it is forwarded to the next node

*/
void CvirusDlg::OnBnClickedButton5()//get next button
{
	node* temp=thevirus.get_next();//moving stuff
	if(temp==NULL)//if end
	{
		obox="End of List";
		UpdateData(FALSE);
		return;
	}
	char storage[80]="";
	CString vacine="";
	char convert[20]="";
	if(temp->vacinated==TRUE)//stuff for vaccinated
			{
				vacine="Yes";
			}else
			{
				vacine="No";//stuff for not vaccinated
			}
	_itoa(temp->age, convert, 10);//putting strings together
	strncat(storage,"Name: ",9);
	strncat(storage,temp->name,40);
	strncat(storage," Age: ",7);
	strncat(storage,convert,5);
	strncat(storage," Vaccinated: ",15);//puttin stuff together
	strncat(storage,vacine,5);
	obox=storage;
	
	UpdateData(FALSE);
}
/*
Function: End of List

Description: this function determines if the current pointer is at the end of the list and then lets the user know

Precondition: properly linked list and a valid node pointed to by the current pointer

PostCondition: The condition of the current pointer is outputted

*/
void CvirusDlg::OnBnClickedButton6()//EOL button
{
	bool temp=thevirus.EOL();
	if(temp==TRUE)//at the end
	{
		obox="The current pointer is at the end of the list";
	}
	if(temp==FALSE)//not
	{
		obox="The current pointer is not at the end of the list";
	}
	UpdateData(FALSE);//back to gui
}
/*
Function: reset

Description: resets the current pointer position to the top of the list

Precondition: none

Postcondition: the current pointer is placed at the beginning of the list
*/
void CvirusDlg::OnBnClickedButton7()//reset button
{
	thevirus.reset;
	obox="The current pointer has been reset.";
	UpdateData(FALSE);

}
