// NodePlatDoc.cpp : implementation of the CNodePlatDoc class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "NodePlatDoc.h"
#include "NetworkSetting.h"
#include "EvaluDlg.h"  //�ο���������
#include "EIdenFusVALU.h"
//////////////////////////////////////////////////////////////////////////
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//���ܾ���socket
static CMySocket* m_ReceiveSocket = NULL;

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc

IMPLEMENT_DYNCREATE(CNodePlatDoc, CDocument)

BEGIN_MESSAGE_MAP(CNodePlatDoc, CDocument)
	//{{AFX_MSG_MAP(CNodePlatDoc)
	ON_COMMAND(IDM_NETWORK_SETTING, OnNetworkSetting)
	ON_COMMAND(IDM_SYSTEM, OnSystemSetting)
	ON_COMMAND(IDM_CONNECT_SERVICE, OnConnectService)
	ON_COMMAND(IDM_TEAM_SERVICE_START, OnTeamServiceStart)
	ON_COMMAND(IDM_TEAM_SERVICE_STOP, OnTeamServiceStop)
	ON_COMMAND(IDM_DISCONNECT_SERVICE, OnDisconnectService)
	ON_COMMAND(IDM_EVA_SIN, OnEvaSin)
	ON_COMMAND(IDM_EVA_MUL, OnEvaMul)
	ON_COMMAND(IDM_EVALUATE, OnEvatuate)
	ON_COMMAND(IDC_MENUITEMA, OnMenuitemA)
	ON_COMMAND(IDC_MENUITEMALL, OnMenuitemAll)
	ON_COMMAND(IDC_MENUITEMB, OnMenuitemB)
	ON_COMMAND(IDC_MENUITEMC, OnMenuitemC)
	ON_COMMAND(IDC_MENUITEMD, OnMenuitemD)
	ON_COMMAND(IDC_MENUITEME, OnMenuitemE)
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_UPDATE_COMMAND_UI(IDC_MENUITEMB, OnUpdateMenuitemb)
	ON_UPDATE_COMMAND_UI(IDC_MENUITEMA, OnUpdateMenuitema)
	ON_UPDATE_COMMAND_UI(IDC_MENUITEMC, OnUpdateMenuitemc)
	ON_UPDATE_COMMAND_UI(IDC_MENUITEMD, OnUpdateMenuitemd)
	ON_UPDATE_COMMAND_UI(IDC_MENUITEME, OnUpdateMenuiteme)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc construction/destruction

CNodePlatDoc::CNodePlatDoc()
{
	// TODO: add one-time construction code here
	theApp.pTmpDocPt = (void*)this;
}

CNodePlatDoc::~CNodePlatDoc()
{

}

BOOL CNodePlatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc serialization

void CNodePlatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc diagnostics

#ifdef _DEBUG
void CNodePlatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNodePlatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc commands

void CNodePlatDoc::OnReceiveMsg()
{
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	
	//������ͷ
	m_ReceiveSocket->Receive(&stHeader, sizeof(ProtcolHeader));
	
	switch (stHeader.nMsgType)
	{

		//ESM��Ϣ
	case 1:
		{
			ESMSTATUS_MARK tmp;
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_ESM_Dat.clear();
			for (int nNum = 1; nNum<=stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmp, sizeof(ESMSTATUS_MARK));
				m_ReceiveSocket->Receive(&tmp, sizeof(ESMSTATUS_MARK));	
				theApp.m_ESM_Dat.push_back(tmp);
			}
			//copy
			theApp.m_RecvMsg.stEsm.clear();
			theApp.m_RecvMsg.stEsm = theApp.m_ESM_Dat;
			::LeaveCriticalSection(&(theApp.g_cs));
			
//			::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 0, 0);

			break;
		}		
		//Comm��Ϣ
	case 2:
		{
			COMSTATUS_MARK tmp;
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_Comm_Dat.clear();
			for (int nNum = 1; nNum<=stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmp, sizeof(COMSTATUS_MARK));
				m_ReceiveSocket->Receive(&tmp, sizeof(COMSTATUS_MARK));	
				theApp.m_Comm_Dat.push_back(tmp);
			}
			//copy
			theApp.m_RecvMsg.stComm.clear();
			theApp.m_RecvMsg.stComm = theApp.m_Comm_Dat;
			::LeaveCriticalSection(&(theApp.g_cs));

//			::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 0, 0);
			
			break;
		}
	case 3:
		{
			TRACKSTATUS_MARK tmp;
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_Trace_Dat.clear();
			for (int nNum = 1; nNum<=stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmp, sizeof(TRACKSTATUS_MARK));
				m_ReceiveSocket->Receive(&tmp, sizeof(TRACKSTATUS_MARK));	
				theApp.m_Trace_Dat.push_back(tmp);
			}
			//copy
			theApp.m_RecvMsg.stTrace.clear();
			theApp.m_RecvMsg.stTrace = theApp.m_Trace_Dat;
			::LeaveCriticalSection(&(theApp.g_cs));

//			::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);

			break;
		}
	case 4:
		{
			SHIP_POSITION tmp;
			//�����ݾܾ��޸�
			::EnterCriticalSection(&(theApp.g_cs));
			theApp.m_Ship_Position.clear();
			for (int nNum = 1; nNum<=stHeader.nMsgLength; ++nNum)
			{
				ZeroMemory(&tmp, sizeof(SHIP_POSITION));
				m_ReceiveSocket->Receive(&tmp, sizeof(SHIP_POSITION));	
				theApp.m_Ship_Position.push_back(tmp);
			}
			//copy
			theApp.m_SPosition.clear();
			theApp.m_SPosition= theApp.m_Ship_Position;
			::LeaveCriticalSection(&(theApp.g_cs));
			
			//			::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);
			
			break;
		}


	default:
		break;
	}	
}

void CNodePlatDoc::OnNetworkSetting() 
{
	// TODO: Add your command handler code here
	CNetworkSetting dlg;
	dlg.DoModal();
}

void CNodePlatDoc::OnSystemSetting() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("ϵͳ�趨");
}

void CNodePlatDoc::OnConnectService() 
{
	// TODO: Add your command handler code here
	//��ȡ��ʱ·��
	CString strTmp;
	CString	sPath;
	
	//��ù����ļ���·��
	::GetCurrentDirectory(_MAX_PATH,sPath.GetBuffer(_MAX_PATH));
	sPath.ReleaseBuffer();
	sPath = sPath+_T("\\NetConfig.ini");
	
	::GetPrivateProfileString(_T("IP��ַ"), _T("������IP��ַ"), _T("127.0.0.1"), strTmp.GetBuffer(MAX_PATH), MAX_PATH, sPath);
	strTmp.ReleaseBuffer();

	//���浱ǰIP
	::WritePrivateProfileString(_T("IP��ַ"), _T("������IP��ַ"), strTmp, sPath);

	//��������
	m_ReceiveSocket = new CMySocket();
	m_ReceiveSocket->Socket();

	BOOL res = m_ReceiveSocket->Connect(strTmp, SERVERPORT);
	
	if (res)
	{
		//��ʼ
		theApp.m_RecvMsg.stComm.clear();
		theApp.m_RecvMsg.stEsm.clear();
		theApp.m_RecvMsg.stTrace.clear();
		theApp.m_SPosition.clear();
		
		//��ʼ��¼����
		CMainFrame* pTmp = (CMainFrame*)AfxGetMainWnd();
		pTmp->StartTimer_X();
	} 
	else
	{
		//ʧ��
		AfxMessageBox(_T("���Ӿ��������ʧ�ܣ���������������"));
	}
}

void CNodePlatDoc::OnDisconnectService() 
{
	// TODO: Add your command handler code here
	//����
	CMainFrame* pTmp = (CMainFrame*)AfxGetMainWnd();
	pTmp->CloseTimer_X();

	theApp.m_RecvMsg.stComm.clear();
	theApp.m_RecvMsg.stEsm.clear();
	theApp.m_RecvMsg.stTrace.clear();
	theApp.m_SPosition.clear();

	m_ReceiveSocket->ShutDown(2);
	m_ReceiveSocket->Close();
	delete m_ReceiveSocket;
}

void CNodePlatDoc::OnTeamServiceStart() 
{
	// TODO: Add your command handler code here
	theApp.ServerCreate();
}

void CNodePlatDoc::OnTeamServiceStop() 
{
	// TODO: Add your command handler code here
	theApp.ServerShutDown();
}

void CNodePlatDoc::SendCoopReq(CSocket* pThis)
{
	ProtcolHeader stHeader;                  //��ͷ��Ϣ

	stHeader.nMsgType = 11;
	stHeader.nMsgLength = sizeof(ProtcolHeader);
	pThis->Send(&stHeader, sizeof(stHeader));
	pThis->Send(&theApp.m_StSendRequest, sizeof(theApp.m_StSendRequest));
}

void CNodePlatDoc::ReceiveData(CSocket* pThis)
{
	//���հ�ͷ
	//���ݰ�ͷ��������״̬��
	ProtcolHeader stHeader;
	ZeroMemory(&stHeader, sizeof(ProtcolHeader));
	pThis->Receive(&stHeader, sizeof(ProtcolHeader));		//�����ָ�붼��pThis
	switch (stHeader.nMsgType)
	{
		//������յ�������
	case 12:
		//���浽���յ�buffer,over
		{
			SendBack_Msg tmpRecBack_Msg;
			//theApp.m_RecvBackMsg_Dat.clear();
			::EnterCriticalSection(&(theApp.g_cs));
			ZeroMemory(&tmpRecBack_Msg, sizeof(SendBack_Msg));
			pThis->Receive(&tmpRecBack_Msg, sizeof(SendBack_Msg));	//����vector��������!!!!!!!
			theApp.m_RecvBackMsg_Dat.push_back(tmpRecBack_Msg);
			::LeaveCriticalSection(&(theApp.g_cs));

// 			//������Ϣ����
// 			SYSTEMTIME tm;
// 			GetLocalTime(&tm);
// 			CString time;
// 			time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 			CString str1,str2,str3;
// 			str1.Format("�ҽ�");
// 			str2.Format("�յ�IPΪ ");
// 			str3.Format("�Ľ���Эͬ����");
// 			theApp.m_MsgDisplay = str1+"��"+time+str2+tmpRecBack_Msg.sSendIp+str3;
// 			
// 			::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);//����ʾ���ڷ�����Ϣ

			break;
		}
	default:
		break;
	}		
}


void CNodePlatDoc::OnMenuitemA() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(0);
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("��A������Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 
	// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
	
	
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	
	
}

void CNodePlatDoc::OnMenuitemAll() 
{
	// TODO: Add your command handler code here
	//��������Эͬ�ĺ���,����Эͬ�Ľ���Ϊ����theApp.IpMap�е�
	map<int, CString>::iterator iter;
	::EnterCriticalSection(&(theApp.g_cs));
	//theApp.SendToIpMap.clear();
	for (iter = theApp.IpMap.begin(); iter != theApp.IpMap.end(); ++iter)
	{
		theApp.SendToIpMap.insert(*iter);
	}
	::LeaveCriticalSection(&(theApp.g_cs));	
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("�����н�����Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
	
}

void CNodePlatDoc::OnMenuitemB() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(1);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("��B������Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 	
	// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnMenuitemC() 
{
	// TODO: Add your command handler code here

	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(2);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("��C������Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnMenuitemD() 
{
	// TODO: Add your command handler code here

	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(3);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("��D������Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnMenuitemE() 
{
	// TODO: Add your command handler code here

	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(4);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}	
	
	// 	SYSTEMTIME tm;
	// 	GetLocalTime(&tm);
	// 	CString time;
	// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	// 	CString str1,str2;
	// 	str1.Format("�ҽ�");
	// 	str2.Format("��E������Эͬ����");
	// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
	// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnUpdateMenuitema(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theApp.m_ThisNumber == 0)
	{
		pCmdUI->Enable(false);
	}
}

void CNodePlatDoc::OnUpdateMenuitemb(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theApp.m_ThisNumber == 1)
	{
		pCmdUI->Enable(false);
	}
	
}

void CNodePlatDoc::OnUpdateMenuitemc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theApp.m_ThisNumber == 2)
	{
		pCmdUI->Enable(false);
	}
}

void CNodePlatDoc::OnUpdateMenuitemd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theApp.m_ThisNumber == 3)
	{
		pCmdUI->Enable(false);
	}
}

void CNodePlatDoc::OnUpdateMenuiteme(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (theApp.m_ThisNumber == 4)
	{
		pCmdUI->Enable(false);
	}
}

/*
void CNodePlatDoc::OnSendA() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(0);

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("��A������Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);


	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP

		::LeaveCriticalSection(&(theApp.g_cs));
	}


}

void CNodePlatDoc::OnSendB() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(1);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("��B������Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
	
}

void CNodePlatDoc::OnSendC() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(2);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("��C������Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnSendD() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(3);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("��D������Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnSendE() 
{
	// TODO: Add your command handler code here
	//theApp.SendToIpMap.clear();                            //���Эͬip
	map<int, CString>::iterator iter;
	iter = theApp.IpMap.find(4);
	if(iter != theApp.IpMap.end())
	{
		::EnterCriticalSection(&(theApp.g_cs));
		theApp.SendToIpMap.insert(make_pair(0,iter->second));//����ЭͬIP
		::LeaveCriticalSection(&(theApp.g_cs));
	}	

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("��E������Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnSendAll() 
{
	// TODO: Add your command handler code here
	//��������Эͬ�ĺ���,����Эͬ�Ľ���Ϊ����theApp.IpMap�е�
	map<int, CString>::iterator iter;
	::EnterCriticalSection(&(theApp.g_cs));
	//theApp.SendToIpMap.clear();
	for (iter = theApp.IpMap.begin(); iter != theApp.IpMap.end(); ++iter)
	{
		theApp.SendToIpMap.insert(*iter);
	}
	::LeaveCriticalSection(&(theApp.g_cs));	

// 	SYSTEMTIME tm;
// 	GetLocalTime(&tm);
// 	CString time;
// 	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
// 	CString str1,str2;
// 	str1.Format("�ҽ�");
// 	str2.Format("�����н�����Эͬ����");
// 	theApp.m_MsgDisplay = str1+"��"+time+str2;
// 	
// 	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnSendMsg() 
{
	// TODO: Add your command handler code here
	CEvaluDlg dlg;
	dlg.DoModal();
	
}

void CNodePlatDoc::OnCloseA() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն�A����Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
	
}

void CNodePlatDoc::OnCloseB() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն�B����Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnCloseC() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն�C����Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnCloseD() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն�D����Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnCloseE() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն�E����Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

void CNodePlatDoc::OnCloseAll() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	

	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն����н���Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}
*/

void CNodePlatDoc::OnClose() 
{
	// TODO: Add your command handler code here
	::EnterCriticalSection(&(theApp.g_cs));
	theApp.SendToIpMap.clear();
	::LeaveCriticalSection(&(theApp.g_cs));	
	
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d:%02d:%02d"), tm.wHour, tm.wMinute, tm.wSecond);
	CString str1,str2;
	str1.Format("�ҽ�");
	str2.Format("�رն����н���Эͬ����");
	theApp.m_MsgDisplay = str1+"��"+time+str2;
	
	::PostMessage(theApp.hDISPLAY_wnd, WM_DISPLAY_MSG, 0, 0);
}

//��������
void CNodePlatDoc::OnEvaSin() 
{
	// TODO: Add your command handler code here
	CEvaluDlg dlg;
	dlg.nmulFlag = 0;  //����
	dlg.DoModal(); //��������1

// 	CEIdenFusVALU dlg;
// 	dlg.DoModal(); //��������2 ���ָ����������
	 
}

//�ར����
void CNodePlatDoc::OnEvaMul() 
{
	// TODO: Add your command handler code here
	CEvaluDlg dlg;
	dlg.nmulFlag = 1; //�ར
	dlg.DoModal();//��������1

// 	CEIdenFusVALU dlg;
// 	dlg.DoModal(); //��������2 ���ָ����������
}

void CNodePlatDoc::OnEvatuate()
{
	CEvaluDlg dlg;
	dlg.nmulFlag = 1; //�ར
	dlg.DoModal();	//��������1

// 	CEIdenFusVALU dlg;
// 	dlg.DoModal();//��������2 ���ָ����������
}



