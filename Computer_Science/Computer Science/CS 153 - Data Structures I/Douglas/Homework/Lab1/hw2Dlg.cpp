// hw2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "hw2.h"
#include "hw2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

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


// Chw2Dlg dialog



Chw2Dlg::Chw2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Chw2Dlg::IDD, pParent)
	, datestring(_T(""))
	, year(0)
	, month(0)
	, day(0)
	, hour(0)
	, minute(0)
	, second(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Chw2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, datestring);
	DDX_Text(pDX, IDC_EDIT2, year);
	DDX_Text(pDX, IDC_EDIT3, month);
	DDX_Text(pDX, IDC_EDIT4, day);
	DDX_Text(pDX, IDC_EDIT5, hour);
	DDX_Text(pDX, IDC_EDIT6, minute);
	DDX_Text(pDX, IDC_EDIT7, second);

}

BEGIN_MESSAGE_MAP(Chw2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// Chw2Dlg message handlers

BOOL Chw2Dlg::OnInitDialog()
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

void Chw2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Chw2Dlg::OnPaint() 
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
HCURSOR Chw2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Chw2Dlg::OnBnClickedButton2()			//Parse
{
	int counter=0;			
	int numslash=0;	//number of slashes counted in the string
	int x=0;         //tmp. variable for range checking
	char * token, * token1, * token2, * token3, * token4, * token5;	//temporary variables
																	//forall 6 parts of
																	//time and date

	bool time=false;				//boolean value representing prescence of time
	bool scds=false;				//boolean representing prescence of seconds
	bool yr=false;					//boolean representing prescence of a year
	bool date=false;				//boolean representing prescence of a date

	char delimit[10]= ":./ ";		//string of delimiters
	
	UpdateData(TRUE);				//Retrieves data from input boxes
	year=0; month=0; day=0; hour=0; minute=0; second=0;	//Changes all variables
														//to 0 so they reset next time data
														//refreshes.

	while (datestring[counter] !=NULL)		//while not at the end of the string
	{
		if(datestring[counter] ==':')		//a : indicates prescence of a time
			time=true;
		if(datestring[counter] == '.')		//a . indicates prescence of a second
			scds=true;
		if(datestring[counter] == '/')	//a / indicates prescence of a date
		{
			numslash++;
			date=true;
		}
	counter++;	
	}

	if (numslash==2)			//2 '/'s indicate that there is a year in the date
		yr=true;

	token=strtok(datestring.GetBuffer(20), delimit);//splits datestring into its parts
	token1=strtok(NULL , delimit);
	token2=strtok(NULL , delimit);
	token3=strtok(NULL, delimit);
	token4=strtok(NULL, delimit);
	token5=strtok(NULL, delimit);
	
	if (date==true)
	{
		x=atoi(token);			//temporary placeholder
		if (x<=12 && x>=1)		//if valid, set = month
			month=x;
		else
			MessageBox("Month", "ERROR: ", MB_OK);		//if invalid, give error
		x=atoi(token1);
		if (x<=31 && x>=1)			//check and set month
			day=x;
		else
			MessageBox("Day", "ERROR: ", MB_OK);
	}
	if (yr==true)				//check and set year
	{
		x=atoi(token2);
		if (x<=9999 && x>=0000)
			year=x;
		else
			MessageBox("Year", "ERROR: ", MB_OK);
	}
	
	if (date==true && yr==true && time==true)
	{
		x=atoi(token3);//check and set hour
		if (x<=23 && x>=0)
			hour=x;
		else
			MessageBox("Hour", "ERROR: ", MB_OK);	
		x=atoi(token4);
		if (x<=59 && x>=0)//check and set minute
			minute=x;
		else
			MessageBox("Month", "ERROR: ", MB_OK);
		if (scds==true)			//check and set seconds
			x=atoi(token5);
			if (x<=59 && x>=0)
				second=x;
			else 
				MessageBox("Second", "ERROR: ", MB_OK);
	}
	
	if (date==true && yr==false && time==true)	//if no year, tokens in different positions
	{											//otherwise, same as above if statement
		x=atoi(token2);
		if (x<=23 && x>=0)
			hour=x;
		else
			MessageBox("Hour", "ERROR: ", MB_OK);		
		x=atoi(token3);
		if (x<=59 && x>=0)
			minute=x;
		else
			MessageBox("Minute", "ERROR: ", MB_OK);
		if (scds==true)			
			x=atoi(token4);
			if (x<=59 && x>=0)
				second=x;
			else
				MessageBox("Second", "ERROR: ", MB_OK);
	}

	if (date==false && time==true)		//if no date, time is first thing
	{
		x=atoi(token);
		if (x<=23 && x>=0)				//check and set hour
			hour=x;
		else
			MessageBox("Hour", "ERROR: ", MB_OK);
		x=atoi(token1);
		if (x<=59 && x>=0)//check and set minute
			minute=x;
		else
			MessageBox("Minute", "ERROR: ", MB_OK);
		if (scds==true)	//check and set second
			x=atoi(token2);
			if (x<=59 && x>=0)
				second=x;
			else
				MessageBox("Second", "ERROR: ", MB_OK);
	}

	datestring=" ";		//make the date input box blank
	UpdateData(FALSE);


}

void Chw2Dlg::OnBnClickedButton1()			//catenate
{
	CString datestring0, datestring1, datestring2, datestring3, datestring4, datestring5; 
		//strings to hold the 6 boxes of data in temporary storage
	
	UpdateData(TRUE);

	itoa(year, datestring0.GetBuffer(4), 10);		//place all dialog variables into
	itoa(month, datestring1.GetBuffer(4), 10);		//temporary string variables.
	itoa(day, datestring2.GetBuffer(4), 10);
	itoa(hour, datestring3.GetBuffer(4), 10);
	itoa(minute, datestring4.GetBuffer(4), 10);
	itoa(second, datestring5.GetBuffer(4), 10);
	datestring0.ReleaseBuffer();					//after using the Null terminated
	datestring1.ReleaseBuffer();					//character array function itoa
	datestring2.ReleaseBuffer();					//buffer must be released prior
	datestring3.ReleaseBuffer();					//to using other CString Functions
	datestring4.ReleaseBuffer();
	datestring5.ReleaseBuffer();

	datestring="";
	
	if (month!=0 && day!=0)				//check for input on month and day
	{
		if (day<=31 && day>=1)			//check range on the day input
		{
			if (month<=12 && month>=1)	//check range on the month
			{
				datestring = datestring1+"/"+datestring2;	//concatenate year and month onto 
				if (year !=0)								//the blank screen
				{
					if (year<=9999 && year>=0)				//check range on year
						datestring+="/"+datestring0;
					else 
						MessageBox("Year", "ERROR: ", MB_OK);	//show error
				}			
			}
			else
				MessageBox("Month", "ERROR: ", MB_OK);
			datestring+=" ";
		}
		else
			MessageBox("Day", "ERROR: ", MB_OK);
	}
	
	
	if (hour!=0 && minute!=0)//check for time input
	{
		if(minute<=59 && minute>=0)			//check minute range
		{
			if (hour<=23 && hour>=0)		//check hour range
			{
				datestring=datestring+datestring3+":"+datestring4;//add on hour and 
																//minute to string
				if (second !=0)
					if (second<=59 && second>=0)//check range of seconds
						datestring=datestring+"."+datestring5;//adds seconds to string
					else
						MessageBox("Second", "ERROR: ", MB_OK);
			}
			else 
				MessageBox("Hour", "ERROR: ", MB_OK);
		}
		else
			MessageBox("Minute", "ERROR: ", MB_OK);
	}

	UpdateData(FALSE);

}

