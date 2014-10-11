// NodePlatDoc.cpp : implementation of the CNodePlatDoc class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "NodePlatDoc.h"
#include "NetworkSetting.h"
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
	ON_COMMAND(IDM_MATEALL, OnSendToMateall)
	ON_COMMAND(IDM_MATEA, OnSendToMateA)
	ON_COMMAND(IDM_MATEB, OnSendToMateB)
	ON_COMMAND(IDM_MATEC, OnSendToMateC)
	ON_COMMAND(IDM_MATED, OnSendToMateD)
	ON_COMMAND(IDM_MATEE, OnSendToMateE)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc construction/destruction

CNodePlatDoc::CNodePlatDoc()
{
	// TODO: add one-time construction code here
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
	m_ReceiveSocket->Create(CLIENTPORT);
	
	BOOL res;
	for (int i = 0; i < 5; ++i)
	{
		res = m_ReceiveSocket->Connect(strTmp, SERVERPORT);
		if (res)
		{
			break;
		}
	}
	
	if (i != 5)
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

#if 0
void CNodePlatDoc::OnSendmsg() 
{
	// TODO: Add your command handler code here
	//��ȡ��Ҫ����ʶ�����Ϣ����ת���ɷ��ͱ��ĵĽṹ
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;	
	VCT_Request_Cooperative_Msg::iterator iteReqCoopMsg;
	Request_Cooperative_Msg m_StRequest;      //��������ʶ��ǰ�����ŵı�����Ϣ
	int i = 0;

	long int lnum;//����ĺ�����
	lnum = theApp.m_ESM.at(theApp.m_iline).lAutonum;//��ȡ����Эͬ������
//����(����10��Ϊ����)	
//     StESM.lAutonum = 8008;
// 	m_StRequest.vctEsm.push_back(StESM);
// 	for ( iteEsm = m_StRequest.vctEsm.begin(); iteEsm != m_StRequest.vctEsm.end(); iteEsm++)
// 	{
// 		memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
// 	}
// 	for ( iteComm = m_StRequest.vctComm.begin(); iteComm != m_StRequest.vctComm.end();iteComm++)
// 	{
// 		memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
// 	}	

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
	int s,t, m, n;
	if (lnum >= 8000)
	{   
		for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /*theApp.m_ClusterUniMsg.end()*/; iteYes++ ,s++)
		{
			if (iteYes->lAutonum == lnum)
			{
				m_StRequest.lAutonum = lnum;//������
				m_StRequest.stTrace = iteYes->structTrace;//����ЭͬTRACE��Ϣ
				if (iteYes->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteYes->vctEsm.begin(),m =1 ; m <= iteYes->vctEsm.size() /*iteEsm = iteYes->vctEsm.end()*/; iteEsm++,m++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);

					}
				}
				if (iteYes->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteYes->vctComm.begin(), n = 1;  n <= iteYes->vctComm.size()  /*iteComm = iteYes->vctComm.end()*/; iteComm++ ,n++)
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
		for (iteNo = theApp.m_ClusterNoTraceMsg.begin() ,t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
		{
			if (iteNo->lAutonum == lnum)
			{
				m_StRequest.lAutonum = lnum;//������
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteNo->vctEsm.begin(),m=1; m<=iteNo->vctEsm.size()/* iteEsm = iteNo->vctEsm.end()*/; iteEsm++,m++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteNo->vctComm.begin(),n=1; n<=iteNo->vctComm.size()/* iteComm = iteNo->vctComm.end()*/; iteComm++,n++)
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

	//�������£�
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

	//�������map�ǽ��洫�����ģ�������ȫ�ֵ��Ǹ�map��ȫ�ֵ�map�Ǹ�������õġ�������ѡ��B���������vector����B����
	for (iteMap = theApp.IpMap.begin(); iteMap != theApp.IpMap.end(); ++iteMap)
	//iteMap = theApp.IpMap.begin();
	{	
		//���/*����ṹ��*/
		if (lnum >= 8000)           //????????????????�ǲ���ͬһʱ�̵�,��������ת��Ϊ����ṹ��
		{
			for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /* iteYes != theApp.m_ClusterUniMsg.end()*/; iteYes++,s++)
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
					for (i = 0; i < iteYes->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i < iteYes->vctComm.size();i++)//����ЭͬCOMM��Ϣ
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
			for (iteNo = theApp.m_ClusterNoTraceMsg.begin(),t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
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
					for (i = 0; i < iteNo->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i < iteNo->vctComm.size();i++)//����ЭͬCOMM��Ϣ
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
		int conreval;
		/*
		//��������ȫ�ֵİ������ҵ��Ǹ�IP��ַ
		iteMap = theApp.IpMap.find(i);
		CString cstest = iteMap->second;
		if (iteMap == theApp.IpMap.end())
		{
		}
		else
		{*/
			CString cstest = iteMap->second;
			conreval = theApp.m_P2PClient->Connect(iteMap->second, P2P_SERVER_PORT);
			
			if (conreval)
			{
				//��������
				SendCoopReq(theApp.m_P2PClient);
				//�ȴ����� 
				ReceiveData(theApp.m_P2PClient);
				//�ر�socket,�ȴ�����ʹ��!
				theApp.m_P2PClient->Close();

				//�жϽ��ջ�����vector�Ƿ�Ϊ��
				//if (sizeof(theApp.m_SendBackMsg))//�����Ϊ��,���յ����ݲ�������!�����Զ��Ϊtrue.
				if (theApp.m_RecvBackMsg_Dat.size() !=0 )
				{	
					//�Ƚ���ǰ�ṹ��������ת��������!!!!!!!!!��д
					for (iteBack = theApp.m_RecvBackMsg_Dat.begin(); iteBack != theApp.m_RecvBackMsg_Dat.end(); iteBack++)
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
						for (int j=0; j< iteBack->BackCOMN; j++)
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
		/*}	*/	
	}

	//�ж����ݷ���
	if ( theApp.m_BackMsg.size() != 0)
	{
		//�����㷨
		//GET_CooperateMsg_Modul(theApp.m_RequestMsg, theApp.m_BackMsg, theApp.m_CooperMsg);
    	//MultipleIdentify(theApp.m_CooperMsg, theApp.m_MulIdentifyMsg);

		//��ս�����Ϣ
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

		//�˴���Ӧ�������ںϵ����ݴ洢�����������������ɴ����ļ���


		AfxMessageBox("calucate ok!");
	}
	else
	{
		AfxMessageBox("δ�ҵ�������Ϣ");
	}
}
#endif

void CNodePlatDoc::OnSendToMateA() 
{
	// TODO: Add your command handler code here
	
}

void CNodePlatDoc::OnSendToMateB() 
{
	// TODO: Add your command handler code here
	
}

void CNodePlatDoc::OnSendToMateC() 
{
	// TODO: Add your command handler code here
	
}

void CNodePlatDoc::OnSendToMateD() 
{
	// TODO: Add your command handler code here
	
}

void CNodePlatDoc::OnSendToMateE() 
{
	// TODO: Add your command handler code here
	
}

void CNodePlatDoc::OnSendToMateall() 
{
	// TODO: Add your command handler code here
		//��ȡ��Ҫ����ʶ�����Ϣ����ת���ɷ��ͱ��ĵĽṹ
	VCT_UNINUM_MSG::iterator iteYes;
	VCT_UNINOTRACE_MSG::iterator iteNo;	
	VCT_ESM_MSG::iterator iteEsm;
	VCT_COMM_MSG::iterator iteComm;	
	map<int, CString>::iterator iteMap;	
	VCT_Request_Cooperative_Msg::iterator iteReqCoopMsg;
	Request_Cooperative_Msg m_StRequest;      //��������ʶ��ǰ�����ŵı�����Ϣ
	int i = 0;

	long int lnum;//����ĺ�����
	lnum = theApp.m_ESM.at(theApp.m_iline).lAutonum;//��ȡ����Эͬ������
//����(����10��Ϊ����)	
//     StESM.lAutonum = 8008;
// 	m_StRequest.vctEsm.push_back(StESM);
// 	for ( iteEsm = m_StRequest.vctEsm.begin(); iteEsm != m_StRequest.vctEsm.end(); iteEsm++)
// 	{
// 		memset(&(*iteEsm), 0, sizeof(ESMSTATUS_MARK));
// 	}
// 	for ( iteComm = m_StRequest.vctComm.begin(); iteComm != m_StRequest.vctComm.end();iteComm++)
// 	{
// 		memset(&(*iteComm), 0, sizeof(COMSTATUS_MARK));
// 	}	

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
	int s,t, m, n;
	if (lnum >= 8000)
	{   
		for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /*theApp.m_ClusterUniMsg.end()*/; iteYes++ ,s++)
		{
			if (iteYes->lAutonum == lnum)
			{
				m_StRequest.lAutonum = lnum;//������
				m_StRequest.stTrace = iteYes->structTrace;//����ЭͬTRACE��Ϣ
				if (iteYes->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteYes->vctEsm.begin(),m =1 ; m <= iteYes->vctEsm.size() /*iteEsm = iteYes->vctEsm.end()*/; iteEsm++,m++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);

					}
				}
				if (iteYes->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteYes->vctComm.begin(), n = 1;  n <= iteYes->vctComm.size()  /*iteComm = iteYes->vctComm.end()*/; iteComm++ ,n++)
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
		for (iteNo = theApp.m_ClusterNoTraceMsg.begin() ,t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
		{
			if (iteNo->lAutonum == lnum)
			{
				m_StRequest.lAutonum = lnum;//������
				//memset(&(StRequest.stTrace), 0, sizeof(TRACKSTATUS_MARK);
				if (iteNo->vctEsm.size())//����ЭͬESM��Ϣ
				{
					for (iteEsm = iteNo->vctEsm.begin(),m=1; m<=iteNo->vctEsm.size()/* iteEsm = iteNo->vctEsm.end()*/; iteEsm++,m++)
					{
						m_StRequest.vctEsm.push_back(*iteEsm);
					}
				}
				if (iteNo->vctComm.size())//����ЭͬCOMM��Ϣ
				{
					for (iteComm = iteNo->vctComm.begin(),n=1; n<=iteNo->vctComm.size()/* iteComm = iteNo->vctComm.end()*/; iteComm++,n++)
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

	//�������£�
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

	//�������map�ǽ��洫�����ģ�������ȫ�ֵ��Ǹ�map��ȫ�ֵ�map�Ǹ�������õġ�������ѡ��B���������vector����B����
	for (iteMap = theApp.IpMap.begin(); iteMap != theApp.IpMap.end(); ++iteMap)
	//iteMap = theApp.IpMap.begin();
	{	
		//���/*����ṹ��*/
		if (lnum >= 8000)           //????????????????�ǲ���ͬһʱ�̵�,��������ת��Ϊ����ṹ��
		{
			for (iteYes = theApp.m_ClusterUniMsg.begin(), s=1 ; s <= theApp.m_ClusterUniMsg.size() /* iteYes != theApp.m_ClusterUniMsg.end()*/; iteYes++,s++)
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
					for (i = 0; i < iteYes->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteYes->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteYes->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteYes->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteYes->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i < iteYes->vctComm.size();i++)//����ЭͬCOMM��Ϣ
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
			for (iteNo = theApp.m_ClusterNoTraceMsg.begin(),t=1; t<=theApp.m_ClusterNoTraceMsg.size()/* iteNo != theApp.m_ClusterNoTraceMsg.end()*/; iteNo++,t++)
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
					for (i = 0; i < iteNo->vctEsm.size();i++)//����ЭͬESM��Ϣ
					{
						theApp.m_StSendRequest.lEsmTargetNumber[i] = iteNo->vctEsm.at(i).lTargetNumber;//Ŀ��esm����
						theApp.m_StSendRequest.dEsmZaiPin[i] = iteNo->vctEsm.at(i).dZaiPin;//��Ƶ
						theApp.m_StSendRequest.dEsmMaiKuan[i] = iteNo->vctEsm.at(i).dMaiKuan;////����
						theApp.m_StSendRequest.dEsmTianXianScan[i] = iteNo->vctEsm.at(i).dTianXianScan;//����ɨ����Ϣ
					}
					for (i = 0; i < iteNo->vctComm.size();i++)//����ЭͬCOMM��Ϣ
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
		int conreval;
		/*
		//��������ȫ�ֵİ������ҵ��Ǹ�IP��ַ
		iteMap = theApp.IpMap.find(i);
		CString cstest = iteMap->second;
		if (iteMap == theApp.IpMap.end())
		{
		}
		else
		{*/
			CString cstest = iteMap->second;
			conreval = theApp.m_P2PClient->Connect(iteMap->second, P2P_SERVER_PORT);
			
			if (conreval)
			{
				//��������
				SendCoopReq(theApp.m_P2PClient);
				//�ȴ����� 
				ReceiveData(theApp.m_P2PClient);
				//�ر�socket,�ȴ�����ʹ��!
				theApp.m_P2PClient->Close();

				//�жϽ��ջ�����vector�Ƿ�Ϊ��
				//if (sizeof(theApp.m_SendBackMsg))//�����Ϊ��,���յ����ݲ�������!�����Զ��Ϊtrue.
				if (theApp.m_RecvBackMsg_Dat.size() !=0 )
				{	
					//�Ƚ���ǰ�ṹ��������ת��������!!!!!!!!!��д
					for (iteBack = theApp.m_RecvBackMsg_Dat.begin(); iteBack != theApp.m_RecvBackMsg_Dat.end(); iteBack++)
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
						for (int j=0; j< iteBack->BackCOMN; j++)
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
		/*}	*/	
	}

	//�ж����ݷ���
	if ( theApp.m_BackMsg.size() != 0)
	{
		//�����㷨
		GET_CooperateMsg_Modul(theApp.m_RequestMsg, theApp.m_BackMsg, theApp.m_CooperMsg);
    	MultipleIdentify(theApp.m_CooperMsg, theApp.m_MulIdentifyMsg);

		//��ս�����Ϣ
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

		//�˴���Ӧ�������ںϵ����ݴ洢�����������������ɴ����ļ���


		AfxMessageBox("calucate ok!");
	}
	else
	{
		AfxMessageBox("δ�ҵ�������Ϣ");
	}
	
}

//��������
void CNodePlatDoc::OnEvaSin() 
{
	// TODO: Add your command handler code here
	
}


//�ར����
void CNodePlatDoc::OnEvaMul() 
{
	// TODO: Add your command handler code here
	
}




