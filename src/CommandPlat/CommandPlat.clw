; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCommandPlatView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "commandplat.h"
LastPage=0

ClassCount=16
Class1=CAllParamSheet
Class2=CCommandPlatApp
Class3=CAboutDlg
Class4=CCommandPlatDoc
Class5=CCommandPlatView
Class6=CLanStatusView
Class7=CMainFrame
Class8=CMessageView
Class9=CMsgAllSheet
Class10=CMsgFstPage
Class11=CMsgSecPage
Class12=CMsgThreePage
Class13=CMySocket
Class14=CParamFstPage
Class15=CParamSecondPage
Class16=CParamSetView

ResourceCount=7
Resource1=IDD_MSG_DLG_FIRST
Resource2=IDD_PARAM_DLG_FIRST
Resource3=IDD_ABOUTBOX
Resource4=IDD_MSG_DLG_THREE
Resource5=IDD_MSG_DLG_SECOND
Resource6=IDR_MAINFRAME
Resource7=IDD_PARAM_DLG_SECOND

[CLS:CAllParamSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=AllParamSheet.h
ImplementationFile=AllParamSheet.cpp

[CLS:CCommandPlatApp]
Type=0
BaseClass=CWinApp
HeaderFile=CommandPlat.h
ImplementationFile=CommandPlat.cpp
Filter=N
VirtualFilter=AC
LastObject=CCommandPlatApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=CommandPlat.cpp
ImplementationFile=CommandPlat.cpp
LastObject=IDM_SHOW_MSG

[CLS:CCommandPlatDoc]
Type=0
BaseClass=CDocument
HeaderFile=CommandPlatDoc.h
ImplementationFile=CommandPlatDoc.cpp

[CLS:CCommandPlatView]
Type=0
BaseClass=CView
HeaderFile=CommandPlatView.h
ImplementationFile=CommandPlatView.cpp
LastObject=CCommandPlatView
Filter=C
VirtualFilter=VWC

[CLS:CLanStatusView]
Type=0
BaseClass=CView
HeaderFile=LanStatusView.h
ImplementationFile=LanStatusView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CLanStatusView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMessageView]
Type=0
BaseClass=CView
HeaderFile=MessageView.h
ImplementationFile=MessageView.cpp

[CLS:CMsgAllSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=MsgAllSheet.h
ImplementationFile=MsgAllSheet.cpp

[CLS:CMsgFstPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgFstPage.h
ImplementationFile=MsgFstPage.cpp

[CLS:CMsgSecPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgSecPage.h
ImplementationFile=MsgSecPage.cpp

[CLS:CMsgThreePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgThreePage.h
ImplementationFile=MsgThreePage.cpp

[CLS:CMySocket]
Type=0
BaseClass=CAsyncSocket
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp

[CLS:CParamFstPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ParamFstPage.h
ImplementationFile=ParamFstPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CParamFstPage

[CLS:CParamSecondPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ParamSecondPage.h
ImplementationFile=ParamSecondPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CParamSecondPage

[CLS:CParamSetView]
Type=0
BaseClass=CView
HeaderFile=ParamSetView.h
ImplementationFile=ParamSetView.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MSG_DLG_FIRST]
Type=1
Class=CMsgFstPage
ControlCount=1
Control1=IDC_LIST_ESM,SysListView32,1350631425

[DLG:IDD_MSG_DLG_SECOND]
Type=1
Class=CMsgSecPage
ControlCount=1
Control1=IDC_LIST_COMMUNICATE,SysListView32,1350631425

[DLG:IDD_MSG_DLG_THREE]
Type=1
Class=CMsgThreePage
ControlCount=1
Control1=IDC_LIST_TRACE,SysListView32,1350631425

[DLG:IDD_PARAM_DLG_FIRST]
Type=1
Class=CParamFstPage
ControlCount=1
Control1=IDC_OURS_TREE,SysTreeView32,1350631431

[DLG:IDD_PARAM_DLG_SECOND]
Type=1
Class=CParamSecondPage
ControlCount=1
Control1=IDC_ENEMY_TREE,SysTreeView32,1350631431

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_CREATE_ST
Command2=IDM_CHIOSE_ST
Command3=IDM_SHOW_MSG
Command4=IDM_START_JQ
Command5=IDM_STOP_JQ
Command6=IDM_TARGET_LIB
Command7=IDM_RADAR_LIB
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

