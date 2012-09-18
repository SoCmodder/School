; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPegsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "pegs.h"
LastPage=0

ClassCount=3
Class1=CPegsApp
Class2=CAboutDlg
Class3=CPegsDlg

ResourceCount=3
Resource1=IDD_PEGS_DIALOG
Resource2=IDD_ABOUTBOX
Resource3=IDR_MENU1

[CLS:CPegsApp]
Type=0
BaseClass=CWinApp
HeaderFile=pegs.h
ImplementationFile=pegs.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=pegsDlg.cpp
ImplementationFile=pegsDlg.cpp

[CLS:CPegsDlg]
Type=0
BaseClass=CDialog
HeaderFile=pegsDlg.h
ImplementationFile=pegsDlg.cpp
LastObject=IDC_RADIO_SIZE5
Filter=D
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_PEGS_DIALOG]
Type=1
Class=CPegsDlg
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_BUTTON_NEW,button,1342242816
Control3=IDC_BUTTON_SELECT,button,1342242816
Control4=IDC_BUTTON_HINT,button,1342242816
Control5=IDC_BUTTON_UNDO,button,1342242816
Control6=IDC_BUTTON_SOLVE,button,1342242816
Control7=IDC_RADIO_SIZE5,button,1342177289
Control8=IDC_RADIO_SIZE6,button,1342177289
Control9=IDC_STATIC,button,1342177287
Control10=IDC_LIST_MOVES,listbox,1352745217

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDC_MENU_NEW
Command2=IDC_MENU_EXIT
Command3=IDC_MENU_ABOUT
CommandCount=3

