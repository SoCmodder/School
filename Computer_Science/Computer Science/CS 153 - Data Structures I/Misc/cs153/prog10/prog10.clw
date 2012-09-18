; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProg10Dlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "prog10.h"

ClassCount=3
Class1=CProg10App
Class2=CProg10Dlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PROG10_DIALOG

[CLS:CProg10App]
Type=0
HeaderFile=prog10.h
ImplementationFile=prog10.cpp
Filter=N

[CLS:CProg10Dlg]
Type=0
HeaderFile=prog10Dlg.h
ImplementationFile=prog10Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_DISPLAY

[CLS:CAboutDlg]
Type=0
HeaderFile=prog10Dlg.h
ImplementationFile=prog10Dlg.cpp
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

[DLG:IDD_PROG10_DIALOG]
Type=1
Class=CProg10Dlg
ControlCount=10
Control1=IDOK,button,1342242816
Control2=IDC_LIST_DISPLAY,listbox,1352745217
Control3=IDC_BUTTON_INSERT,button,1342242817
Control4=IDC_EDIT_INPUT,edit,1350631552
Control5=IDC_BUTTON_FIND,button,1342242816
Control6=IDC_BUTTON_REMOVE,button,1342242816
Control7=IDC_BUTTON_PURGE,button,1342242816
Control8=IDC_RADIO_INORDER,button,1342177289
Control9=IDC_RADIO_PREORDER,button,1342177289
Control10=IDC_RADIO_POSTORDER,button,1342177289

