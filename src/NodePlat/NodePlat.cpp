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
	
	theApp.pClient = new CMySocket();
	//��������
	theApp.m_P2PSocket->Accept(*(theApp.pClient));
	
	theApp.pClient->GetPeerName(strTmp, nPort);
	//ת��IP��ַ����Ϊ��־
	dwClientIP = inet_addr(strTmp.GetBuffer(0));
	strTmp.ReleaseBuffer();
	
	//����map
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

void CNodePlatApp::ReceiveFromClient(void)
{
	//1\���� ���˵���������


}

void CNodePlatApp::SendToClient(void)
{
	/*
	//3\��������
	if (�費��Ҫ����)
	{
		//send data

	}

	//2\���͸�������Ӧ����
	if (have received req data)
	{
		if (�㷨�������!)
		{
			//�ش��㷨����

		}
	}*/
}