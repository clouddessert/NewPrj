; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNetworkSetting
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "nodeplat.h"
LastPage=0

ClassCount=20
Class1=CAllParamSheet
Class2=CDrawView
Class3=CMainFrame
Class4=CMsgAllSheet
Class5=CMsgCtlView
Class6=CMsgFourthPage
Class7=CMsgFstPage
Class8=CMsgListView
Class9=CMsgSecPage
Class10=CMsgThreePage
Class11=CMySocket
Class12=CNodePlatApp
Class13=CAboutDlg
Class14=CNodePlatDoc
Class15=CNodePlatView
Class16=CParamFstPage
Class17=CParamSecondPage

ResourceCount=15
Resource1=IDD_PARAM_DLG_FIRST
Resource2=IDD_MSG_DLG_FIRST
Resource3=IDD_MSG_DLG_FOURTH
Resource4=IDD_MSG_DLG_FIFTH
Resource5=IDD_ABOUTBOX
Resource6=IDR_MENU1
Resource7=IDD_PARAM_DLG_SECOND
Class18=CMsgSocket
Resource8=IDR_MENU2
Class19=CMsgFifthPage
Resource9=IDD_MSG_DLG_SECOND
Resource10=IDD_MSG_DLG_SEVENTH
Resource11=IDD_MSG_DLG_THREE
Resource12=IDD_MSG_DLG_EIGHTH
Resource13=IDD_MSG_DLG_SIXTH
Resource14=IDR_MAINFRAME
Class20=CNetworkSetting
Resource15=IDD_NETWORKDLG

[CLS:CAllParamSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=AllParamSheet.h
ImplementationFile=AllParamSheet.cpp

[CLS:CDrawView]
Type=0
BaseClass=CView
HeaderFile=DrawView.h
ImplementationFile=DrawView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CDrawView

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CMsgAllSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=MsgAllSheet.h
ImplementationFile=MsgAllSheet.cpp

[CLS:CMsgCtlView]
Type=0
BaseClass=CView
HeaderFile=MsgCtlView.h
ImplementationFile=MsgCtlView.cpp

[CLS:CMsgFourthPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgFourthPage.h
ImplementationFile=MsgFourthPage.cpp
LastObject=CMsgFourthPage

[CLS:CMsgFstPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgFstPage.h
ImplementationFile=MsgFstPage.cpp
LastObject=CMsgFstPage

[CLS:CMsgListView]
Type=0
BaseClass=CView
HeaderFile=MsgListView.h
ImplementationFile=MsgListView.cpp

[CLS:CMsgSecPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgSecPage.h
ImplementationFile=MsgSecPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=IDM_SENDMSG

[CLS:CMsgThreePage]
Type=0
BaseClass=CPropertyPage
HeaderFile=MsgThreePage.h
ImplementationFile=MsgThreePage.cpp
Filter=D
VirtualFilter=idWC

[CLS:CMySocket]
Type=0
BaseClass=CSocket
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp

[CLS:CNodePlatApp]
Type=0
BaseClass=CWinApp
HeaderFile=NodePlat.h
ImplementationFile=NodePlat.cpp
LastObject=CNodePlatApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=NodePlat.cpp
ImplementationFile=NodePlat.cpp
LastObject=CAboutDlg

[CLS:CNodePlatDoc]
Type=0
BaseClass=CDocument
HeaderFile=NodePlatDoc.h
ImplementationFile=NodePlatDoc.cpp
LastObject=CNodePlatDoc
Filter=N
VirtualFilter=DC

[CLS:CNodePlatView]
Type=0
BaseClass=CView
HeaderFile=NodePlatView.h
ImplementationFile=NodePlatView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CNodePlatView

[CLS:CParamFstPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ParamFstPage.h
ImplementationFile=ParamFstPage.cpp

[CLS:CParamSecondPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=ParamSecondPage.h
ImplementationFile=ParamSecondPage.cpp

[DLG:IDD_MSG_DLG_FOURTH]
Type=1
Class=CMsgFourthPage
ControlCount=1
Control1=IDC_LIST_FUSIONMSG,SysListView32,1350631425

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

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

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

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_NETWORKSETTING
Command2=IDM_CONNECTSVR
Command3=ID_APP_ABOUT
CommandCount=3

[CLS:CMsgSocket]
Type=0
HeaderFile=MsgSocket.h
ImplementationFile=MsgSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CMsgSocket

[CLS:CMsgFifthPage]
Type=0
HeaderFile=MsgFifthPage.h
ImplementationFile=MsgFifthPage.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDM_SENDMSG
VirtualFilter=idWC

[DLG:IDD_MSG_DLG_FIFTH]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST_UNICLUSTERMSG,SysListView32,1350631425

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=IDM_SENDMSG
CommandCount=1

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=IDM_SENDMSG
CommandCount=1

[DLG:IDD_MSG_DLG_SIXTH]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST_MulESM,SysListView32,1350631425

[DLG:IDD_MSG_DLG_SEVENTH]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST_MulCOMM,SysListView32,1350631425

[DLG:IDD_MSG_DLG_EIGHTH]
Type=1
Class=?
ControlCount=1
Control1=IDC_LIST_MulTRACE,SysListView32,1350631425

[CLS:CNetworkSetting]
Type=0
HeaderFile=NetworkSetting.h
ImplementationFile=NetworkSetting.cpp
BaseClass=CDialog
Filter=D
LastObject=CNetworkSetting
VirtualFilter=dWC

[DLG:IDD_NETWORKDLG]
Type=1
Class=CNetworkSetting
ControlCount=6
Control1=IDC_SERVERSET,button,1342177287
Control2=IDC_TEAMSET,button,1342177287
Control3=IDC_SERVERIP,static,1342308352
Control4=IDC_SERIP,edit,1350631552
Control5=IDC_TEAMLIST,SysListView32,1350631425
Control6=IDC_BUTTONCLOSE,button,1342242816

