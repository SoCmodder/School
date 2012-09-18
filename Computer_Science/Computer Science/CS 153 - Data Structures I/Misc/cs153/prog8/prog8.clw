; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProg8Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "prog8.h"

ClassCount=3
Class1=CProg8App
Class2=CProg8Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROG8_DIALOG

[CLS:CProg8App]
Type=0
HeaderFile=prog8.h
ImplementationFile=prog8.cpp
Filter=N

[CLS:CProg8Dlg]
Type=0
HeaderFile=prog8Dlg.h
ImplementationFile=prog8Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_ALG

[CLS:CAboutDlg]
Type=0
HeaderFile=prog8Dlg.h
ImplementationFile=prog8Dlg.cpp
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

[DLG:IDD_PROG8_DIALOG]
Type=1
Class=CProg8Dlg
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_ALG,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_RPN,edit,1350631552
Control6=IDC_EDIT_ANSWER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BUTTON_SOLVEALG,button,1342242816
Control9=IDC_BUTTON_SOLVERPN,button,1342242816

