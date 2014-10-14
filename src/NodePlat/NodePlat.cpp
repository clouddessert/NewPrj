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

void CNodePlatApp::SetIPLib(void)
{
	//��ȡ��ʱ·��
	CString strTmp,strTmpA;
	CString	sPath;
	
	char host_name[255];
	//��ȡ������������
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) 
	{
		//error
	}
	struct hostent *phe = gethostbyname(host_name);
	
	struct in_addr addr;
    memcpy(&addr,phe->h_addr_list[0],sizeof(struct in_addr));
	CString strLocalIP;
	strLocalIP.Format("%s", inet_ntoa(addr));
	
	//��ù����ļ���·��
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	//��ȡIP,���IP��ַ�ͱ���IPһ��,�����!
	if (::GetPrivateProfileString(_T("���IP"), _T("A��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(0, strTmp));
		}
		else
		{
			m_ThisNumber = 0;

		}
	}
	
	if (::GetPrivateProfileString(_T("���IP"), _T("B��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(1, strTmp));
		}
		else
		{
			m_ThisNumber = 1;
			
		}
	}
	if (::GetPrivateProfileString(_T("���IP"), _T("C��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(2, strTmp));
		}
		else
		{
			m_ThisNumber = 2;
			
		}
	}
	if (::GetPrivateProfileString(_T("���IP"), _T("D��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		//strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
		{
			theApp.IpMap.insert(make_pair(3, strTmp));
		}
		else
		{
			m_ThisNumber = 3;
			
		}
	}
	strTmp.ReleaseBuffer();
	if (::GetPrivateProfileString(_T("���IP"), _T("E��IP��ַ"), NULL, strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath))
	{
		//strTmp.ReleaseBuffer();
		if (strTmp.Compare(strLocalIP))
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


void CNodePlatApp::ServerCreate(void)
{
	//��ini�ļ�����IP��
	SetIPLib();

	//����p2pģʽsocket�ķ����//��ʼ����
	theApp.m_P2PSocket = new CMsgSocket();
	theApp.m_P2PSocket->Socket();
	theApp.m_P2PSocket->Bind(P2P_SERVER_PORT);
	theApp.m_P2PSocket->Listen();
	theApp.m_P2PSocket->AsyncSelect(FD_ACCEPT);

	//p2p�ͻ���socket��ʼ��
	for (int x = 0; x < 5; ++x)
	{
		theApp.m_P2PClient[x] = new CSocket();
	}

	//����ͬ��ʱ��
	hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
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

	//�ͷż�������Դ
	for (int x = 0; x < 5; ++x)
	{
		delete theApp.m_P2PClient[x];
		theApp.m_P2PClient[x] = NULL;
	}

	//�ر��ź���
	::CloseHandle(hEvent);

	//���IP��
	theApp.IpMap.clear();
}

void CNodePlatApp::ClientAccept(void)
{	
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMsgSocket();
	//��������
	if ( theApp.m_P2PSocket->Accept(*(theApp.pClient)) )
	{
		//�ȴ������¼�
		theApp.pClient->AsyncSelect(FD_READ);

		theApp.pClient->GetPeerName(strTmp, nPort);
		//ת��IP��ַ����Ϊ��־
		dwClientIP = inet_addr(strTmp.GetBuffer(0));
		strTmp.ReleaseBuffer();
		
		//����map
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
			//ɾ����Դ
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
			//�ر�SOCKET
			theApp.m_pClient->second->Close();
			delete (theApp.m_pClient->second);
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
	/*********************�����ܷ����***************************/
	//char* crevchar = new char;
	//pThis->Receive(crevchar, sizeof(char));
	/*********************���Խ���*******************************/

	//���հ�ͷ
	//���ݰ�ͷ��������״̬��
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	pThis->Receive(&stHeader, sizeof(ProtcolHeader));		//�����ָ�붼��pThis
	switch (stHeader.nMsgType)
	{
		//������յ�������
	case 11:
		{
			//���յ�����
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_RecvReqMsg_Dat.clear();
			ZeroMemory(&theApp.tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			pThis->Receive(&theApp.tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			theApp.m_RecvReqMsg_Dat.push_back(theApp.tmpRecRequest_Msg);
			//����Ľ��ղ�Ҫ�ýṹ�壬��������ṹ���vector���������ʹ�ã�������
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
		//������յ�������
	case 12:
		//���浽���յ�buffer,over
		{
			SendBack_Msg tmpRecBack_Msg;
			::EnterCriticalSection(&(theApp.g_cs));
			ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
			pThis->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));	//����vector��������!!!!!!!
			theApp.m_RecvBackMsg_Dat.push_back(tmpRecBack_Msg);
			::LeaveCriticalSection(&(theApp.g_cs));
			break;
		}
	default:
		break;
	}		
}

void CNodePlatApp::SendToClient(CMsgSocket* pThis)
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
	CoopFind_Information_To_MainShip(stUniAllN, theApp.tmpRecRequest_Msg, stSendBackMsg);

	ProtcolHeader stHeader;                  //��ͷ��Ϣ
	//�жϷ�����Ϣ��Ϊ��,���з���
	if ( (stSendBackMsg.BackTraceN + stSendBackMsg.BackESMN +stSendBackMsg.BackCOMN) != 0)
    {
		//׼����ɣ��������ݷ���
		stHeader.nMsgType = 12;
		stHeader.nMsgLength = sizeof(stSendBackMsg);
		pThis->Send(&stHeader, sizeof(stHeader));
		pThis->Send(&stSendBackMsg, sizeof(stSendBackMsg));
    }
}