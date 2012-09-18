; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDLinkedListDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DLinkedList.h"

ClassCount=3
Class1=CDLinkedListApp
Class2=CDLinkedListDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DLINKEDLIST_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CDLinkedListApp]
Type=0
HeaderFile=DLinkedList.h
ImplementationFile=DLinkedList.cpp
Filter=N

[CLS:CDLinkedListDlg]
Type=0
HeaderFile=DLinkedListDlg.h
ImplementationFile=DLinkedListDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_DISP

[CLS:CAboutDlg]
Type=0
HeaderFile=DLinkedListDlg.h
ImplementationFile=DLinkedListDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC_BY,static,1342308352

[DLG:IDD_DLINKEDLIST_DIALOG]
Type=1
Class=CDLinkedListDlg
ControlCount=10
Control1=IDC_LIST_DISP,listbox,1352728833
Control2=IDC_EDIT_INPUT,edit,1350631552
Control3=IDC_BUTTON_INSERT,button,1342242816
Control4=IDC_BUTTON_REMOVE,button,1342242816
Control5=IDC_BUTTON_FIND,button,1342242816
Control6=IDC_BUTTON_EMPTY,button,1342242816
Control7=IDC_BUTTON_FULL,button,1342242816
Control8=IDC_EDIT_FILENAME,edit,1350631552
Control9=IDC_STATIC_FNAME,static,1342308352
Control10=IDC_BUTTON_APPEND,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CDLinkedListDlg
Command1=ID_MENU_NEW
Command2=ID_MENU_OPEN
Command3=ID_MENU_SAVE
Command4=ID_MENU_EXIT
Command5=ID_MENU_ABOUT
CommandCount=5

