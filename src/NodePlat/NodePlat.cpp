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
//����socket
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
#if 0
	//0914��
	//���հ�ͷ
	//���ݰ�ͷ��������״̬��
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	theApp.m_P2PSocket->Receive(&stHeader, sizeof(ProtcolHeader));
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
			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				theApp.m_P2PSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
			}
			//���ò���ƥ���������Ϣ���㷨,�����޸��㷨�ӿ�
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
		
	case 12:
		//���յı��˵�����
		//���浽���յ�buffer,over?????????????
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
    //0903��
	//\���� ���˵��������� 	//4\�����ڽ��������Ĳ��ҵ��ķ�����Ϣ
	//���������ǽṹ����ɵ����� ���պ󣬽����͹����ĺ����������ת�ɺ�����������
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	//������ͷ
	theApp.m_P2PSocket->Receive(&stHeader, sizeof(ProtcolHeader));
	switch (stHeader.nMsgType)  //���յ����ͺͷ��͵�����һ��
	{
		//���� ���˵���������,������COM��ESM��Ϣ
    case 5:
		{
			SendRequest_Msg tmpRecRequest_Msg;
			
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			//��ս���������Ϣ�Ľṹ��
			memset(&theApp.m_StReceiveRequest, 0, sizeof(SendRequest_Msg));
			
            //����
			for (int nNum = 1; nNum <= stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				theApp.m_P2PSocket->Receive(&tmpRecRequest_Msg, sizeof(SendRequest_Msg));
				
			}
			::LeaveCriticalSection(&(theApp.g_cs));	
			break;
		}
	case 6://���ձ𽢷������Ĳ��ҵ��ķ�����Ϣ
		{
			SendBack_Msg tmpRecBack_Msg;
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			//��ս��շ�����Ϣ�Ľṹ��
			memset(&theApp.m_ReceiveBackMsg, 0, sizeof(SendBack_Msg));
			
            //����
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
	//0903��
	//3\��������
	ProtcolHeader stHeader;
	VCT_SendRequest_Msg::iterator iteSendReq_Dat;
	VCT_SendBack_Msg::iterator iteSendBack_Dat;
	
	if (sizeof(theApp.m_StSendRequest))  //������
	{    
		//send data
		//����������������
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
	//2\���͸�������Ӧ����
	if (have received req data)
	{
	if (�㷨�������!)
	{
	//�ش��㷨����
	}
}*/
	if (sizeof(theApp.m_SendBackMsg))
	{
		if (/*�㷨�������*/)//����ж��㷨�Ƿ������
		{
			//�õ���Ҫ���ظ��ڽ������� (�������Ѿ�ת���ɺ����������)
			//���ͻش��㷨������
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
//0914��
	//��ȡ��Ҫ����ʶ�����Ϣ����ת���ɷ��ͱ��ĵĽṹ
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;
	long int lnum;//����ĺ�����
	lnum = theApp.m_ESM_Dat.at(theApp.m_iline).lAutonum;//��ȡ����Эͬ������
	
	theApp.m_StRequest.vctEsm.clear();
	theApp.m_StRequest.vctComm.clear();
	memset(&(theApp.m_StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK));
	memset(&theApp.m_StRequest, 0, sizeof(Request_Cooperative_Msg));//��ձ�������ʶ��ǰ��Ϣ�Ľṹ��		
	memset(&theApp.m_StSendRequest, 0, sizeof(SendRequest_Msg));//��շ�������Ľṹ��
	
	/*ȡ������ʶ��ǰ�����ŵ������Ϣ���洢Line460-523*/
	if (lnum >= 8000)
	{
		for (iteYes = theApp.m_ClusterUniMsg.begin(); iteYes != theApp.m_ClusterUniMsg.end(); iteYes++)
		{
			if (iteYes->lAutonum == lnum)
			{
				theApp.m_StRequest.lAutonum = lnum;//������
				theApp.m_StRequest.stTrace = iteYes->structTrace;//����ЭͬTRACE��Ϣ
				if (iteYes->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteYes->vctEsm.begin(); iteEsm = iteYes->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteYes->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteYes->vctComm.begin(); iteComm = iteYes->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				////��ű�����γ��
				//StRequest.stReqShipPosi.dHeight = iteYes->structTrace.d
				//StRequest.stReqShipPosi.dLati = ;
				//StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0

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
				theApp.m_StRequest.lAutonum = lnum;//������
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteNo->vctEsm.begin(); iteEsm = iteNo->vctEsm.end(); iteEsm++)
					{
						theApp.m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteNo->vctComm.begin(); iteComm = iteNo->vctComm.end(); iteComm++)
					{
						theApp.m_StRequest.vctComm.push_back(*iteComm);
					}
				}
				//��ű�����γ��
				// 				StRequest.stReqShipPosi.dHeight = ;
				// 				StRequest.stReqShipPosi.dLati = ;
				// 				StRequest.stReqShipPosi.dLonti = ;
				theApp.m_StRequest.nCorrFlag = 0;//������Ϣ�Ľṹ���Ƿ��ҵ��������Ϣ�ı�־��ʼ��Ϊ0
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

	for (int i = 0; i < theApp.IpMap.size(); ++i)
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
		iteMap = theApp.IpMap.find(i);
		theApp.m_P2PSocket->SendTo(&theApp.m_StSendRequest, sizeof(theApp.m_StSendRequest), P2P_SERVER_PORT, iteMap->second,0);		
		//��¼��ǰʱ��(���ʱ��ǰʱ��)
			
		//��ʱ�ж�

		//�жϽ��յ���Ϣ�Ƿ�Ϊ��		
		if (sizeof(theApp.m_SendBackMsg))//�����Ϊ��,���յ����ݲ�������!
		{	
			//�Ƚ���ǰ�ṹ��������ת��������!!!!!!!!!��д


			//�ٽ�ת����Ľṹ�����������������������ʶ��
		//	m_BackMsg.push_back(/*ת����Ľṹ��*/);
			//��ս��յĽṹ��/*buffer����*/
			memset(&theApp.m_SendBackMsg, 0, sizeof(SendBack_Msg));
		}
			
			
			
	}

	//�����㷨




//#endif
		

		
}
