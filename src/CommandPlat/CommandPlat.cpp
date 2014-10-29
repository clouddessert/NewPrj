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

	// 初始化临界区
	::InitializeCriticalSection(&g_cs);

	//设置同步事件
	hUpdateDataEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	//无事件
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
	//设置标题
	m_pMainWnd->SetWindowText("电子战系统仿真平台");
	
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

//数据发送线程
DWORD WINAPI UdpDataThread(LPVOID lParam)
{
	CString str;
	str = _T("发送ESM数据\r\n");

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
		//如果数据准备好
		if (WAIT_OBJECT_0 == WaitForSingleObject(theApp.hUpdateDataEvent, INFINITE))
		{
			//发送所有数据
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
				str = _T("发送ESM数据\r\n");
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
				str = _T("发送通讯数据\r\n");
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
							stVal.dAltitude = pTrace_Dat->dObjHeight;	//！！！

							stOut = GEO2Polar(stVal, stRef);

							pTrace_Dat->dRange = stOut.dRDistance;
							pTrace_Dat->dAzimuth = stOut.dAzimuth;
							pTrace_Dat->dElevationAngle = stOut.dHLowAngle;
							
							theApp.m_pClient->second->Send(&(*pTrace_Dat), sizeof(TRACKSTATUS_MARK));
						}
					}
				}
				str = _T("发送航迹数据\r\n");
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
		//重置消息
		ResetEvent(theApp.hUpdateDataEvent);
	}
	
	return(0);
}

void CCommandPlatApp::ServerCreate(void)
{
	theApp.m_ClientMap.clear();
	theApp.m_pClient = NULL;
	
	//新建对象
	theApp.pSvr = new CMySocket();
	
	//创建socket
	theApp.pSvr->Socket();
	//绑定监听端口
	theApp.pSvr->Bind(SERVERPORT);
	//开始监听
	theApp.pSvr->Listen();
}

void CCommandPlatApp::ServerShutDown(void)
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
	theApp.pSvr->Close();
	//释放监听端资源
	delete theApp.pSvr;
	theApp.pSvr = NULL;
}

void CCommandPlatApp::ClientAccept(void)
{
	CString strTmp;
	UINT nPort = 0;
	DWORD dwClientIP = 0;
	
	theApp.pClient = new CMySocket();
	//接受连接
	theApp.pSvr->Accept(*(theApp.pClient));
	
	theApp.pClient->GetPeerName(strTmp, nPort);
	//转换IP地址，作为标志
	dwClientIP = inet_addr(strTmp.GetBuffer(0));
	strTmp.ReleaseBuffer();
	
	//存入map
	map<DWORD, CMySocket*>::iterator pTmpItor;
	pTmpItor = theApp.m_ClientMap.find(dwClientIP);
	if (theApp.m_ClientMap.end() == pTmpItor)
	{
		//none
	}
	else
	{
		//发现已经有的socket关闭，再申请新的
		//release resource
		pTmpItor->second->Close();
		delete (pTmpItor->second);
		//删除资源
		theApp.m_ClientMap.erase(pTmpItor);
	}
	//存入map
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

	CString str = _T("什么客户端已经连接进入\r\n");
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

	CString str = _T("什么客户端丢失\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::OnShowMsg() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("服务器IP地址:127.0.0.1;端口号:8001"));
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
	theApp.m_Ship_Position.push_back(stShipPosition); //舰1

	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 118.9;
	stShipPosition.dLati = 22.4;
	theApp.m_Ship_Position.push_back(stShipPosition); //舰2
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 119.1;
	stShipPosition.dLati = 22.6;
	theApp.m_Ship_Position.push_back(stShipPosition); //舰3
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 119.15;
	stShipPosition.dLati = 22.7;
	theApp.m_Ship_Position.push_back(stShipPosition); //舰4
	stShipPosition.dHeight = 0.0;
	stShipPosition.dLonti = 118.85;
	stShipPosition.dLati = 22.2;
	theApp.m_Ship_Position.push_back(stShipPosition); //舰5
	//这里注意5条船，不一定用到，但是可以多定义。这里注意，超多5条船，需要添加定义！！！
	p_CurrentShip = theApp.m_Ship_Position.begin();

//ESM
	stEsmStatus.lAutonum = 5001;
	stEsmStatus.lTargetNumber = 3001;
    stEsmStatus.dReachAzimuth =(float)35.0;
//	stEsmStatus.sPlatType = 117;   //1表示F117,2表示F118,3表示F119,4表示F120
    strcpy(stEsmStatus.sPlatType,_T("F117")); 
	stEsmStatus.dConfidence = (float)0.8;
	stEsmStatus.cJfFlag = 0;
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 5;
	stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("飞机"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("50"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("001")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
//10.13 信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称, 
	stEsmStatus.dThreatLevel = 2;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 10;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 3;
	stEsmStatus.dMaiKuan = 5;
    stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("导弹"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("51"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("002")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
//10.13 信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称,
	stEsmStatus.dThreatLevel = 3;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 12;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 5;
    stEsmStatus.dTianXianScan = 6;
	strcpy(stEsmStatus.cPlatName,_T("舰艇"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("52"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("003")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
//10.13 信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称,
	stEsmStatus.dThreatLevel = 5;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 11;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 2;
	stEsmStatus.dMaiKuan = 6;
    stEsmStatus.dTianXianScan = 2;
	strcpy(stEsmStatus.cPlatName,_T("飞机"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("53"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("004")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
//10.13 信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称,
	stEsmStatus.dThreatLevel = 3;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 10;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 3;
	stEsmStatus.dMaiKuan = 4;
    stEsmStatus.dTianXianScan = 4;
	strcpy(stEsmStatus.cPlatName,_T("舰艇"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("54"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("005")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
// 10.13信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称,
	stEsmStatus.dThreatLevel = 4;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 15;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13	//载频//脉宽//天线扫描
	stEsmStatus.dChongPin = 5;
	stEsmStatus.dMaiKuan = 4;
    stEsmStatus.dTianXianScan = 6;
	strcpy(stEsmStatus.cPlatName,_T("导弹"));       //平台名称
	strcpy(stEsmStatus.cPlatNumber,_T("55"));   //平台编号
    strcpy(stEsmStatus.cEquipmentNumber,_T("006")); //设备编号
	strcpy(stEsmStatus.cEquipmentType,_T("ESM")); //设备类型
//10.13 信号到达时间,威胁等级,有效辐射频率,国家/地区,敌我属性,雷达用途,雷达名称,
	stEsmStatus.dThreatLevel = 5;
	stEsmStatus.lSignalReachTime = 1500;
	stEsmStatus.dERPower = 13;
	strcpy(stEsmStatus.cCountry,_T("中国"));
	strcpy(	stEsmStatus.cDWAttribute,_T("我方"));
	strcpy(	stEsmStatus.cRadarPurpose,_T("目标探测"));
	strcpy(	stEsmStatus.cRadarName,_T("目标探测雷达"));
//10.13 载频信息，脉冲幅度，仰角，脉冲特征
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
//10.13载频,脉冲幅度
	stComStatus.dComZaiPin = 3.5;
	stComStatus.dPulseExtent = 2.0;
	strcpy(stComStatus.cPlatName,_T("舰艇"));       //平台名称
	strcpy(stComStatus.cPlatNumber,_T("50"));   //平台编号
    strcpy(stComStatus.cEquipmentNumber,_T("001")); //设备编号
	strcpy(stComStatus.cEquipmentType,_T("COM")); //设备类型
//10.13信号到达时间,信号类型,调制样式,敌我属性,国家/地区
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" 脉冲信号"));
	strcpy(stComStatus.cModulationStyle ,_T("A样式")); 
	strcpy(stComStatus.cDWAttribute ,_T("我方")); 
	strcpy(stComStatus.cCountry  ,_T("中国")); 

	theApp.m_Comm_Dat.push_back(stComStatus);
	
	stComStatus.lAutonum = 5001;
	stComStatus.lTargetNumber = 4002;
	stComStatus.dReachAzimuth =(float)20.0;
//	stComStatus.sPlatType = 119;
    strcpy(stComStatus.sPlatType,_T("F119")); 
	stComStatus.dConfidence = (float)0.6;
	stEsmStatus.cJfFlag = 0;
//10.13载频,脉冲幅度
	stComStatus.dComZaiPin = 4.0;
	stComStatus.dPulseExtent = 2.0;
	strcpy(stComStatus.cPlatName,_T("飞机"));       //平台名称
	strcpy(stComStatus.cPlatNumber,_T("51"));   //平台编号
    strcpy(stComStatus.cEquipmentNumber,_T("002")); //设备编号
	strcpy(stComStatus.cEquipmentType,_T("COM")); //设备类型
	//10.13信号到达时间,信号类型,调制样式,敌我属性,国家/地区
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" 脉冲信号"));
	strcpy(stComStatus.cModulationStyle ,_T("B样式")); 
	strcpy(stComStatus.cDWAttribute ,_T("我方")); 
	strcpy(stComStatus.cCountry  ,_T("中国")); 

	theApp.m_Comm_Dat.push_back(stComStatus);
	
	stComStatus.lAutonum = 5002;
	stComStatus.lTargetNumber = 4003;
	stComStatus.dReachAzimuth =(float)40.0;
//	stComStatus.sPlatType = 119;
    strcpy(stComStatus.sPlatType,_T("F119")); 
	stComStatus.dConfidence = (float)0.3;
	stEsmStatus.cJfFlag = 0;
//10.13载频,脉冲幅度
	stComStatus.dComZaiPin = 3.5;
	stComStatus.dPulseExtent = 3.0;
	strcpy(stComStatus.cPlatName,_T("导弹"));       //平台名称
	strcpy(stComStatus.cPlatNumber,_T("52"));   //平台编号
    strcpy(stComStatus.cEquipmentNumber,_T("003")); //设备编号
	strcpy(stComStatus.cEquipmentType,_T("COM")); //设备类型
	//10.13信号到达时间,信号类型,调制样式,敌我属性,国家/地区
	stComStatus.lSignalReachTime = 1500;
	strcpy(stComStatus.cSignalType,_T(" 脉冲信号"));
	strcpy(stComStatus.cModulationStyle ,_T("C样式")); 
	strcpy(stComStatus.cDWAttribute ,_T("我方")); 
	strcpy(stComStatus.cCountry  ,_T("中国")); 

	theApp.m_Comm_Dat.push_back(stComStatus);

//TRACK	
	stTrackStatus.lTargetNumber = 5001;
	stTrackStatus.dAzimuth =(float)35.0;
//	stTrackStatus.sPlatType = 117;          //平台类型
    strcpy(stTrackStatus.sPlatType ,_T("F117"));
	stTrackStatus.dConfidence = (float)0.3;
	stTrackStatus.cJfFlag = 0;
	stTrackStatus.dLonti = (float)118.20;   //目标经度 
	stTrackStatus.dLati = (float)24.10;     //目标纬度
	stTrackStatus.dObjHeight = (float)500.0;	//目标高度
	strcpy(stTrackStatus.cPlatName,_T("飞机1"));       //平台名称
	strcpy(stTrackStatus.cPlatNumber,_T("50"));   //平台编号
    strcpy(stTrackStatus.cEquipmentNumber,_T("001")); //设备编号
	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //设备类型

	theApp.m_Trace_Dat.push_back(stTrackStatus);

	stTrackStatus.lTargetNumber = 5002;
	stTrackStatus.dAzimuth =(float)40.0;
//	stTrackStatus.sPlatType = 118;
	strcpy(stTrackStatus.sPlatType,_T("F118")); 
	stTrackStatus.dConfidence = (float)0.2;
	stTrackStatus.cJfFlag = 0;
	stTrackStatus.dLonti = (float)117.30;   //目标经度
	stTrackStatus.dLati = (float)24.20;     //目标纬度
	stTrackStatus.dObjHeight = (float)800.0;	//目标高度
	strcpy(stTrackStatus.cPlatName,_T("飞机2"));       //平台名称
	strcpy(stTrackStatus.cPlatNumber,_T("51"));   //平台编号
    strcpy(stTrackStatus.cEquipmentNumber,_T("002")); //设备编号
	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //设备类型
	theApp.m_Trace_Dat.push_back(stTrackStatus);

// 	stTrackStatus.lTargetNumber = 5003;
// 	stTrackStatus.fAzimuth =(float)35.0;
// 	stTrackStatus.sPlatType = 119;
// 	stTrackStatus.dConfidence = (float)0.5;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)116.40;   //目标经度
// 	stTrackStatus.fLati = (float)24.30;     //目标纬度
// 	strcpy(stTrackStatus.cPlatName,_T("导弹"));     //平台名称
// 	strcpy(stTrackStatus.cPlatNumber,_T("52"));   //平台编号
//     strcpy(stTrackStatus.cEquipmentNumber,_T("003")); //设备编号
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //设备类型
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
// 
// 	stTrackStatus.lTargetNumber = 5004;
// 	stTrackStatus.fAzimuth =(float)35.0;
// 	stTrackStatus.sPlatType = 119;
// 	stTrackStatus.dConfidence = (float)0.4;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)119.40;  //目标经度
// 	stTrackStatus.fLati = (float)24.30;    //目标纬度
// 	strcpy(stTrackStatus.cPlatName,_T("舰艇"));     //平台名称
// 	strcpy(stTrackStatus.cPlatNumber,_T("53"));   //平台编号
//     strcpy(stTrackStatus.cEquipmentNumber,_T("004")); //设备编号
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //设备类型
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
// 
// 	stTrackStatus.lTargetNumber = 5005;
// 	stTrackStatus.fAzimuth =(float)55.0;
// 	stTrackStatus.sPlatType = 120;
// 	stTrackStatus.dConfidence = (float)0.6;
// 	stTrackStatus.cJfFlag = 0;
// 	stTrackStatus.fLonti = (float)118.50;  //目标经度
// 	stTrackStatus.fLati = (float)25.40;    //目标纬度
// 	strcpy(stTrackStatus.cPlatName,_T("飞机2"));     //平台名称
// 	strcpy(stTrackStatus.cPlatNumber,_T("54"));     //平台编号
//     strcpy(stTrackStatus.cEquipmentNumber,_T("005")); //设备编号
// 	strcpy(stTrackStatus.cEquipmentType,_T("Track")); //设备类型
// 	theApp.m_Trace_Dat.push_back(stTrackStatus);
    
	//后开启网络
	ServerCreate();

	//create thread 
	theApp.bThreadRun = TRUE;
	DWORD dwThreadID = 0;
	::CreateThread(NULL, 0, UdpDataThread, NULL, 0, &dwThreadID);

	CLanStatusView* pTp = (CLanStatusView*)theApp.pMsgFm;
	pTp->ClearMessages();

	CString str = _T("开启服务器\r\n");
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

	CString str = _T("关闭服务器\r\n");
	::EnterCriticalSection(&(theApp.g_cs));
	m_NewMessage.push_back(str);
	::LeaveCriticalSection(&(theApp.g_cs));
}

void CCommandPlatApp::OnRadarLib() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("弹出雷达库"));
}

void CCommandPlatApp::OnTargetLib() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("弹出目标库"));
}

void CCommandPlatApp::OnCreateSt() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("创建新的态势，未完善，待续"));
}

void CCommandPlatApp::OnChioseSt() 
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("选择已有的态势，未完善，待续"));
}
