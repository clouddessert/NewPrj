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
	// ��ʼ���ٽ���
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
		AfxMessageBox("SOCKET ��ʼ��ʧ��");
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
	//���ñ���
	m_pMainWnd->SetWindowText("����ʶ����̬����������ƽ̨");
	
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
	//����p2pģʽsocket
	theApp.m_P2PSocket = new CMsgSocket();
	theApp.m_P2PSocket->Socket();
	
	theApp.m_P2PSocket->Bind(P2P_SERVER_PORT);
	
	//��ʼ����
	theApp.m_P2PSocket->Listen();
}

void CNodePlatApp::ServerShutDown(void)
{
	for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
	{
		//�رտͻ�������
		theApp.m_pClient->second->Close();
		//�ͷſͻ�����Դ
		delete (theApp.m_pClient->second);
		theApp.m_pClient->second = NULL;
	}
	//�ͻ������
	theApp.m_ClientMap.clear();
	
	//�رռ���
	theApp.m_P2PSocket->Close();
	//�ͷż�������Դ
	delete theApp.m_P2PSocket;
	theApp.m_P2PSocket = NULL;
}

void CNodePlatApp::ClientAccept(void)
{	
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMsgSocket();
	//��������
	theApp.m_P2PSocket->Accept(*(theApp.pClient));
	
	theApp.pClient->GetPeerName(strTmp, nPort);
	//ת��IP��ַ����Ϊ��־
	dwClientIP = inet_addr(strTmp.GetBuffer(0));
	strTmp.ReleaseBuffer();
	
	//����map
	::EnterCriticalSection(&(theApp.g_cs));
//	theApp.m_ClientMap.insert(map<DWORD, CMySocket*>::value_type(dwClientIP, theApp.pClient));
	theApp.m_ClientMap.insert(map<DWORD, CMsgSocket*>::value_type(dwClientIP, theApp.pClient));
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CNodePlatApp::ClientClose(void* pContext)
{
//	CMySocket* pSk = (CMySocket*)pContext;
	CMsgSocket* pSk = (CMsgSocket*)pContext;
	
	::EnterCriticalSection(&(theApp.g_cs));
	for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
	{
		if (pSk == theApp.m_pClient->second)
		{
			//�ر�SOCKET
			theApp.m_pClient->second->Close();
			//ɾ���رյ���Դ
			theApp.m_ClientMap.erase(theApp.m_pClient);
			break;
		}
		else
		{
			//����
		}
	}
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CNodePlatApp::ReceiveFromClient(CMsgSocket* pThis)
{
//#if 0
	//0914��
	//���հ�ͷ
	//���ݰ�ͷ��������״̬��
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	pThis->Receive(&stHeader, sizeof(ProtcolHeader));		//�����ָ�붼��pThis
	switch (stHeader.nMsgType)
	{
	case 11:
		{
			//���յ�����
			//ȥ������ݿ�Ѱ������; ƥ��?????????�����޸��㷨�ӿ�
			//׼������
			//����1
			//�ŵ���Ҫ���͵�buufer����,��ʱ���buffer�Ƿ�Ϊ��,���Ǿͷ�����!?????????
			//����2
			//if (�ҵ�)
			//SendToClient();
			SendRequest_Msg tmpRecRequest_Msg;
			::EnterCriticalSection(&(theApp.g_cs));
//			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
			theApp.m_RecvReqMsg_Dat.clear();
// 			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
// 			{
				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				pThis->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				theApp.m_RecvReqMsg_Dat.push_back(tmpRecRequest_Msg);
//			}	//����Ľ��ղ�Ҫ�ýṹ�壬��������ṹ���vector���������ʹ�ã�������
			::LeaveCriticalSection(&(theApp.g_cs));	
			//SendTo,һ��Ҫ���,����Ϊ�˷���ʹ������sendTO
			SendToClient(pThis,tmpRecRequest_Msg);
			break;
		}
		
	case 12:
		//���յı��˵�����
		//���浽���յ�buffer,over?????????????
		{
			SendBack_Msg tmpRecBack_Msg;
			::EnterCriticalSection(&(theApp.g_cs));
//			memset(&theApp.m_ReceiveBackMsg, 0, sizeof(SendBack_Msg));
//			theApp.m_RecvBackMsg_Dat.clear();
// 			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
// 			{
				ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
				pThis->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));	//����vector��������!!!!!!!
				theApp.m_RecvBackMsg_Dat.push_back(tmpRecBack_Msg);
//			}
			::LeaveCriticalSection(&(theApp.g_cs));
			break;
		}
	default:
		break;
	}
// #endif
	
// #if 0 	
//     //0903��
// 	//\���� ���˵��������� 	//4\�����ڽ��������Ĳ��ҵ��ķ�����Ϣ
// 	//���������ǽṹ����ɵ����� ���պ󣬽����͹����ĺ����������ת�ɺ�����������
// 	ProtcolHeader stHeader;
// 	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
// 	//������ͷ
// 	theApp.m_P2PSocket->Receive(&stHeader, sizeof(ProtcolHeader));
// 	switch (stHeader.nMsgType)  //���յ����ͺͷ��͵�����һ��
// 	{
// 		//���� ���˵���������,������COM��ESM��Ϣ
//     case 5:
// 		{
// 			SendRequest_Msg tmpRecRequest_Msg;
// 			
// 			//�����ݾܾ��޸�
// 			::EnterCriticalSection(&(theApp.g_cs));
// 			//��ս���������Ϣ�Ľṹ��
// 			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
// 			
//             //����
// 			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
// 			{
// 				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
// 				theApp.m_P2PSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
// 				
// 			}
// 			::LeaveCriticalSection(&(theApp.g_cs));	
// 			break;
// 		}
// 	case 6://���ձ𽢷������Ĳ��ҵ��ķ�����Ϣ
// 		{
// 			SendBack_Msg tmpRecBack_Msg;
// 			//�����ݾܾ��޸�
// 			::EnterCriticalSection(&(theApp.g_cs));
// 			//��ս��շ�����Ϣ�Ľṹ��
// 			memset(&theApp.m_ReceiveBackMsg, 0, sizeof(SendBack_Msg));
// 			
//             //����
// 			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
// 			{
// 				ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
// 				theApp.m_P2PSocket->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));
// 				
// 			}
// 			::LeaveCriticalSection(&(theApp.g_cs));	
// 			break;
// 		}
// 	default:
// 		break;
// 	}
// #endif
	
}

void CNodePlatApp::SendToClient(CMsgSocket* pThis, SendRequest_Msg tmpRecRequest_Msg)
{
//0916WHY��
	VCT_UNINUM_MSG::iterator iteUnin;
	VCT_UNINOTRACE_MSG::iterator iteNoTraceUnin;
	VCT_COMM_MSG::iterator iteSingleCom;
	VCT_ESM_MSG::iterator iteSingleEsm;
	VCT_TRACE_MSG::iterator iteSingleTrace;
	VCT_ESM_MSG::iterator iteEsm;          //ͬ��λESM��Ϣ
	VCT_COMM_MSG::iterator iteComm; 
	UNI_NUM stUni;
	UNI_NOTRACE_NUM stUniNoT;
	//������Ҫд��������
	//������Ҫsendto������׼����
    //�����㷨 ׼����Ҫ���ͳ�����Ӧ���� ��������
	//����:��ʱ�̱���������б������ޱ���������Ϣ, �ڽ��������ĺ����������ṹ��, �ҳ��ķ�����Ϣ(��ת��Ϊ������ʽ�Ľṹ��)
     SendBack_Msg stSendBackMsg;
     ZeroMemory(&stSendBackMsg, sizeof(SendBack_Msg));
	 UNI_All_NUM stUniAllN;
	 //��մ洢���������ݽṹ���еĸ�����.
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
	 //�洢�������б������ޱ���������Ϣ
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
	 //�洢δ����ĵ�����Ϣ
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
     //�����㷨,�ҳ���Ӧ����ķ�����ϢstSendBackMsg
	 CoopFind_Information_To_MainShip(stUniAllN, tmpRecRequest_Msg, stSendBackMsg);

	//׼����ɣ�����
	UINT nPort = 0;
	CString strTmp;
	pThis->GetPeerName(strTmp, nPort);
	//ǰ��2����Ҫ�޸�
//	theApp.m_P2PSocket->SendTo(NULL, sizeof(theApp.m_StSendRequest), nPort, strTmp);
	theApp.m_P2PSocket->SendTo(&stSendBackMsg, sizeof(stSendBackMsg), nPort, strTmp);
	//it is ok!

// #if 0 
// 	//0903��
// 	//3\��������
// 	ProtcolHeader stHeader;
// 	VCT_SendRequest_Msg::iterator iteSendReq_Dat;
// 	VCT_SendBack_Msg::iterator iteSendBack_Dat;
// 	
// 	if (sizeof(theApp.m_StSendRequest))  //������
// 	{    
// 		//send data
// 		//����������������
// 		::EnterCriticalSection(&(theApp.g_cs));
// 		switch (theApp.cMsgType)
// 		{
// 		case 5:
// 			{
// 				stHeader.nMsgType = 5;
// 				stHeader.nMsgLength = sizeof(theApp.m_StSendRequest);
// 				for ( theApp.m_pClient =m_ClientMap.begin(); theApp.m_pClient != m_ClientMap.end(); theApp.m_pClient++)
// 				{
// 					theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
// 					theApp.m_pClient->second->Send(&theApp.m_StSendRequest, sizeof(SendRequest_Msg));
// 					
// 				}
// 				break;
// 			}
// 		default:
// 			break;
// 		}
// 	}
// 	
// 	/*
// 	//2\���͸�������Ӧ����
// 	if (have received req data)
// 	{
// 	if (�㷨�������!)
// 	{
// 	//�ش��㷨����
// 	}
// }*/
// 	if (sizeof(theApp.m_SendBackMsg))
// 	{
// 		if (/*�㷨�������*/)//����ж��㷨�Ƿ������
// 		{
// 			//�õ���Ҫ���ظ��ڽ������� (�������Ѿ�ת���ɺ����������)
// 			//���ͻش��㷨������
// 			::EnterCriticalSection(&(theApp.g_cs));
// 			switch (theApp.cMsgType)
// 			{
// 			case 6:
// 				{
// 					stHeader.nMsgType = 6;
// 					stHeader.nMsgLength = sizeof(theApp.m_SendBackMsg);
// 					for ( theApp.m_pClient = m_ClientMap.begin(); theApp.m_pClient != m_ClientMap.end(); theApp.m_pClient++)
// 					{
// 						theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
// 						theApp.m_pClient->second->Send(&theApp.m_SendBackMsg, sizeof(SendBack_Msg));						
// 					}
// 					break;
// 				}
// 			default:
// 				break;
// 			}	
// 		}
// 	}
// #endif
}

void CNodePlatApp::OnSendmsg() /*map<int, CString> IpMap*//*vector<IP>*/
{
	// TODO: Add your command handler code here
	AfxMessageBox("ok");
//#if 0
//0914��
	//��ȡ��Ҫ����ʶ�����Ϣ����ת���ɷ��ͱ��ĵĽṹ
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;	
	VCT_Request_Cooperative_Msg::iterator iteReqCoopMsg;
	Request_Cooperative_Msg m_StRequest;      //��������ʶ��ǰ�����ŵı�����Ϣ
	long int lnum;//����ĺ�����
	lnum = theApp.m_ESM_Dat.at(theApp.m_iline).lAutonum;//��ȡ����Эͬ������
	
	m_StRequest.vctEsm.clear();
	m_StRequest.vctComm.clear();
	memset(&(m_StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK));
	memset(&m_StRequest, 0, sizeof(Request_Cooperative_Msg));//��ձ�������ʶ��ǰ��Ϣ�Ľṹ��		
	memset(&theApp.m_StSendRequest, 0, sizeof(SendRequest_Msg));//��շ�������Ľṹ��

	for ( iteReqCoopMsg = theApp.m_RequestMsg.begin(); iteReqCoopMsg != theApp.m_RequestMsg.end(); iteReqCoopMsg++)
	{ 
		iteReqCoopMsg->lAutonum = NULL;
		iteReqCoopMsg->nCorrFlag = NULL;
		iteReqCoopMsg->nStampTime = NULL;
		memset(&iteReqCoopMsg->stTrace, 0, sizeof(TRACKSTATUS_MARK));
		memset(&iteReqCoopMsg->stReqShipPosi, 0, sizeof(SHIP_POSITION));
		for ( iteEsm = iteReqCoopMsg->vctEsm.begin(); iteEsm != iteReqCoopMsg->vctEsm.end(); iteEsm++)
		{
			memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
		}
		for ( iteComm = iteReqCoopMsg->vctComm.begin(); iteComm != iteReqCoopMsg->vctComm.end();iteComm++)
		{
			memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
		}		
	}
	theApp.m_RequestMsg.clear();
	
	/*ȡ������ʶ��ǰ�����ŵ������Ϣ���洢Line460-523*/
	if (lnum >= 8000)
	{
		for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
		{
			if (iteYes->lAutonum == lnum)
			{
				m_StRequest.lAutonum = lnum;//������
				m_StRequest.stTrace = iteYes->structTrace;//����ЭͬTRACE��Ϣ
				if (iteYes->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteYes->vctEsm.begin(); iteEsm = iteYes->vctEsm.end(); iteEsm++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteYes->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteYes->vctComm.begin(); iteComm = iteYes->vctComm.end(); iteComm++)
					{
						m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				////��ű�����γ��
				//StRequest.stReqShipPosi.dHeight = iteYes->structTrace.d
				//StRequest.stReqShipPosi.dLati = ;
				//StRequest.stReqShipPosi.dLonti = ;
				m_StRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0
				theApp.m_RequestMsg.push_back(m_StRequest);
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
				m_StRequest.lAutonum = lnum;//������
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteNo->vctEsm.begin(); iteEsm = iteNo->vctEsm.end(); iteEsm++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteNo->vctComm.begin(); iteComm = iteNo->vctComm.end(); iteComm++)
					{
						m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				//��ű�����γ��
				// 				StRequest.stReqShipPosi.dHeight = ;
				// 				StRequest.stReqShipPosi.dLati = ;
				// 				StRequest.stReqShipPosi.dLonti = ;
				m_StRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0
				theApp.m_RequestMsg.push_back(m_StRequest);
				break;
			}
		}
	} 
	//���
	//����Ӧ�Ľڵ㷢�����ݰ�
	//��¼��ǰʱ��(���ʱ��ǰʱ��)
	
	//��ʱ�ж�
	//�жϽ��յ������Ƿ�Ϊ��?
	
	//�����Ϊ��,���յ����ݲ�������!
	//��������,��copyһ�ݵ�ǰ������;��ս��յ�buffer����
	VCT_SendBack_Msg::iterator iteBack;
	BACK_Cooperative_Msg stBackCooper;
//	TRACKSTATUS_MARK stTrace;
	ESMSTATUS_MARK stEsm;
	COMSTATUS_MARK stCom;
//	SHIP_POSITION stBackShipPosi;            //Ӧ�𽢵ľ�γ��

	//for (int i = 0; i < theApp.IpMap.size(); ++i)
	//�������map�ǽ��洫�����ģ�������ȫ�ֵ��Ǹ�map��ȫ�ֵ�map�Ǹ�������õġ�������ѡ��B���������vector����B����
	for (int i = 0; i < IpMap.size(); ++i)
	{	
		//���/*����ṹ��*/
		if (lnum >= 8000)
		{
			for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
			{
				if (iteYes->lAutonum == lnum)
				{	
					/*����ṹ��*/
					//StSendRequest.num ++;//��Ϣ��Ԫ���???????????????
					//long int nStampTime;             //����������Ϣʱ�ĵ�ǰʱ��??????????
					theApp.m_StSendRequest.lAutomn = lnum;//������
					theApp.m_StSendRequest.stTrace = iteYes->structTrace;//����ЭͬTRACE��Ϣ
					theApp.m_StSendRequest.nRequestEsmN = iteYes->vctEsm.size();
					theApp.m_StSendRequest.nRequestComN = iteYes->vctComm.size();
					for (int i = 0; i <= iteYes->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i <= iteYes->vctComm.size();i++)//����ЭͬCOMM��Ϣ
					{
						theApp.m_StSendRequest.lComTargetNumber[i] = iteYes->vctComm.at(i).lTargetNumber;//Ŀ��comm����
						theApp.m_StSendRequest.dComZaiPin[i] = iteYes->vctComm.at(i).dComZaiPin;//��Ƶ��Ϣ
						theApp.m_StSendRequest.dComPulseExtent[i] = iteYes->vctComm.at(i).dPulseExtent;//�������
					}
					//StSendRequest.stReqShipPosi.dHeight = ;//������γ��
					//StSendRequest.stReqShipPosi.dLati = ;
					//StSendRequest.stReqShipPosi.dLonti = ;
					theApp.m_StSendRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0					
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
					/*����ṹ��*/				
					//StSendRequest.num ++;//��Ϣ��Ԫ���???????????????
					//long int nStampTime;                     //����������Ϣʱ�ĵ�ǰʱ��
					theApp.m_StSendRequest.lAutomn = lnum;//������
					//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);//����ЭͬTRACE��Ϣ
					theApp.m_StSendRequest.nRequestEsmN = iteNo->vctEsm.size();
					theApp.m_StSendRequest.nRequestComN = iteNo->vctComm.size();
					for (int i = 0; i <= iteNo->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i <= iteNo->vctComm.size();i++)//����ЭͬCOMM��Ϣ
					{
						theApp.m_StSendRequest.lComTargetNumber[i] = iteNo->vctComm.at(i).lTargetNumber;//Ŀ��comm����
						theApp.m_StSendRequest.dComZaiPin[i] = iteNo->vctComm.at(i).dComZaiPin;//��Ƶ��Ϣ
						theApp.m_StSendRequest.dComPulseExtent[i] = iteNo->vctComm.at(i).dPulseExtent;//�������
						theApp.m_StSendRequest.dComFre[i] = iteNo->vctComm.at(i).dComFre; // ����Ƶ��(MHz)
						theApp.m_StSendRequest.dComBand[i] = iteNo->vctComm.at(i).dComBand; // �źŴ���(MHz)
						theApp.m_StSendRequest.dComJPN[i] = iteNo->vctComm.at(i).dComJPN; // ��������             
					}
					//StSendRequest.stReqShipPosi.dHeight = ;//������γ��
					//StSendRequest.stReqShipPosi.dLati = ;
					//StSendRequest.stReqShipPosi.dLonti = ;
					theApp.m_StSendRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0					
					break;
				}
			}
		}
		//����Ӧ�Ľڵ㷢�����ݰ�
		//��������ȫ�ֵİ������ҵ��Ǹ�IP��ַ
		iteMap = theApp.IpMap.find(i);
		//�������Ҫ��������!!!
		theApp.m_P2PSocket->Connect(iteMap->second, P2P_SERVER_PORT);
		//�����sendTo���������socket����������Ҫ��
		theApp.m_P2PSocket->SendTo(&theApp.m_StSendRequest, sizeof(theApp.m_StSendRequest), P2P_SERVER_PORT, iteMap->second);		
		//��¼��ǰʱ��(���ʱ��ǰʱ��)
			
		//��ʱ�жϣ������д��������ֱȽϸ���!!��Ҫ������д�õĻ����ϣ�



		//�жϽ��ջ�����vector�Ƿ�Ϊ��
		//if (sizeof(theApp.m_SendBackMsg))//�����Ϊ��,���յ����ݲ�������!�����Զ��Ϊtrue.
		if (theApp.m_RecvBackMsg_Dat.size() !=0 )
		{	
			//�Ƚ���ǰ�ṹ��������ת��������!!!!!!!!!��д
			for (iteBack = m_RecvBackMsg_Dat.begin(); iteBack != m_RecvBackMsg_Dat.end(); iteBack++)
			{
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
					stEsm.dMaiKuan = iteBack->dEsmZaiPin[i];
					stEsm.dTianXianScan = iteBack->dEsmTianXianScan[i];
					stBackCooper.vctEsm.push_back(stEsm);
				}
				for (int j=0; i< iteBack->BackCOMN; j++)
				{
					stCom.lTargetNumber = iteBack->lComTargetNumber[j];
					stCom.dComZaiPin = iteBack->dComZaiPin[j];
					stCom.dPulseExtent = iteBack->dComPulseExtent[j];
					stCom.dComFre = iteBack->dComFre[j];
					stCom.dComBand = iteBack->dComBand[j];
					stCom.dComJPN = iteBack->dComJPN[j];
					stBackCooper.vctComm.push_back(stCom);
				}
				theApp.m_BackMsg.push_back(stBackCooper);
			}
			//��ս��յĽṹ��/*buffer����*/
			memset(&theApp.m_SendBackMsg, 0, sizeof(SendBack_Msg));
		}					
	}

	//�����㷨
	GET_CooperateMsg_Modul(theApp.m_RequestMsg, theApp.m_BackMsg, theApp.m_CooperMsg);
	

//#endif		
}
