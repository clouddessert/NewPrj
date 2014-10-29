// CommandPlat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CommandPlat.h"

#include "MainFrm.h"
#include "CommandPlatDoc.h"
#include "CommandPlatView.h"

#include "gs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////
#include "LanStatusView.h"

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatApp

BEGIN_MESSAGE_MAP(CCommandPlatApp, CWinApp)
	//{{AFX_MSG_MAP(CCommandPlatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDM_SHOW_MSG, OnShowMsg)
	ON_COMMAND(IDM_START_JQ, OnStartJq)
	ON_COMMAND(IDM_STOP_JQ, OnStopJq)
	ON_COMMAND(IDM_RADAR_LIB, OnRadarLib)
	ON_COMMAND(IDM_TARGET_LIB, OnTargetLib)
	ON_COMMAND(IDM_CREATE_ST, OnCreateSt)
	ON_COMMAND(IDM_CHIOSE_ST, OnChioseSt)
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatApp construction

CCommandPlatApp::CCommandPlatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	pClient = NULL;
	pSvr = NULL;
	bThreadRun = FALSE;

	// ��ʼ���ٽ���
	::InitializeCriticalSection(&g_cs);

	//����ͬ���¼�
	hUpdateDataEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	//���¼�
	m_NewMessage.clear();

	pMsgFm = NULL;

	cMsgType = 0x00;

	m_ESM_Dat.clear();
	m_Comm_Dat.clear();
	m_Trace_Dat.clear();

	hESM_wmd = NULL;
	hCOMM_wmd = NULL;
	hTRACE_wmd = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCommandPlatApp object

CCommandPlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatApp initialization

BOOL CCommandPlatApp::InitInstance()
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
		RUNTIME_CLASS(CCommandPlatDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCommandPlatView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	//���ñ���
	m_pMainWnd->SetWindowText("����սϵͳ����ƽ̨");
	
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
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
void CCommandPlatApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCommandPlatApp message handlers

//���ݷ����߳�
DWORD WINAPI UdpDataThread(LPVOID lParam)
{
	CString str;
	str = _T("����ESM����\r\n");

	ProtcolHeader stHeader;

	VCT_ESM_MSG::iterator pESM_Dat;
	VCT_COMM_MSG::iterator pComm_Dat;
	VCT_TRACE_MSG::iterator pTrace_Dat;
	VCT_SHIP_POSITION::iterator pShip_Position;

	std::map<DWORD, SHIP_POSITION>::iterator pxx_tmp;

	OriginGEO stRef;
	PositionGEO	stVal;
	PositionPolar stOut;

	int tmp_val;

	while (theApp.bThreadRun)
	{
		::srand(NULL);
		//�������׼����
		if (WAIT_OBJECT_0 == WaitForSingleObject(theApp.hUpdateDataEvent, INFINITE))
		{
			//������������
			::EnterCriticalSection(&(theApp.g_cs));
			switch (theApp.cMsgType)
			{
			case 1:
				stHeader.nMsgType = 1;
				stHeader.nMsgLength = theApp.m_ESM_Dat.size();
				for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
				{
					pxx_tmp = theApp.m_ShipRelatePlat.find(theApp.m_pClient->first);
					if ( pxx_tmp == theApp.m_ShipRelatePlat.end() )
					{
						//none,over
					}
					else
					{
						theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
						
						for (pESM_Dat = theApp.m_ESM_Dat.begin(); pESM_Dat != theApp.m_ESM_Dat.end(); pESM_Dat++)
						{
							//Modify the Data
							tmp_val = pESM_Dat->lAutonum;
							for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
							{
								if ( tmp_val == pTrace_Dat->lTargetNumber )
								{
									break;
								}
							}
							if (pTrace_Dat != theApp.m_Trace_Dat.end())
							{
								pESM_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
								pESM_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
							}

							tmp_val = rand();
							pESM_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
							tmp_val = rand();
							pESM_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
							
							theApp.m_pClient->second->Send(&(*pESM_Dat), sizeof(ESMSTATUS_MARK));
						}
					}
				}
				str = _T("����ESM����\r\n");
				theApp.m_NewMessage.push_back(str);
				break;
			case 2:
				stHeader.nMsgType = 2;
				stHeader.nMsgLength = theApp.m_Comm_Dat.size();
				for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
				{
					pxx_tmp = theApp.m_ShipRelatePlat.find(theApp.m_pClient->first);
					if ( pxx_tmp == theApp.m_ShipRelatePlat.end() )
					{
						//none,over
					}
					else
					{
						theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
						
						for (pComm_Dat = theApp.m_Comm_Dat.begin(); pComm_Dat != theApp.m_Comm_Dat.end(); pComm_Dat++)
						{
							//Modify the Data
							tmp_val = pComm_Dat->lAutonum;
							for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
							{
								if ( tmp_val == pTrace_Dat->lTargetNumber )
								{
									break;
								}
							}
							
							if (pTrace_Dat != theApp.m_Trace_Dat.end())
							{
								pComm_Dat->dElevationAngle = pTrace_Dat->dElevationAngle;
								pComm_Dat->dReachAzimuth = pTrace_Dat->dAzimuth;
							}

							tmp_val = rand();
							pComm_Dat->dReachAzimuth += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
							tmp_val = rand();
							pComm_Dat->dElevationAngle += (tmp_val>(RAND_MAX/2)?(0.01*tmp_val/RAND_MAX):(-0.01*tmp_val/RAND_MAX));
							
							theApp.m_pClient->second->Send(&(*pComm_Dat), sizeof(COMSTATUS_MARK));
						}
					}
				}
				str = _T("����ͨѶ����\r\n");
				theApp.m_NewMessage.push_back(str);
				break;
			case 3:
				stHeader.nMsgType = 3;
				stHeader.nMsgLength = theApp.m_Trace_Dat.size();
				for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
				{
					pxx_tmp = theApp.m_ShipRelatePlat.find(theApp.m_pClient->first);
					if ( pxx_tmp == theApp.m_ShipRelatePlat.end() )
					{
						//none,over
					}
					else
					{
						theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
						
						for (pTrace_Dat = theApp.m_Trace_Dat.begin(); pTrace_Dat != theApp.m_Trace_Dat.end(); pTrace_Dat++)
						{
							//Modify the Data
							stRef.dRefLon_ = pxx_tmp->second.dLonti;
							stRef.dRefLat_ = pxx_tmp->second.dLati;
							stRef.dRefAlt_ = pxx_tmp->second.dHeight;

							stVal.dLongitude = pTrace_Dat->dLonti;
							stVal.dLatitude = pTrace_Dat->dLati;
							stVal.dAltitude = pTrace_Dat->dObjHeight;	//������

							stOut = GEO2Polar(stVal, stRef);

							pTrace_Dat->dRange = stOut.dRDistance;
							pTrace_Dat->dAzimuth = stOut.dAzimuth;
							pTrace_Dat->dElevationAngle = stOut.dHLowAngle;
							
							theApp.m_pClient->second->Send(&(*pTrace_Dat), sizeof(TRACKSTATUS_MARK));
						}
					}
				}
				str = _T("���ͺ�������\r\n");
				theApp.m_NewMessage.push_back(str);
				break;
			case 4:
				stHeader.nMsgType = 4;
				stHeader.nMsgLength = theApp.m_Ship_Position.size();
				for (theApp.m_pClient = theApp.m_ClientMap.begin(); theApp.m_pClient != theApp.m_ClientMap.end(); theApp.m_pClient++)
				{
					theApp.m_pClient->second->Send(&stHeader, sizeof(ProtcolHeader));
					
					for (pShip_Position = theApp.m_Ship_Position.begin(); pShip_Position != theApp.m_Ship_Position.end(); pShip_Position++)
					{
						//Modify the Data

						theApp.m_pClient->second->Send(&(*pShip_Position), sizeof(SHIP_POSITION));
					}
				}
				break;
			default:
				break;
			}
			::LeaveCriticalSection(&(theApp.g_cs));
		}
		//������Ϣ
		ResetEvent(theApp.hUpdateDataEvent);
	}
	
	return(0);
}

void CCommandPlatApp::ServerCreate(void)
{
	theApp.m_ClientMap.clear();
	theApp.m_pClient = NULL;
	
	//�½�����
	theApp.pSvr = new CMySocket();
	
	//����socket
	theApp.pSvr->Socket();
	//�󶨼����˿�
	theApp.pSvr->Bind(SERVERPORT);
	//��ʼ����
	theApp.pSvr->Listen();
}

void CCommandPlatApp::ServerShutDown(void)
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
	theApp.pSvr->Close();
	//�ͷż�������Դ
	delete theApp.pSvr;
	theApp.pSvr = NULL;
}

void CCommandPlatApp::ClientAccept(void)
{
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMySocket();
	//��������
	theApp.pSvr->Accept(*(theApp.pClient));
	
	theApp.pClient->GetPeerName(strTmp, nPort);
	//ת��IP��ַ����Ϊ��־
	dwClientIP = inet_addr(strTmp.GetBuffer(0));
	strTmp.ReleaseBuffer();
	
	//����map
	map<DWORD, CMySocket*>::iterator pTmpItor;
	pTmpItor = theApp.m_ClientMap.find(dwClientIP);
	if (theApp.m_ClientMap.end() == pTmpItor)
	{
		//none
	}
	else
	{
		//�����Ѿ��е�socket�رգ��������µ�
		//release resource
		pTmpItor->second->Close();
		delete (pTmpItor->second);
		//ɾ����Դ
		theApp.m_ClientMap.erase(pTmpItor);
	}
	//����map
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.m_ClientMap.insert(map<DWORD, CMySocket*>::value_type(dwClientIP, theApp.pClient));

	//add bu fy 10.28
	std::map<DWORD, SHIP_POSITION>::iterator pxx;
	pxx = theApp.m_ShipRelatePlat.find(dwClientIP);
	if ( pxx == theApp.m_ShipRelatePlat.end() )
	{
		theApp.m_ShipRelatePlat.insert(std::map<DWORD, SHIP_POSITION>::value_type(dwClientIP, *p_CurrentShip));
		++p_CurrentShip;
	}

	::LeaveCriticalSection(&(theApp.g_cs));

	CString str = _T("ʲô�ͻ����Ѿ����ӽ���\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::ClientMsgReceive(void)
{
	
}

void CCommandPlatApp::ClientClose(void* pContext)
{
	CMySocket* pSk = (CMySocket*)pContext;
	
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

	CString str = _T("ʲô�ͻ��˶�ʧ\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::OnShowMsg() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("������IP��ַ:127.0.0.1;�˿ں�:8001"));
}

void CCommandPlatApp::OnStartJq() 
{
	// TODO: Add your command handler code here
	//clear data
	theApp.m_ESM_Dat.clear();
	theApp.m_Comm_Dat.clear();
	theApp.m_Trace_Dat.clear();
	theApp.m_Ship_Position.clear();

	theApp.m_ShipRelatePlat.clear();

	//init data
	ESMSTATUS_MARK stEsmStatus;
	COMSTATUS_MARK  stComStatus;
	TRACKSTATUS_MARK stTrackStatus;
	SHIP_POSITION stShipPosition;

	//Ship Position(Modify By Clouddessert)
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 119.0;
	stShipPosition.dLati = 22.5;
	theApp.m_Ship_Position.push_back(stShipPosition); //��1

	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 118.9;
	stShipPosition.dLati = 22.4;
	theApp.m_Ship_Position.push_back(stShipPosition); //��2
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 119.1;
	stShipPosition.dLati = 22.6;
	theApp.m_Ship_Position.push_back(stShipPosition); //��3
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 119.15;
	stShipPosition.dLati = 22.7;
	theApp.m_Ship_Position.push_back(stShipPosition); //��4
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 118.85;
	stShipPosition.dLati = 22.2;
	theApp.m_Ship_Position.push_back(stShipPosition); //��5
	//����ע��5��������һ���õ������ǿ��Զඨ�塣����ע�⣬����5��������Ҫ��Ӷ��壡����
	p_CurrentShip = theApp.m_Ship_Position.begin();

//ESM
	stEsmStatus.lAutonum = 5001;
	stEsmStatus.lTargetNumber = 3001;
    stEsmStatus.dReachAzimuth =(float)35.0;
//	stEsmStatus.sPlatType = 117;   //1��ʾF117,2��ʾF118,3��ʾF119,4��ʾF120
    strcpy(stEsmStatus.sPlatType,_T("F117")); 
	stEsmStatus.dConfidence = (float)0.8;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 5;
	stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("�ɻ�"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("50"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("001")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
//10.13 �źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����, 
	stEsmStatus.dThreatLevel = 2;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 10;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 8.1;
	stEsmStatus.dPulseExtent = 2.5;
	stEsmStatus.dElevationAngle = 45.3;
	stEsmStatus.dMaiChongFeature = 3.0;
	theApp.m_ESM_Dat.push_back(stEsmStatus);
	
	stEsmStatus.lAutonum = 5001;
   	stEsmStatus.lTargetNumber = 3002;
	stEsmStatus.dReachAzimuth =(float)50.0;
//	stEsmStatus.sPlatType = 118;
	strcpy(stEsmStatus.sPlatType,_T("F118")); 
	stEsmStatus.dConfidence = (float)0.4;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 3;
	stEsmStatus.dMaiKuan = 5;
    stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("����"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("51"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("002")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
//10.13 �źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����,
	stEsmStatus.dThreatLevel = 3;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 12;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 9.1;
	stEsmStatus.dPulseExtent = 1.5;
	stEsmStatus.dElevationAngle = 35.3;
	stEsmStatus.dMaiChongFeature = 2.0;
    theApp.m_ESM_Dat.push_back(stEsmStatus);
	
	stEsmStatus.lAutonum = 5002;
   	stEsmStatus.lTargetNumber = 3003;
	stEsmStatus.dReachAzimuth =(float)40.0;
//	stEsmStatus.sPlatType = 119;
	strcpy(stEsmStatus.sPlatType,_T("F119")); 
	stEsmStatus.dConfidence = (float)0.6;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 5;
    stEsmStatus.dTianXianScan = 6;
	strcpy(stEsmStatus.cPlatName,_T("��ͧ"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("52"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("003")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
//10.13 �źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����,
	stEsmStatus.dThreatLevel = 5;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 11;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 7.1;
	stEsmStatus.dPulseExtent = 2.7;
	stEsmStatus.dElevationAngle = 40.3;
	stEsmStatus.dMaiChongFeature = 2.7;
	theApp.m_ESM_Dat.push_back(stEsmStatus);
	
	stEsmStatus.lAutonum = 5002;
   	stEsmStatus.lTargetNumber = 3004;
	stEsmStatus.dReachAzimuth =(float)34.2;
//	stEsmStatus.sPlatType = 118;
	strcpy(stEsmStatus.sPlatType,_T("F118")); 
	stEsmStatus.dConfidence = (float)0.8;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 6;
    stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("�ɻ�"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("53"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("004")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
//10.13 �źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����,
	stEsmStatus.dThreatLevel = 3;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 10;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 8.5;
	stEsmStatus.dPulseExtent = 2.7;
	stEsmStatus.dElevationAngle = 40.3;
	stEsmStatus.dMaiChongFeature = 2.9;
	theApp.m_ESM_Dat.push_back(stEsmStatus);
	
	stEsmStatus.lAutonum = 5001;
   	stEsmStatus.lTargetNumber = 3005;
	stEsmStatus.dReachAzimuth =(float)35.0;
//	stEsmStatus.sPlatType = 120;
	strcpy(stEsmStatus.sPlatType,_T("F120")); 
	stEsmStatus.dConfidence = (float)0.3;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 3;
	stEsmStatus.dMaiKuan = 4;
    stEsmStatus.dTianXianScan = 4;
	strcpy(stEsmStatus.cPlatName,_T("��ͧ"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("54"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("005")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
// 10.13�źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����,
	stEsmStatus.dThreatLevel = 4;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 15;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 7.8;
	stEsmStatus.dPulseExtent = 1.8;
	stEsmStatus.dElevationAngle = 38.3;
	stEsmStatus.dMaiChongFeature = 4.0;
	theApp.m_ESM_Dat.push_back(stEsmStatus);
	
	stEsmStatus.lAutonum = 5002;
   	stEsmStatus.lTargetNumber = 3006;
	stEsmStatus.dReachAzimuth =(float)35.0;
//	stEsmStatus.sPlatType = 118;
	strcpy(stEsmStatus.sPlatType,_T("F118")); 
	stEsmStatus.dConfidence = (float)0.5;
	stEsmStatus.cJfFlag = 0;
//10.13	//��Ƶ//����//����ɨ��
	stEsmStatus.dChongPin = 5;
	stEsmStatus.dMaiKuan = 4;
    stEsmStatus.dTianXianScan = 6;
	strcpy(stEsmStatus.cPlatName,_T("����"));       //ƽ̨����
	strcpy(stEsmStatus.cPlatNumber,_T("55"));   //ƽ̨���
    strcpy(stEsmStatus.cEquipmentNumber,_T("006")); //�豸���
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //�豸����
//10.13 �źŵ���ʱ��,��в�ȼ�,��Ч����Ƶ��,����/����,��������,�״���;,�״�����,
	stEsmStatus.dThreatLevel = 5;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 13;
	strcpy(stEsmStatus.cCountry,_T("�й�"));
	strcpy(	stEsmStatus.cDWAttribute,_T("�ҷ�"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("Ŀ��̽��"));
	strcpy(	stEsmStatus.cRadarName,_T("Ŀ��̽���״�"));
//10.13 ��Ƶ��Ϣ��������ȣ����ǣ���������
	stEsmStatus.dZaiPin = 5.5;
	stEsmStatus.dPulseExtent = 3.5;
	stEsmStatus.dElevationAngle = 38.3;
	stEsmStatus.dMaiChongFeature = 3.0;
	theApp.m_ESM_Dat.push_back(stEsmStatus);
	
//COM
	stComStatus.lAutonum = 5001;
	stComStatus.lTargetNumber = 4001;
	stComStatus.dReachAzimuth =(float)35.0;
//	stComStatus.sPlatType = 117;
	strcpy(stComStatus.sPlatType,_T("F117")); 
	stComStatus.dConfidence = (float)0.5;
	stComStatus.cJfFlag = 0;
//10.13��Ƶ,�������
	stComStatus.dComZaiPin = 3.5;
	stComStatus.dPulseExtent = 2.0;
	strcpy(stComStatus.cPlatName,_T("��ͧ"));       //ƽ̨����
	strcpy(stComStatus.cPlatNumber,_T("50"));   //ƽ̨���
    strcpy(stComStatus.cEquipmentNumber,_T("001")); //�豸���
	strcpy(stComStatus.cEquipmentType,_T("COM")); //�豸����
//10.13�źŵ���ʱ��,�ź�����,������ʽ,��������,����/����
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" �����ź�"));
	strcpy(stComStatus.cModulationStyle ,_T("A��ʽ")); 
	strcpy(stComStatus.cDWAttribute ,_T("�ҷ�")); 
	strcpy(stComStatus.cCountry  ,_T("�й�")); 

	theApp.m_Comm_Dat.push_back(stComStatus);
	
	stComStatus.lAutonum = 5001;
	stComStatus.lTargetNumber = 4002;
	stComStatus.dReachAzimuth =(float)20.0;
//	stComStatus.sPlatType = 119;
    strcpy(stComStatus.sPlatType,_T("F119")); 
	stComStatus.dConfidence = (float)0.6;
	stEsmStatus.cJfFlag = 0;
//10.13��Ƶ,�������
	stComStatus.dComZaiPin = 4.0;
	stComStatus.dPulseExtent = 2.0;
	strcpy(stComStatus.cPlatName,_T("�ɻ�"));       //ƽ̨����
	strcpy(stComStatus.cPlatNumber,_T("51"));   //ƽ̨���
    strcpy(stComStatus.cEquipmentNumber,_T("002")); //�豸���
	strcpy(stComStatus.cEquipmentType,_T("COM")); //�豸����
	//10.13�źŵ���ʱ��,�ź�����,������ʽ,��������,����/����
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" �����ź�"));
	strcpy(stComStatus.cModulationStyle ,_T("B��ʽ")); 
	strcpy(stComStatus.cDWAttribute ,_T("�ҷ�")); 
	strcpy(stComStatus.cCountry  ,_T("�й�")); 

	theApp.m_Comm_Dat.push_back(stComStatus);
	
	stComStatus.lAutonum = 5002;
	stComStatus.lTargetNumber = 4003;
	stComStatus.dReachAzimuth =(float)40.0;
//	stComStatus.sPlatType = 119;
    strcpy(stComStatus.sPlatType,_T("F119")); 
	stComStatus.dConfidence = (float)0.3;
	stEsmStatus.cJfFlag = 0;
//10.13��Ƶ,�������
	stComStatus.dComZaiPin = 3.5;
	stComStatus.dPulseExtent = 3.0;
	strcpy(stComStatus.cPlatName,_T("����"));       //ƽ̨����
	strcpy(stComStatus.cPlatNumber,_T("52"));   //ƽ̨���
    strcpy(stComStatus.cEquipmentNumber,_T("003")); //�豸���
	strcpy(stComStatus.cEquipmentType,_T("COM")); //�豸����
	//10.13�źŵ���ʱ��,�ź�����,������ʽ,��������,����/����
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" �����ź�"));
	strcpy(stComStatus.cModulationStyle ,_T("C��ʽ")); 
	strcpy(stComStatus.cDWAttribute ,_T("�ҷ�")); 
	strcpy(stComStatus.cCountry  ,_T("�й�")); 

	theApp.m_Comm_Dat.push_back(stComStatus);

//TRACK	
	stTrackStatus.lTargetNumber = 5001;
	stTrackStatus.dAzimuth =(float)35.0;
//	stTrackStatus.sPlatType = 117;          //ƽ̨����
    strcpy(stTrackStatus.sPlatType ,_T("F117"));
	stTrackStatus.dConfidence = (float)0.3;
	stTrackStatus.cJfFlag = 0;
	stTrackStatus.dLonti = (float)118.20;   //Ŀ�꾭�� 
	stTrackStatus.dLati = (float)24.10;     //Ŀ��γ��
	stTrackStatus.dObjHeight = (float)500.0;	//Ŀ��߶�
	strcpy(stTrackStatus.cPlatName,_T("�ɻ�1"));       //ƽ̨����
	strcpy(stTrackStatus.cPlatNumber,_T("50"));   //ƽ̨���
    strcpy(stTrackStatus.cEquipmentNumber,_T("001")); //�豸���
	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //�豸����

	theApp.m_Trace_Dat.push_back(stTrackStatus);

	stTrackStatus.lTargetNumber = 5002;
	stTrackStatus.dAzimuth =(float)40.0;
//	stTrackStatus.sPlatType = 118;
	strcpy(stTrackStatus.sPlatType,_T("F118")); 
	stTrackStatus.dConfidence = (float)0.2;
	stTrackStatus.cJfFlag = 0;
	stTrackStatus.dLonti = (float)117.30;   //Ŀ�꾭��
	stTrackStatus.dLati = (float)24.20;     //Ŀ��γ��
	stTrackStatus.dObjHeight = (float)800.0;	//Ŀ��߶�
	strcpy(stTrackStatus.cPlatName,_T("�ɻ�2"));       //ƽ̨����
	strcpy(stTrackStatus.cPlatNumber,_T("51"));   //ƽ̨���
    strcpy(stTrackStatus.cEquipmentNumber,_T("002")); //�豸���
	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //�豸����
	theApp.m_Trace_Dat.push_back(stTrackStatus);

// 	stTrackStatus.lTargetNumber = 5003;
// 	stTrackStatus.fAzimuth =(float)35.0;
// 	stTrackStatus.sPlatType = 119;
// 	stTrackStatus.dConfidence = (float)0.5;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)116.40;   //Ŀ�꾭��
// 	stTrackStatus.fLati = (float)24.30;     //Ŀ��γ��
// 	strcpy(stTrackStatus.cPlatName,_T("����"));     //ƽ̨����
// 	strcpy(stTrackStatus.cPlatNumber,_T("52"));   //ƽ̨���
//     strcpy(stTrackStatus.cEquipmentNumber,_T("003")); //�豸���
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //�豸����
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
// 
// 	stTrackStatus.lTargetNumber = 5004;
// 	stTrackStatus.fAzimuth =(float)35.0;
// 	stTrackStatus.sPlatType = 119;
// 	stTrackStatus.dConfidence = (float)0.4;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)119.40;  //Ŀ�꾭��
// 	stTrackStatus.fLati = (float)24.30;    //Ŀ��γ��
// 	strcpy(stTrackStatus.cPlatName,_T("��ͧ"));     //ƽ̨����
// 	strcpy(stTrackStatus.cPlatNumber,_T("53"));   //ƽ̨���
//     strcpy(stTrackStatus.cEquipmentNumber,_T("004")); //�豸���
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //�豸����
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
// 
// 	stTrackStatus.lTargetNumber = 5005;
// 	stTrackStatus.fAzimuth =(float)55.0;
// 	stTrackStatus.sPlatType = 120;
// 	stTrackStatus.dConfidence = (float)0.6;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)118.50;  //Ŀ�꾭��
// 	stTrackStatus.fLati = (float)25.40;    //Ŀ��γ��
// 	strcpy(stTrackStatus.cPlatName,_T("�ɻ�2"));     //ƽ̨����
// 	strcpy(stTrackStatus.cPlatNumber,_T("54"));     //ƽ̨���
//     strcpy(stTrackStatus.cEquipmentNumber,_T("005")); //�豸���
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //�豸����
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
    
	//��������
	ServerCreate();

	//create thread 
	theApp.bThreadRun = TRUE;
	DWORD dwThreadID = 0;
	::CreateThread(NULL, 0, UdpDataThread, NULL, 0, &dwThreadID);

	CLanStatusView* pTp = (CLanStatusView*)theApp.pMsgFm;
	pTp->ClearMessages();

	CString str = _T("����������\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::OnStopJq() 
{
	// TODO: Add your command handler code here
	ServerShutDown();

	theApp.bThreadRun = FALSE;
	
	//clear data
	theApp.m_ESM_Dat.clear();
	theApp.m_Comm_Dat.clear();
	theApp.m_Trace_Dat.clear();
	theApp.m_Ship_Position.clear();


	//update List
	::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 1, 0);
	::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 1, 0);
	::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 1, 0);

	CString str = _T("�رշ�����\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::OnRadarLib() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("�����״��"));
}

void CCommandPlatApp::OnTargetLib() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("����Ŀ���"));
}

void CCommandPlatApp::OnCreateSt() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("�����µ�̬�ƣ�δ���ƣ�����"));
}

void CCommandPlatApp::OnChioseSt() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("ѡ�����е�̬�ƣ�δ���ƣ�����"));
}
