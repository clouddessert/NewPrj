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
ON_COMMAND(IDM_SENDMSG, OnSendmsg)
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
#if 0
	//0914改
	//接收包头
	//根据包头类型做出状态机
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	theApp.m_P2PSocket->Receive(&stHeader, sizeof(ProtcolHeader));
	switch (stHeader.nMsgType)
	{
	case 11:
		{
			//接收的请求
			//去你的数据库寻找数据; 匹配?????????还需修改算法接口
			//准备发送
			//方法1
			//放到需要发送的buufer里面,定时检查buffer是否为空,不是就发发送!?????????
			//方法2
			//if (找到)
			//SendToClient();
			SendRequest_Msg tmpRecRequest_Msg;
			::EnterCriticalSection(&(theApp.g_cs));
			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				theApp.m_P2PSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			}
			//调用查找匹配请求的信息的算法,还需修改算法接口
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
		
	case 12:
		//接收的别人的数据
		//保存到接收的buffer,over?????????????
		{
			SendBack_Msg tmpRecBack_Msg;
			::EnterCriticalSection(&(theApp.g_cs));
			memset(&theApp.m_ReceiveBackMsg, 0, sizeof(SendBack_Msg));
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
				theApp.m_P2PSocket->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));
			}
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
	default:
		break;
	}
#endif
	
#if 0 	
    //0903改
	//\接收 别人的请求数据 	//4\接收邻舰发送来的查找到的返回信息
	//考虑请求是结构体组成的容器 接收后，将发送过来的含数组的容器转成含容器的容器
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	//解析包头
	theApp.m_P2PSocket->Receive(&stHeader, sizeof(ProtcolHeader));
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
				theApp.m_P2PSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				
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
				theApp.m_P2PSocket->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));
				
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
	//0903改
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

void CNodePlatApp::OnSendmsg(/*map<int, CString> IpMap*//*vector<IP>*/) 
{
	// TODO: Add your command handler code here
	AfxMessageBox("ok");
//#if 0
//0914改
	//获取需要联合识别的信息，并转化成发送报文的结构
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;
	long int lnum;//请求的合批号
	lnum = theApp.m_ESM_Dat.at(theApp.m_iline).lAutonum;//获取请求协同的批号
	
	theApp.m_StRequest.vctEsm.clear();
	theApp.m_StRequest.vctComm.clear();
	memset(&(theApp.m_StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK));
	memset(&theApp.m_StRequest, 0, sizeof(Request_Cooperative_Msg));//清空保存联合识别前信息的结构体		
	memset(&theApp.m_StSendRequest, 0, sizeof(SendRequest_Msg));//清空发送请求的结构体
	
	/*取出联合识别前此批号的相关信息并存储Line460-523*/
	if (lnum >= 8000)
	{
		for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
		{
			if (iteYes->lAutonum == lnum)
			{
				theApp.m_StRequest.lAutonum = lnum;//合批号
				theApp.m_StRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
				if (iteYes->vctEsm.size())//请求协同ESM信息
				{
					for (iteEsm = iteYes->vctEsm.begin(); iteEsm = iteYes->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteYes->vctComm.size())//请求协同COMM信息
				{
					for (iteComm = iteYes->vctComm.begin(); iteComm = iteYes->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				////存放本舰经纬高
				//StRequest.stReqShipPosi.dHeight = iteYes->structTrace.d
				//StRequest.stReqShipPosi.dLati = ;
				//StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0

				break;
			}
		}
	} 
	
	else
	{
		for (iteNo = theApp.m_ClusterNoTraceMsg.begin(); iteNo != theApp.m_ClusterNoTraceMsg.end(); iteNo++)
		{
			if (iteNo->lAutonum == lnum)
			{
				theApp.m_StRequest.lAutonum = lnum;//合批号
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//请求协同ESM信息
				{
					for (iteEsm = iteNo->vctEsm.begin(); iteEsm = iteNo->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//请求协同COMM信息
				{
					for (iteComm = iteNo->vctComm.begin(); iteComm = iteNo->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				//存放本舰经纬高
				// 				StRequest.stReqShipPosi.dHeight = ;
				// 				StRequest.stReqShipPosi.dLati = ;
				// 				StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0
				break;
			}
		}
	} 
	

	//组包
	//向相应的节点发送数据包
	//记录当前时间(组包时当前时戳)
	
	//超时判断
	//判断接收的容器是否为空?
	
	//如果不为空,接收的数据参与运算!
	//参与运算,先copy一份当前的容器;清空接收的buffer容器

	for (int i = 0; i < theApp.IpMap.size(); ++i)
	{	
		//组包/*请求结构体*/
		if (lnum >= 8000)
		{
			for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
			{
				if (iteYes->lAutonum == lnum)
				{	
					/*请求结构体*/
					//StSendRequest.num ++;//信息单元序号???????????????
					//long int nStampTime;             //发送请求信息时的当前时间??????????
					theApp.m_StSendRequest.lAutomn = lnum;//合批号
					theApp.m_StSendRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
					theApp.m_StSendRequest.nRequestEsmN = iteYes->vctEsm.size();
					theApp.m_StSendRequest.nRequestComN = iteYes->vctComm.size();
					for (int i = 0; i <= iteYes->vctEsm.size();i++)//请求协同ESM信息
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//目标esm批号
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//载频
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////脉宽
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//天线扫描信息
					}
					for (i = 0; i <= iteYes->vctComm.size();i++)//请求协同COMM信息
					{
						theApp.m_StSendRequest.lComTargetNumber[i] = iteYes->vctComm.at(i).lTargetNumber;//目标comm批号
						theApp.m_StSendRequest.dComZaiPin[i] = iteYes->vctComm.at(i).dComZaiPin;//载频信息
						theApp.m_StSendRequest.dComPulseExtent[i] = iteYes->vctComm.at(i).dPulseExtent;//脉冲幅度
					}
					//StSendRequest.stReqShipPosi.dHeight = ;//本舰经纬高
					//StSendRequest.stReqShipPosi.dLati = ;
					//StSendRequest.stReqShipPosi.dLonti = ;
					
					theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0					
					break;
				}
			}
		} 		
		else
		{
			for (iteNo = theApp.m_ClusterNoTraceMsg.begin(); iteNo != theApp.m_ClusterNoTraceMsg.end(); iteNo++)
			{
				if (iteNo->lAutonum == lnum)
				{
					/*请求结构体*/				
					//StSendRequest.num ++;//信息单元序号???????????????
					//long int nStampTime;                     //发送请求信息时的当前时间
					theApp.m_StSendRequest.lAutomn = lnum;//合批号
					//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);//请求协同TRACE信息
					theApp.m_StSendRequest.nRequestEsmN = iteNo->vctEsm.size();
					theApp.m_StSendRequest.nRequestComN = iteNo->vctComm.size();
					for (int i = 0; i <= iteNo->vctEsm.size();i++)//请求协同ESM信息
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//目标esm批号
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//载频
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////脉宽
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//天线扫描信息
					}
					for (i = 0; i <= iteNo->vctComm.size();i++)//请求协同COMM信息
					{
						theApp.m_StSendRequest.lComTargetNumber[i] = iteNo->vctComm.at(i).lTargetNumber;//目标comm批号
						theApp.m_StSendRequest.dComZaiPin[i] = iteNo->vctComm.at(i).dComZaiPin;//载频信息
						theApp.m_StSendRequest.dComPulseExtent[i] = iteNo->vctComm.at(i).dPulseExtent;//脉冲幅度
					}
					//StSendRequest.stReqShipPosi.dHeight = ;//本舰经纬高
					//StSendRequest.stReqShipPosi.dLati = ;
					//StSendRequest.stReqShipPosi.dLonti = ;
					
					theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0					
					break;
				}
			}
		}
		//向相应的节点发送数据包
		iteMap = theApp.IpMap.find(i);
		theApp.m_P2PSocket->SendTo(&theApp.m_StSendRequest, sizeof(theApp.m_StSendRequest), P2P_SERVER_PORT, iteMap->second,0);		
		//记录当前时间(组包时当前时戳)
			
		//超时判断

		//判断接收的信息是否为空		
		if (sizeof(theApp.m_SendBackMsg))//如果不为空,接收的数据参与运算!
		{	
			//先将当前结构体中数组转化成容器!!!!!!!!!待写


			//再将转化后的结构体存入容器（后续进行联合识别）
		//	m_BackMsg.push_back(/*转化后的结构体*/);
			//清空接收的结构体/*buffer容器*/
			memset(&theApp.m_SendBackMsg, 0, sizeof(SendBack_Msg));
		}
			
			
			
	}

	//调用算法




//#endif
		

		
}
