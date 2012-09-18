; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProg7Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "prog7.h"

ClassCount=3
Class1=CProg7App
Class2=CProg7Dlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROG7_DIALOG
Resource4=IDR_MENU1

[CLS:CProg7App]
Type=0
HeaderFile=prog7.h
ImplementationFile=prog7.cpp
Filter=N

[CLS:CProg7Dlg]
Type=0
HeaderFile=prog7Dlg.h
ImplementationFile=prog7Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_MENU_NEW

[CLS:CAboutDlg]
Type=0
HeaderFile=prog7Dlg.h
ImplementationFile=prog7Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_PROG7_DIALOG]
Type=1
Class=CProg7Dlg
ControlCount=18
Control1=IDC_LIST_BAG,listbox,1352728833
Control2=IDC_EDIT_INPUT,edit,1350631552
Control3=IDC_EDIT_CURRENT,edit,1350631552
Control4=IDC_BUTTON_SET,button,1342242816
Control5=IDC_BUTTON_INSERTHEAD,button,1342242816
Control6=IDC_BUTTON_INSERTTAIL,button,1342242816
Control7=IDC_BUTTON_INSERTBEFORE,button,1342242816
Control8=IDC_BUTTON_INSERTAFTER,button,1342242816
Control9=IDC_BUTTON_REMOVEHEAD,button,1342242816
Control10=IDC_BUTTON_REMOVETAIL,button,1342242816
Control11=IDC_BUTTON_REMOVECURRENT,button,1342242816
Control12=IDC_BUTTON_REMOVE,button,1342242816
Control13=IDC_BUTTON_FIND,button,1342242816
Control14=IDC_BUTTON_RESET,button,1342242816
Control15=IDC_BUTTON_EMPTY,button,1342242816
Control16=IDC_BUTTON_FULL,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=CProg7Dlg
Command1=IDC_MENU_NEW
Command2=IDC_MENU_EXIT
Command3=IDC_MENU_ABOUT
CommandCount=3

