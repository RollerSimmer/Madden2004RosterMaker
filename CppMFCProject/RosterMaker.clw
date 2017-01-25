; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRosterMakerDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RosterMaker.h"

ClassCount=4
Class1=CRosterMakerApp
Class2=CRosterMakerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CEdit_Append
Resource3=IDD_ROSTERMAKER_DIALOG

[CLS:CRosterMakerApp]
Type=0
HeaderFile=RosterMaker.h
ImplementationFile=RosterMaker.cpp
Filter=N

[CLS:CRosterMakerDlg]
Type=0
HeaderFile=RosterMakerDlg.h
ImplementationFile=RosterMakerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC__CHECK__USE_TEMPLATE

[CLS:CAboutDlg]
Type=0
HeaderFile=RosterMakerDlg.h
ImplementationFile=RosterMakerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ROSTERMAKER_DIALOG]
Type=1
Class=CRosterMakerDlg
ControlCount=17
Control1=IDC_STATIC,static,1342308352
Control2=IDC__ROS_NAME,edit,1350631552
Control3=IDC__ROS_BROWSE,button,1342246657
Control4=IDC_STATIC,static,1208090624
Control5=IDC__CSV_NAME,edit,1216413824
Control6=IDC__CSV_BROWSE,button,1208028928
Control7=IDC_STATIC,static,1208090624
Control8=IDC_DELIM,edit,1216413824
Control9=IDC__IMPORT_TO_ROS,button,1208028928
Control10=IDC__EXPORT_TO_CSV,button,1208028928
Control11=IDC_STATIC,static,1342308352
Control12=IDC_OUTPUT,edit,1353777284
Control13=IDC__AUTO_ROSTER,button,1342246656
Control14=IDC_STATIC,static,1342308352
Control15=IDC__TEMPLATE_NAME,edit,1350631552
Control16=IDC__TEMPLATE_BROWSE,button,1342246656
Control17=IDC__CHECK__USE_TEMPLATE,button,1342242819

[CLS:CEdit_Append]
Type=0
HeaderFile=Edit_Append.h
ImplementationFile=Edit_Append.cpp
BaseClass=CEdit
Filter=W

