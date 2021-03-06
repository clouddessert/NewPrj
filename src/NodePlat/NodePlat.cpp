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

#define bzero(a, b) memset(a, 0, b)
/////////////////////////////////////////////////////////////////////////////
// CNodePlatApp

BEGIN_MESSAGE_MAP(CNodePlatApp, CWinApp)
//{{AFX_MSG_MAP(CNodePlatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
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

	
	m_SendReqMsg_Dat.clear();          //发送的请求信息，由多个结构体组成的容器(已经转成含有数组的容器)
	m_RecvReqMsg_Dat.clear();          //接收请求信息
	m_SendBackMsg_Dat.clear();         //发送返回匹配信息
	m_RecvBackMsg_Dat.clear();         //接收返回信息
	
	m_RequestNum_Dat.clear();          //请求协同的批号
	m_RequestMsg.clear();              //保存联合识别前信息（所有请求协同信息 容器）	
	m_BackMsg.clear();                 //各舰返回的所有匹配信息
	m_CooperMsg.clear();               //本舰和各舰的合并信息
	
	SendToIpMap.clear();

	hESM_wmd = NULL;
	hCOMM_wmd = NULL;
	hTRACE_wmd = NULL;
	hSigOut_wnd = NULL;
	hMulOut_wnd = NULL;
	hMulESM_wmd = NULL;
	hMulCOMM_wnd = NULL;
	hMulTRACE_wnd = NULL;

	HWND hDISPLAY_wnd = NULL;
	
	//	pOutPt = NULL;	
	pXview = NULL;
	hEvent = NULL;
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
	m_DataBase.InitDataBase();
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
	
	SetIPLib();
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

void CNodePlatApp::SetIPLib(void)
{
	//读取临时路径
	CString strTmp,strTmpA;
	CString	sPath;
	
	char host_name[255];
	//获取本地主机名称
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) 
	{
		//error
	}
	struct hostent *phe = gethostbyname(host_name);
	
	struct in_addr addr;
    memcpy(&addr,phe->h_addr_list[0],sizeof(struct in_addr));
//	CString strLocalIP;
	m_strLocalIP.Format("%s", inet_ntoa(addr));
	
	//获得工程文件夹路径
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	//获取IP,如果IP地址和本机IP一致,不添加!
	if (::GetPrivateProfileString(_T("编队IP"), _T("A船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(m_strLocalIP))
		{
			theApp.IpMap.insert(make_pair(0, strTmp));
		}
		else
		{
			m_ThisNumber = 0;

		}
	}
	
	if (::GetPrivateProfileString(_T("编队IP"), _T("B船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(m_strLocalIP))
		{
			theApp.IpMap.insert(make_pair(1, strTmp));
		}
		else
		{
			m_ThisNumber = 1;
			
		}
	}
	if (::GetPrivateProfileString(_T("编队IP"), _T("C船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(m_strLocalIP))
		{
			theApp.IpMap.insert(make_pair(2, strTmp));
		}
		else
		{
			m_ThisNumber = 2;
			
		}
	}
	if (::GetPrivateProfileString(_T("编队IP"), _T("D船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		//strTmp.ReleaseBuffer();
		if (strTmp.Compare(m_strLocalIP))
		{
			theApp.IpMap.insert(make_pair(3, strTmp));
		}
		else
		{
			m_ThisNumber = 3;
			
		}
	}
	strTmp.ReleaseBuffer();
	if (::GetPrivateProfileString(_T("编队IP"), _T("E船IP地址"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		//strTmp.ReleaseBuffer();
		if (strTmp.Compare(m_strLocalIP))
		{
			theApp.IpMap.insert(make_pair(4, strTmp));
		}
		else
		{
			m_ThisNumber = 4;
			
		}
	}
	strTmp.ReleaseBuffer();
}

DWORD WINAPI SendDataProc(LPVOID lParam);
void CNodePlatApp::ServerCreate(void)
{
	//从ini文件加载IP库
	SetIPLib();

	//创建p2p模式socket的服务端//开始监听
	theApp.m_P2PSocket = new CMsgSocket();
	theApp.m_P2PSocket->Socket();
	theApp.m_P2PSocket->Bind(P2P_SERVER_PORT);
	theApp.m_P2PSocket->Listen();
	theApp.m_P2PSocket->AsyncSelect(FD_ACCEPT);

	//创建同步时间
	hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	theApp.SendToIpMap.clear();

	//创建发送数据线程
	theApp.bThreadFlag = TRUE;
	DWORD dwThreadID = 0;
	theApp.hSendProc = ::CreateThread(NULL, 0, SendDataProc, NULL, 0, &dwThreadID);
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

	//关闭信号量
	::CloseHandle(hEvent);
	hEvent = INVALID_HANDLE_VALUE;

	//关闭发送数据线程
	theApp.bThreadFlag = FALSE;
	::CloseHandle(theApp.hSendProc);
	theApp.hSendProc = INVALID_HANDLE_VALUE;

	//send ip clear
	theApp.SendToIpMap.clear();

	//清空IP库
	theApp.IpMap.clear();
}

void CNodePlatApp::ClientAccept(void)
{	
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMsgSocket();
	//接受连接
	if ( theApp.m_P2PSocket->Accept(*(theApp.pClient)) )
	{
		//等待读的事件
		theApp.pClient->AsyncSelect(FD_READ);

		theApp.pClient->GetPeerName(strTmp, nPort);
		//转换IP地址，作为标志
		dwClientIP = inet_addr(strTmp.GetBuffer(0));
		strTmp.ReleaseBuffer();
		
		//存入map
		map<DWORD, CMsgSocket*>::iterator pTmpItor;
		pTmpItor = theApp.m_ClientMap.find(dwClientIP);
		if (theApp.m_ClientMap.end() == pTmpItor)
		{
			//none
		}
		else
		{
			//release resource
			pTmpItor->second->Close();
			delete (pTmpItor->second);
			//删除资源
			theApp.m_ClientMap.erase(pTmpItor);
		}
		//insert
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.m_ClientMap.insert(map<DWORD, CMsgSocket*>::value_type(dwClientIP, theApp.pClient));
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	else
	{
		delete (theApp.pClient);
		theApp.pClient = NULL;
	}
}

void CNodePlatApp::ClientClose(void* pContext)
{
	CMsgSocket* pSk = (CMsgSocket*)pContext;
	
	::EnterCriticalSection(&(theApp.g_cs));
	for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
	{
		if (pSk == theApp.m_pClient->second)
		{
			//关闭SOCKET
			theApp.m_pClient->second->Close();
			delete (theApp.m_pClient->second);
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

void CNodePlatApp::ReceiveFromClient(CMsgSocket* pThis)
{
	/*********************测试能否接收***************************/
	//char* crevchar = new char;
	//pThis->Receive(crevchar, sizeof(char));
	/*********************测试结束*******************************/

	//接收包头
	//根据包头类型做出状态机
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	pThis->Receive(&stHeader, sizeof(ProtcolHeader));		//后面的指针都用pThis
	switch (stHeader.nMsgType)
	{
		//代表接收的是请求
	case 11:
		{
			//接收的请求
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_RecvReqMsg_Dat.clear();
			ZeroMemory(&theApp.tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			pThis->Receive(&theApp.tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			theApp.m_RecvReqMsg_Dat.push_back(theApp.tmpRecRequest_Msg);
			//这里的接收不要用结构体，换成这个结构体的vector，方便后面使用！！！！
			::LeaveCriticalSection(&(theApp.g_cs));	

			//命令消息生成
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			CString time;
			time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
			CString str1,str2,str3;
			str1.Format("我舰");
			str2.Format("收到IP为 ");
			str3.Format("的舰的协同请求");
			theApp.m_MsgDisplay = str1+"于"+time+str2+theApp.tmpRecRequest_Msg.sSendIp+str3;
			
			::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息

			break;
		}
		//代表接收的是数据
// 	case 12:
// 		//保存到接收的buffer,over
// 		{
// 			SendBack_Msg tmpRecBack_Msg;
// 			::EnterCriticalSection(&(theApp.g_cs));
// 			ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
// 			pThis->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));	//都用vector做缓冲区!!!!!!!
// 			theApp.m_RecvBackMsg_Dat.push_back(tmpRecBack_Msg);
// 			::LeaveCriticalSection(&(theApp.g_cs));
// 
// 			//命令消息生成
// 			SYSTEMTIME tm;
// 			GetLocalTime(&tm);
// 			CString time;
// 			time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 			CString str1,str2,str3;
// 			str1.Format("我舰");
// 			str2.Format("收到IP为 ");
// 			str3.Format("的舰的协同数据");
// 			theApp.m_MsgDisplay = str1+"于"+time+str2+theApp.tmpRecRequest_Msg.sSendIp+str3;
// 			
// 			::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息
// 
// 			break;
// 		}
	default:
		break;
	}		
}

void CNodePlatApp::SendToClient(CMsgSocket* pThis)
{
	//0916WHY改
	VCT_UNINUM_MSG::iterator iteUnin;
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	VCT_COMM_MSG::iterator iteSingleCom;
	VCT_ESM_MSG::iterator iteSingleEsm;
	VCT_TRACE_MSG::iterator iteSingleTrace;
	VCT_ESM_MSG::iterator iteEsm;          //同方位ESM信息
	VCT_COMM_MSG::iterator iteComm; 
	UNI_NUM stUni;
	UNI_NOTRACE_NUM stUniNoT;
	SHIP_POSITION stSelfPosi;
	//这里需要写！！！！
	//这里需要sendto的数据准备好
    //调用算法 准备需要发送出的响应数据 被动发送
	//输入:该时刻本舰聚类后有编批和无编批数据信息, 邻舰发送来的含数组的请求结构体, 找出的返回信息(已转化为数组形式的结构体)
     SendBack_Msg stSendBackMsg;
     ZeroMemory(&stSendBackMsg, sizeof(SendBack_Msg));
	 UNI_All_NUM stUniAllN;
	 //清空存储聚类后的数据结构体中的各容器.
	 for ( iteUnin = stUniAllN.vctUnin.begin(); iteUnin != stUniAllN.vctUnin.end(); iteUnin++)
	 {
		iteUnin->lAutonum = NULL;
		memset(&(iteUnin->structTrace), 0, sizeof(TRACKSTATUS_MARK));
		for ( iteEsm = iteUnin->vctEsm.begin(); iteEsm != iteUnin->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for( iteComm = iteUnin->vctComm.begin(); iteComm != iteUnin->vctComm.end(); iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}
		iteUnin->vctEsm.clear();
		iteUnin->vctComm.clear();
	 }
	 for ( iteNoTraceUnin = stUniAllN.vctNoTraceUnin.begin(); iteNoTraceUnin != stUniAllN.vctNoTraceUnin.end(); iteNoTraceUnin++)
	 {
		 iteNoTraceUnin->lAutonum = NULL;
		 for ( iteEsm = iteNoTraceUnin->vctEsm.begin(); iteEsm != iteNoTraceUnin->vctEsm.end(); iteEsm++)
		 {
			 memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		 }
		 for( iteComm = iteNoTraceUnin->vctComm.begin(); iteComm != iteNoTraceUnin->vctComm.end(); iteComm++)
		 {
			 memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		 }
		 iteNoTraceUnin->vctEsm.clear();
		 iteNoTraceUnin->vctComm.clear();
	 }
     for ( iteSingleTrace = stUniAllN.vctSingleTrace.begin(); iteSingleTrace != stUniAllN.vctSingleTrace.end(); iteSingleTrace++)
     {
		memset(&(*iteSingleTrace), 0, sizeof(TRACKSTATUS_MARK));
     }
	 for( iteSingleEsm = stUniAllN.vctSingleEsm.begin(); iteSingleEsm != stUniAllN.vctSingleEsm.end(); iteSingleEsm++)
	 {
		memset(&(*iteSingleEsm), 0, sizeof(ESMSTATUS_MARK));
	 }
	 for( iteSingleCom = stUniAllN.vctSingleCom.begin(); iteSingleCom != stUniAllN.vctSingleCom.end(); iteSingleCom++)
	 {
    	memset(&(*iteSingleCom ), 0, sizeof(COMSTATUS_MARK));
	 }
	 stUniAllN.vctSingleTrace.clear();
	 stUniAllN.vctSingleEsm.clear();
	 stUniAllN.vctSingleCom.clear();
	 //存储聚类后的有编批和无编批数据信息
	 for ( iteUnin = m_ClusterUniMsg.begin(); iteUnin != m_ClusterUniMsg.end(); iteUnin++)
	 {
		 stUni.lAutonum = iteUnin->lAutonum;
		 stUni.structTrace = iteUnin->structTrace;
		 for ( iteEsm = iteUnin->vctEsm.begin(); iteEsm != iteUnin->vctEsm.end(); iteEsm++)
		 {
			 stUni.vctEsm.push_back(*iteEsm);
		 }
		 for ( iteComm = iteUnin->vctComm.begin(); iteComm != iteUnin->vctComm.end(); iteComm++)
		 {
			 stUni.vctComm.push_back(*iteComm);
		 }
		 stUniAllN.vctUnin.push_back(stUni);
	 }
	 for( iteNoTraceUnin = m_ClusterNoTraceMsg.begin(); iteNoTraceUnin != m_ClusterNoTraceMsg.end(); iteNoTraceUnin++)
	 {
		 stUniNoT.lAutonum = iteNoTraceUnin->lAutonum;
		 for ( iteEsm = iteNoTraceUnin->vctEsm.begin(); iteEsm != iteNoTraceUnin->vctEsm.end(); iteEsm++)
		 {
			 stUniNoT.vctEsm.push_back(*iteEsm);
		 }
		 for ( iteComm = iteNoTraceUnin->vctComm.begin(); iteComm != iteNoTraceUnin->vctComm.end(); iteComm++)
		 {
			 stUniNoT.vctComm.push_back(*iteComm);
		 }
		 stUniAllN.vctNoTraceUnin.push_back(stUniNoT);
	 }
	 //存储未聚类的单独信息
     for ( iteSingleTrace = m_SingleTrace.begin(); iteSingleTrace != m_SingleTrace.end(); iteSingleTrace++)
     {
		 stUniAllN.vctSingleTrace.push_back(*iteSingleTrace);
     }
	 for ( iteSingleEsm = m_SingleEsm.begin(); iteSingleEsm != m_SingleEsm.end(); iteSingleEsm++)
	 {
		 stUniAllN.vctSingleEsm.push_back(*iteSingleEsm);
	 }
	 for( iteSingleCom = m_SingleComm.begin(); iteSingleCom != m_SingleComm.end(); iteSingleCom++)
     {
		 stUniAllN.vctSingleCom.push_back(*iteSingleCom);
	 }
	 //获取本舰的经纬高
	 if ( m_ThisNumber == 0) //代表A舰 ,或得A舰的经纬高
	 {
		 stSelfPosi = theApp.m_Ship_Position.at(0);
         
	 }
	 if ( m_ThisNumber == 1) // 代表B舰获得的经纬高
	 {
		 stSelfPosi = theApp.m_Ship_Position.at(1);

	 }
	 if ( m_ThisNumber == 2) // 代表C舰获得的经纬高
	 {
		 stSelfPosi = theApp.m_Ship_Position.at(2);
	 }
	 if ( m_ThisNumber == 3) // 代表d舰获得的经纬高
	 {
		 stSelfPosi = theApp.m_Ship_Position.at(3);
		 
	 }
	 if ( m_ThisNumber == 4) // 代表e舰获得的经纬高
	 {
		 stSelfPosi = theApp.m_Ship_Position.at(4);
	 }

     //调用算法,找出响应请求的返回信息stSendBackMsg
	CoopFind_Information_To_MainShip(stSelfPosi,stUniAllN, theApp.tmpRecRequest_Msg, stSendBackMsg);

	ProtcolHeader stHeader;                  //报头信息
	//判断返回信息不为空,进行发送
	if ( (stSendBackMsg.BackTraceN + stSendBackMsg.BackESMN +stSendBackMsg.BackCOMN) != 0)
    {
		//准备完成，发送数据返回
		strcpy(stSendBackMsg.sReceiveIp, theApp.tmpRecRequest_Msg.sSendIp);//接收方IP
		strcpy(stSendBackMsg.sSendIp, theApp.tmpRecRequest_Msg.sReceiveIp);//发送方IP
		stHeader.nMsgType = 12;
		stHeader.nMsgLength = sizeof(stSendBackMsg);
		pThis->Send(&stHeader, sizeof(stHeader));
		pThis->Send(&stSendBackMsg, sizeof(stSendBackMsg));
    }

	//命令消息生成
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2,str3;
	str1.Format("我舰");
	str2.Format("向IP为 ");
	str3.Format("的舰发送协同数据");
	theApp.m_MsgDisplay = str1+"于"+time+str2+theApp.tmpRecRequest_Msg.sSendIp+str3;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息
}

/****************************发送数据的函数******************************************/

void CNodePlatApp::SendMsg(map<int, CString> SendToIpMap) 
{
	// TODO: Add your command handler code here
	//获取需要联合识别的信息，并转化成发送报文的结构
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;	
	vector<int>::iterator iteNum;
	VCT_Request_Cooperative_Msg::iterator iteReqCoopMsg;
	VCT_SendRequest_Msg::iterator iteSendReq;
	Request_Cooperative_Msg m_StRequest;      //保存联合识别前此批号的本舰信息
	int i = 0;

	long int lnum;//请求的合批号
	lnum = m_ESM.at(m_iline).lAutonum;//获取请求协同的批号
	int flag =0;
	int l = m_RequestNum_Dat.size();
	for (iteNum = m_RequestNum_Dat.begin(); iteNum != m_RequestNum_Dat.end(); iteNum++)
	{
		if (lnum == *iteNum)
		{
			flag = 1;
			break;
		}
	}
	if(!flag)
	{
		m_RequestNum_Dat.push_back(lnum);//请求协同批号容器
	}

	VCT_SendBack_Msg::iterator iteBack;
	BACK_Cooperative_Msg stBackCooper;
	//	TRACKSTATUS_MARK stTrace;
	ESMSTATUS_MARK stEsm;
	COMSTATUS_MARK stCom;
	//	SHIP_POSITION stBackShipPosi;            //应答舰的经纬高

	CNodePlatDoc *pTmpDoc = (CNodePlatDoc*)theApp.pTmpDocPt;

	int s,t, m, n;

	//清空
	m_StRequest.vctEsm.clear();
	m_StRequest.vctComm.clear();
	memset(&(m_StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK));
	memset(&m_StRequest, 0, sizeof(Request_Cooperative_Msg));//清空保存联合识别前信息的结构体		
	memset(&theApp.m_StSendRequest, 0, sizeof(SendRequest_Msg));//清空发送请求的结构体

	if ( SendToIpMap.empty() )
	{
		//none
	}
	else
	{
		for (iteReqCoopMsg = theApp.m_RequestMsg.begin(); iteReqCoopMsg != theApp.m_RequestMsg.end(); iteReqCoopMsg++)
		{ 
			iteReqCoopMsg->lAutonum = NULL;
			iteReqCoopMsg->nCorrFlag = NULL;
			iteReqCoopMsg->nStampTime = NULL;
			memset(&iteReqCoopMsg->stTrace, 0, sizeof(TRACKSTATUS_MARK));
			memset(&iteReqCoopMsg->stReqShipPosi, 0, sizeof(SHIP_POSITION));//本舰经纬高
			for ( iteEsm = iteReqCoopMsg->vctEsm.begin(); iteEsm != iteReqCoopMsg->vctEsm.end(); iteEsm++)
			{
				memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
			}
			for ( iteComm = iteReqCoopMsg->vctComm.begin(); iteComm != iteReqCoopMsg->vctComm.end();iteComm++)
			{
				memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
			}
			iteReqCoopMsg->vctEsm.clear();
			iteReqCoopMsg->vctComm.clear();
		}
		theApp.m_RequestMsg.clear();
		
		/*取出联合识别前此批号的相关信息并存储Line460-523*/
		for (iteNum = m_RequestNum_Dat.begin(); iteNum != m_RequestNum_Dat.end(); iteNum++)
		{
			if ((*iteNum) >= 8000)
			{   
				for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /*theApp.m_ClusterUniMsg.end()*/; iteYes++ ,s++)
				{
					if (iteYes->lAutonum == *iteNum)
					{
						m_StRequest.lAutonum = *iteNum;//合批号
						m_StRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
						if (iteYes->vctEsm.size())//请求协同ESM信息
						{
							for (iteEsm = iteYes->vctEsm.begin(),m =1 ; m <= iteYes->vctEsm.size() /*iteEsm = iteYes->vctEsm.end()*/; iteEsm++,m++)
							{
								m_StRequest.vctEsm.push_back(*iteEsm);
							}
						}
						if (iteYes->vctComm.size())//请求协同COMM信息
						{
							for (iteComm = iteYes->vctComm.begin(), n = 1;  n <= iteYes->vctComm.size()  /*iteComm = iteYes->vctComm.end()*/; iteComm++ ,n++)
							{
								m_StRequest.vctComm.push_back(*iteComm);
							}
						}
						//取出本舰的经纬高:根据舰的编号来确定
						if ( m_ThisNumber == 0) //代表A舰 ,或得A舰的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(0);
						}
						if ( m_ThisNumber == 1) // 代表B舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(1);
						}
						if ( m_ThisNumber == 2) // 代表c舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(2);
						}
						if ( m_ThisNumber == 3) // 代表D舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(3);
						}
						if ( m_ThisNumber == 4) // 代表E舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(4);
						}
						m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0
						theApp.m_RequestMsg.push_back(m_StRequest);
						break;
					}
				}
			} 	
			else
			{
				for (iteNo = theApp.m_ClusterNoTraceMsg.begin() ,t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
				{
					if (iteNo->lAutonum == *iteNum)
					{
						m_StRequest.lAutonum = *iteNum;//合批号
						//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
						if (iteNo->vctEsm.size())//请求协同ESM信息
						{
							for (iteEsm = iteNo->vctEsm.begin(),m=1; m<=iteNo->vctEsm.size()/* iteEsm = iteNo->vctEsm.end()*/; iteEsm++,m++)
							{
								m_StRequest.vctEsm.push_back(*iteEsm);
							}
						}
						if (iteNo->vctComm.size())//请求协同COMM信息
						{
							for (iteComm = iteNo->vctComm.begin(),n=1; n<=iteNo->vctComm.size()/* iteComm = iteNo->vctComm.end()*/; iteComm++,n++)
							{
								m_StRequest.vctComm.push_back(*iteComm);
							}
						}
						//取出本舰的经纬高:根据舰的编号来确定
						if ( m_ThisNumber == 0) //代表A舰 ,或得A舰的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(0);
						}
						if ( m_ThisNumber == 1) // 代表B舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(1);
						}
						if ( m_ThisNumber == 2) // 代表C舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(2);
						}
						if ( m_ThisNumber == 3) // 代表D舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(3);
						}
						if ( m_ThisNumber == 4) // 代表E舰获得的经纬高
						{
							m_StRequest.stReqShipPosi = theApp.m_Ship_Position.at(4);
						}
						m_StRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0
						theApp.m_RequestMsg.push_back(m_StRequest);
						break;
					}
				}
			}
		} 
	}

	int nShipNum = 0;
	//这里面的map是界面传过来的！！不是全局的那个map，全局的map是给你界面用的。比如你选中B舰，这里的vector就是B舰的
	theApp.m_SendReqMsg_Dat.clear();//清空发送请求数据
	for (iteMap = SendToIpMap.begin(), nShipNum = 0; iteMap != SendToIpMap.end(); ++iteMap, ++nShipNum)//遍历界面传来的协同舰ip
	{
		//流程如下！
		//组包
		//向相应的节点发送数据包
		//记录当前时间(组包时当前时戳)
		//超时判断
		//判断接收的容器是否为空?	
		//如果不为空,接收的数据参与运算!
		//参与运算,先copy一份当前的容器;清空接收的buffer容器

		//组包/*请求结构体*/存容器
		int n = m_RequestNum_Dat.size();
		for (iteNum = m_RequestNum_Dat.begin(); iteNum != m_RequestNum_Dat.end(); iteNum++)
		{
			if (*iteNum >=8000)//(lnum >= 8000)   //????????????????是不是同一时刻的,从容器中转存为数组结构体
			{
				for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /* iteYes != theApp.m_ClusterUniMsg.end()*/; iteYes++,s++)
				{
					if (iteYes->lAutonum == *iteNum)
					//if (iteYes->lAutonum == lnum)
					{	
						/*请求结构体*/
						//StSendRequest.num ++;//信息单元序号???????????????
						//long int nStampTime;             //发送请求信息时的当前时间??????????
						strcpy(theApp.m_StSendRequest.sReceiveIp, iteMap->second);//接收方IP
						strcpy(theApp.m_StSendRequest.sSendIp, theApp.m_strLocalIP);//发送方IP
						theApp.m_StSendRequest.lAutomn = *iteNum;//合批号
						theApp.m_StSendRequest.stTrace = iteYes->structTrace;//请求协同TRACE信息
						theApp.m_StSendRequest.nRequestEsmN = iteYes->vctEsm.size();
						theApp.m_StSendRequest.nRequestComN = iteYes->vctComm.size();
						for (i = 0; i < iteYes->vctEsm.size();i++)//请求协同ESM信息
						{
							theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//目标esm批号
							theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//载频
							theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////脉宽
							theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//天线扫描信息
							//					theApp.m_StSendRequest.dEsmConfidence[i] = iteYes->vctEsm.at(i).dConfidence; //可信度
							
						}
						for (i = 0; i < iteYes->vctComm.size();i++)//请求协同COMM信息
						{
							theApp.m_StSendRequest.lComTargetNumber[i] = iteYes->vctComm.at(i).lTargetNumber;//目标comm批号
							theApp.m_StSendRequest.dComZaiPin[i] = iteYes->vctComm.at(i).dComZaiPin;//载频信息
							theApp.m_StSendRequest.dComPulseExtent[i] = iteYes->vctComm.at(i).dPulseExtent;//脉冲幅度
							//					theApp.m_StSendRequest.dComConfidence[i] =  iteYes->vctComm.at(i).dConfidence; //可信度
							
						}
						//取出本舰的经纬高:根据舰的编号来确定
						if ( m_ThisNumber == 0) //代表A舰,获得A舰的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(0);
						}
						if ( m_ThisNumber == 1) // 代表B舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(1);
						}
						if ( m_ThisNumber == 2) // 代表c舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(2);
						}
						if ( m_ThisNumber == 3) // 代表D舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(3);
						}
						if ( m_ThisNumber == 4) // 代表E舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(4);
						}
						theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0
						theApp.m_SendReqMsg_Dat.push_back(theApp.m_StSendRequest);
						break;
					}
				}
			} 		
			else
			{
				for (iteNo = theApp.m_ClusterNoTraceMsg.begin(),t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
				{
					if (iteNo->lAutonum == *iteNum)
					//if (iteNo->lAutonum == lnum)
					{
						/*请求结构体*/				
						//StSendRequest.num ++;//信息单元序号???????????????
						//long int nStampTime;                     //发送请求信息时的当前时间					
						strcpy(theApp.m_StSendRequest.sReceiveIp, iteMap->second);//接收方IP
						strcpy(theApp.m_StSendRequest.sSendIp, theApp.m_strLocalIP);//发送方IP
						theApp.m_StSendRequest.lAutomn = lnum;//合批号
						//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);//请求协同TRACE信息
						theApp.m_StSendRequest.nRequestEsmN = iteNo->vctEsm.size();
						theApp.m_StSendRequest.nRequestComN = iteNo->vctComm.size();
						for (i = 0; i < iteNo->vctEsm.size();i++)//请求协同ESM信息
						{
							theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//目标esm批号
							theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//载频
							theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////脉宽
							theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//天线扫描信息
							//					theApp.m_StSendRequest.dEsmConfidence[i] = iteYes->vctEsm.at(i).dConfidence; //可信度
							
						}
						for (i = 0; i < iteNo->vctComm.size();i++)//请求协同COMM信息
						{
							theApp.m_StSendRequest.lComTargetNumber[i] = iteNo->vctComm.at(i).lTargetNumber;//目标comm批号
							theApp.m_StSendRequest.dComZaiPin[i] = iteNo->vctComm.at(i).dComZaiPin;//载频信息
							theApp.m_StSendRequest.dComPulseExtent[i] = iteNo->vctComm.at(i).dPulseExtent;//脉冲幅度
							theApp.m_StSendRequest.dComFre[i] = iteNo->vctComm.at(i).dComFre; // 中心频率(MHz)
							theApp.m_StSendRequest.dComBand[i] = iteNo->vctComm.at(i).dComBand; // 信号带宽(MHz)
							theApp.m_StSendRequest.dComJPN[i] = iteNo->vctComm.at(i).dComJPN; // 跳步次数    
							//					theApp.m_StSendRequest.dComConfidence[i] =  iteYes->vctComm.at(i).dConfidence; //可信度
							
						}
						//本舰经纬高
						if ( m_ThisNumber == 0) //代表A舰,获得A舰的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(0);
						}
						if ( m_ThisNumber == 1) // 代表B舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(1);
						}
						if ( m_ThisNumber == 2) // 代表c舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(2);
						}
						if ( m_ThisNumber == 3) // 代表D舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(3);
						}
						if ( m_ThisNumber == 4) // 代表E舰获得的经纬高
						{
							theApp.m_StSendRequest.stReqShipPosi = theApp.m_Ship_Position.at(4);
						}
						
						theApp.m_StSendRequest.nCorrFlag = 0;//请求信息的结构体是否找到相关联信息的标志初始化为0					
						theApp.m_SendReqMsg_Dat.push_back(theApp.m_StSendRequest);
						break;
					}
				}
			}
		}
		
		//create socket---------------------------------------------/
		theApp.m_P2PClient[nShipNum]->Socket();
		
		//设定网络的接收延迟为200ms
		int nNetTimeout = 200;
		BOOL bDontLinger = FALSE;
		BOOL bReuseaddr = TRUE;
		
		::setsockopt(theApp.m_P2PClient[nShipNum]->m_hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int));
		//发送延迟为400ms
		nNetTimeout = 400;
		::setsockopt(theApp.m_P2PClient[nShipNum]->m_hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int));
		//connect关闭
		::setsockopt(theApp.m_P2PClient[nShipNum]->m_hSocket, SOL_SOCKET, SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
		//close后重新使用
		::setsockopt(theApp.m_P2PClient[nShipNum]->m_hSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&bReuseaddr,sizeof(BOOL));
		//over

		if ( SendToIpMap.size() > 1 )//所有舰
		{
			//命令消息生成
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			CString time;
			time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
			CString str1,str2,str3;
			str1.Format("我舰");
			str2.Format("向所有舰发送协同请求");
			theApp.m_MsgDisplay = str1+"于"+time+str2;		
			::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息
		}
		else
		{
			//命令消息生成
			SYSTEMTIME tm;
			GetLocalTime(&tm);
			CString time;
			time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
			CString str1,str2,str3;
			str1.Format("我舰");
			str2.Format("向IP为 ");
			str3.Format("的舰发送协同请求");
			theApp.m_MsgDisplay = str1+"于"+time+str2+iteMap->second+str3;		
			::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息
		}
// 		//命令消息生成
// 		SYSTEMTIME tm;
// 		GetLocalTime(&tm);
// 		CString time;
// 		time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 		CString str1,str2,str3;
// 		str1.Format("我舰");
// 		str2.Format("向IP为 ");
// 		str3.Format("的舰发送协同请求");
// 		theApp.m_MsgDisplay = str1+"于"+time+str2+iteMap->second+str3;		
// 		::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息

		//向相应的节点发送数据包
		int conreval;
		CString cstest = iteMap->second;
		conreval = theApp.m_P2PClient[nShipNum]->Connect(iteMap->second, P2P_SERVER_PORT);
		
		if (conreval)//连接成功
		{
			int m = m_SendReqMsg_Dat.size();
			for (iteSendReq = m_SendReqMsg_Dat.begin(); iteSendReq != m_SendReqMsg_Dat.end(); iteSendReq++)
			{
				theApp.m_StSendRequest = *iteSendReq;
				//发送请求
				pTmpDoc->SendCoopReq(theApp.m_P2PClient[nShipNum]);
				//等待数据 
				pTmpDoc->ReceiveData(theApp.m_P2PClient[nShipNum]);
			}										
		}
		else
		{
			//connect失败!
		}
		//关闭socket,等待重新使用!
		theApp.m_P2PClient[nShipNum]->ShutDown(2);
		theApp.m_P2PClient[nShipNum]->Close();
		
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!这里是单次接收的数据，需要立刻处理!!!!!!!!!!!!!!!!!!!!!!!!!
		//判断接收缓冲区vector是否为空
		if (theApp.m_RecvBackMsg_Dat.size() !=0 )
		{	
			//先将当前结构体中数组转化成容器
			for (iteBack = theApp.m_RecvBackMsg_Dat.begin(); iteBack != theApp.m_RecvBackMsg_Dat.end(); iteBack++)
			{	
				stBackCooper.vctComm.clear();
				stBackCooper.vctEsm.clear();
				stBackCooper.lAutonum = iteBack->lAutonum;
				stBackCooper.nCorrFlag = iteBack->nCorrFlag;
				stBackCooper.nStampTime = iteBack->nStampTime;
				stBackCooper.BackESMN = iteBack->BackESMN;
				stBackCooper.BackCOMN = iteBack->BackCOMN;
				stBackCooper.BackTrackN = iteBack->BackTraceN;
				memcpy(&stBackCooper.stBackShipPosi, &(iteBack->stBackShipPosi), sizeof(stBackCooper.stBackShipPosi)); 
				memcpy(&stBackCooper.stTrace, &(iteBack->stTrace),sizeof(stBackCooper.stTrace));
				
				for (int i=0; i< iteBack->BackESMN; i++)
				{
					stEsm.lTargetNumber = iteBack->lEsmTargetNumber[i];
					stEsm.dZaiPin = iteBack->dEsmZaiPin[i];
					stEsm.dMaiKuan = iteBack->dEsmMaiKuan[i];
					stEsm.dTianXianScan = iteBack->dEsmTianXianScan[i];
					stEsm.dConfidence = iteBack->dEsmConfidence[i];
					for ( int k = 0; k<32; k++)
					{
						stEsm.sPlatType[k] = iteBack->sEsmPlatType[i][k];	
					}
					stBackCooper.vctEsm.push_back(stEsm);
				}
				for (int j=0; j< iteBack->BackCOMN; j++)
				{
					stCom.lTargetNumber = iteBack->lComTargetNumber[j];
					stCom.dComZaiPin = iteBack->dComZaiPin[j];
					stCom.dPulseExtent = iteBack->dComPulseExtent[j];
					stCom.dComFre = iteBack->dComFre[j];
					stCom.dComBand = iteBack->dComBand[j];
					stCom.dComJPN = iteBack->dComJPN[j];
					stCom.dConfidence = iteBack->dComConfidence[j];
					for ( int k = 0; k<32; k++)
					{
						stCom.sPlatType[k] = iteBack->sComPlatType[j][k];	
					}
					stBackCooper.vctComm.push_back(stCom);
				}
				theApp.m_BackMsg.push_back(stBackCooper);
				//命令消息生成
				SYSTEMTIME tm;
				GetLocalTime(&tm);
				CString time;
				time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
				CString str1,str2,str3;
				str1.Format("我舰");
				str2.Format("收到IP为 ");
				str3.Format("的舰的协同数据");
				theApp.m_MsgDisplay = str1+"于"+time+str2+iteBack->sSendIp+str3;
				::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//给显示窗口发送消息
			}
			//清空接收的buffer容器
			//memset(&theApp.m_SendBackMsg, 0, sizeof(SendBack_Msg));
			for (iteBack = theApp.m_RecvBackMsg_Dat.begin(); iteBack != theApp.m_RecvBackMsg_Dat.end(); iteBack++)
			{
				memset(iteBack, 0, sizeof(SendBack_Msg));
			}
			theApp.m_RecvBackMsg_Dat.clear();
		}
	}

	//判断数据返回
	if (theApp.m_BackMsg.size() != 0)
	{
		theApp.m_MulIdentifyMsg.clear();
		theApp.m_MulTrace.clear();
		theApp.m_MulESM.clear();
		theApp.m_MulComm.clear();
		//调用算法
		GET_CooperateMsg_Modul(theApp.m_StSendRequest.stReqShipPosi,theApp.m_RequestMsg, theApp.m_BackMsg, theApp.m_CooperMsg);
		/* 综合识别结果*/
    	MultipleIdentify(theApp.m_CooperMsg, theApp.m_MulIdentifyMsg);
		/*融合信息结果*/
		FusionCooperativeMsg(theApp.m_RequestMsg, theApp.m_BackMsg, theApp.m_MulIdentifyMsg, theApp.m_CoopFusIdentify);
		//在界面上显示当前时刻
		//将返回信息分开存储并显示
		for ( iteCoFus1 = theApp.m_CoopFusIdentify.begin(); iteCoFus1 != theApp.m_CoopFusIdentify.end(); iteCoFus1++)
		{
			if ( iteCoFus1->lAutonum > 7999||(iteCoFus1->lAutonum >4999 && iteCoFus1->lAutonum <6000))
			{
				theApp.m_MulTrace.push_back(iteCoFus1->stFusTrack);
			}
			
			if (iteCoFus1->vctFusEsm.size() != 0)
			{
				for (iteFusEsm1 = iteCoFus1->vctFusEsm.begin(); iteFusEsm1 !=  iteCoFus1->vctFusEsm.end(); iteFusEsm1++ )
				{
					theApp.m_MulESM.push_back(*iteFusEsm1);
				}
			}
			if (iteCoFus1->vctFusCom.size() != 0)
			{
				for (iteFusCom1 = iteCoFus1->vctFusCom.begin(); iteFusCom1 !=  iteCoFus1->vctFusCom.end(); iteFusCom1++ )
				{
					theApp.m_MulComm.push_back(*iteFusCom1);
				}
			}
		}

		//清空接收信息
		for (theApp.iteBackMsg = theApp.m_BackMsg.begin(); theApp.iteBackMsg != theApp.m_BackMsg.end(); theApp.iteBackMsg++)
		{
			theApp.iteBackMsg->BackCOMN = NULL;
		    theApp.iteBackMsg->BackESMN= NULL;
		    theApp.iteBackMsg->BackTrackN = NULL;
		//  theApp.iteBackMsg->dAzimuth = NULL;
		// 	theApp.iteBackMsg->dElevationAngle = NULL;
		// 	theApp.iteBackMsg->dRange = NULL;
	    	theApp.iteBackMsg->lAutonum = NULL;
		    theApp.iteBackMsg->nStampTime =NULL;
		    memset(&theApp.iteBackMsg->stBackShipPosi, 0, sizeof(SHIP_POSITION));
		    memset(&theApp.iteBackMsg->stTrace, 0, sizeof( TRACKSTATUS_MARK));
		    for (iteEsm = theApp.iteBackMsg->vctEsm.begin(); iteEsm != theApp.iteBackMsg->vctEsm.end(); iteEsm++)
			{
			    memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
			}
		    for (iteComm = theApp.iteBackMsg->vctComm.begin(); iteComm != theApp.iteBackMsg->vctComm.end(); iteComm++)
			{
			    memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
			}
		    theApp.iteBackMsg->vctComm.clear();
		    theApp.iteBackMsg->vctEsm.clear();	 
		}
	    theApp.m_BackMsg.clear();

		//此处，应将航迹融合的数据存储起来，方便评估，可存入文件中

		//这里不能弹出对话框！！！！！
		//AfxMessageBox("calucate ok!");
	}
	else
	{
		//AfxMessageBox("未找到返回信息");
	}
}

DWORD WINAPI SendDataProc(LPVOID lParam)
{
	map<int, CString> stTmp;
	map<int, CString>::iterator iter;

	int x = 0;

	//p2p客户端socket初始化
	for (x = 0; x < 5; ++x)
	{
		theApp.m_P2PClient[x] = new CSocket();
	}

	while (theApp.bThreadFlag)
	{
		//Sleep 1000ms
		Sleep(1000);
		
		::EnterCriticalSection(&(theApp.g_cs));
		stTmp.clear();
		for (iter = theApp.SendToIpMap.begin(); iter != theApp.SendToIpMap.end(); ++iter)
		{
			stTmp.insert(*iter);
		}
		::LeaveCriticalSection(&(theApp.g_cs));

		theApp.SendMsg(stTmp);
	}

	//释放监听端资源
	for (x = 0; x < 5; ++x)
	{
		delete theApp.m_P2PClient[x];
		theApp.m_P2PClient[x] = NULL;
	}
	
	return 0;
}



int CNodePlatApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_DataBase.ExitDataBase();
	return CWinApp::ExitInstance();
}
