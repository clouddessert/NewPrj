// NodePlat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "NodePlatDoc.h"
#include "NodePlatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//接受socket
//MySocket* m_ReceiveSocket = NULL;
/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp

BEGIN_MESSAGE_MAP(CNodePlatApp, CWinApp)
	//{{AFX_MSG_MAP(CNodePlatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp construction

CNodePlatApp::CNodePlatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	// 初始化临界区
	::InitializeCriticalSection(&g_cs);	
	
	m_ESM_Dat.clear();
	m_Comm_Dat.clear();
	m_Trace_Dat.clear();

	m_RecvMsg.stComm.clear();
	m_RecvMsg.stEsm.clear();
	m_RecvMsg.stTrace.clear();

	hESM_wmd = NULL;
	hCOMM_wmd = NULL;
	hTRACE_wmd = NULL;
	hSigOut_wnd = NULL;

//	pOutPt = NULL;

	pXview = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNodePlatApp object

CNodePlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp initialization

BOOL CNodePlatApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox("SOCKET 初始化失败");
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CNodePlatDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CNodePlatView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	// The one and only window has been initialized, so show and update it.
	//设置标题
	m_pMainWnd->SetWindowText("联合识别与态势评估仿真平台");

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CNodePlatApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp message handlers

void CNodePlatApp::ServerCreate(void)
{
	//创建p2p模式socket
	theApp.m_P2PSocket = new CMsgSocket();
	theApp.m_P2PSocket->Socket();
	
	theApp.m_P2PSocket->Bind(P2P_SERVER_PORT);
	//开始监听
	theApp.m_P2PSocket->Listen();

}

void CNodePlatApp::ServerShutDown(void)
{
	for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
	{
		//关闭客户端连接
		theApp.m_pClient->second->Close();
		//释放客户端资源
		delete (theApp.m_pClient->second);
		theApp.m_pClient->second = NULL;
	}
	//客户端清空
	theApp.m_ClientMap.clear();
	
	//关闭监听
	theApp.m_P2PSocket->Close();
	//释放监听端资源
	delete theApp.m_P2PSocket;
	theApp.m_P2PSocket = NULL;
}

void CNodePlatApp::ClientAccept(void)
{
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMySocket();
	//接受连接
	theApp.m_P2PSocket->Accept(*(theApp.pClient));
	
	theApp.pClient->GetPeerName(strTmp, nPort);
	//转换IP地址，作为标志
	dwClientIP = inet_addr(strTmp.GetBuffer(0));
	strTmp.ReleaseBuffer();
	
	//存入map
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.m_ClientMap.insert(map<DWORD, CMySocket*>::value_type(dwClientIP, theApp.pClient));
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CNodePlatApp::ClientClose(void* pContext)
{
	CMySocket* pSk = (CMySocket*)pContext;
	
	::EnterCriticalSection(&(theApp.g_cs));
	for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
	{
		if (pSk == theApp.m_pClient->second)
		{
			//关闭SOCKET
			theApp.m_pClient->second->Close();
			//删除关闭的资源
			theApp.m_ClientMap.erase(theApp.m_pClient);
			break;
		}
		else
		{
			 //继续
		}
	}
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CNodePlatApp::ReceiveFromClient(void)
{
	//1\接收 别人的请求数据 	//4\接收邻舰发送来的查找到的返回信息
	//考虑请求是结构体组成的容器 接收后，将发送过来的含数组的容器转成含容器的容器
#if 0 

	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	//解析包头
	m_ReceiveSocket->Receive(&stHeader, sizeof(ProtcolHeader));
	switch (stHeader.nMsgType)  //接收的类型和发送的类型一致
	{
		//接收 别人的请求数据,航迹，COM，ESM消息
    case 5:
		{
			SendRequest_Msg tmpRecRequest_Msg;
			
			//读数据拒绝修改
			::EnterCriticalSection(&(theApp.g_cs));
			//清空接收请求信息的结构体
			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
			
            //接收
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				m_ReceiveSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
		
			}
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
	case 6://接收别舰发送来的查找到的返回信息
		{
			SendBack_Msg tmpRecBack_Msg;
			//读数据拒绝修改
			::EnterCriticalSection(&(theApp.g_cs));
			//清空接收返回信息的结构体
			memset(&theApp.m_ReceiveBackMsg, 0, sizeof(SendBack_Msg));
			
            //接收
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
				m_ReceiveSocket->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));
			
			}
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
	default:
		break;
	}
#endif

}

void CNodePlatApp::SendToClient(void)
{

#if 0 	
	//3\请求数据
	ProtcolHeader stHeader;
	VCT_SendRequest_Msg::iterator iteSendReq_Dat;
	VCT_SendBack_Msg::iterator iteSendBack_Dat;

	if (sizeof(theApp.m_StSendRequest))  //有请求
	{    
		//send data
		//发送所有请求数据
	    ::EnterCriticalSection(&(theApp.g_cs));
		switch (theApp.cMsgType)
		{
		case 5:
			{
				stHeader.nMsgType = 5;
				stHeader.nMsgLength = sizeof(theApp.m_StSendRequest);
				for ( theApp.m_pClient =m_ClientMap.begin(); theApp.m_pClient != m_ClientMap.end(); theApp.m_pClient++)
				{
					theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
					theApp.m_pClient->second->Send(&theApp.m_StSendRequest, sizeof(SendRequest_Msg));
				
				}
				break;
			}
		default:
	        break;
		}
	}

 /*
//2\发送给别人响应数据
if (have received req data)
{
  if (算法处理完成!)
	{
	    //回传算法数据
	}
}*/

	if (sizeof(theApp.m_SendBackMsg))
	{
		if (/*算法处理完成*/)//如何判断算法是否处理完成
		{
			//得到需要返回给邻舰的数据 (该数据已经转换成含数组的容器)
			//发送回传算法的数据
			::EnterCriticalSection(&(theApp.g_cs));
			switch (theApp.cMsgType)
			{
			case 6:
				{
					stHeader.nMsgType = 6;
					stHeader.nMsgLength = sizeof(theApp.m_SendBackMsg);
					for ( theApp.m_pClient = m_ClientMap.begin(); theApp.m_pClient != m_ClientMap.end(); theApp.m_pClient++)
					{
						theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
						theApp.m_pClient->second->Send(&theApp.m_SendBackMsg, sizeof(SendBack_Msg));
						
					}
					break;
				}
			default:
				break;
			}	
		}
	}
#endif
}