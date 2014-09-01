// NodePlatDoc.cpp : implementation of the CNodePlatDoc class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "NodePlatDoc.h"

//////////////////////////////////////////////////////////////////////////
#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//����socket
CMySocket* m_ReceiveSocket = NULL;

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc

IMPLEMENT_DYNCREATE(CNodePlatDoc, CDocument)

BEGIN_MESSAGE_MAP(CNodePlatDoc, CDocument)
	//{{AFX_MSG_MAP(CNodePlatDoc)
	ON_COMMAND(IDM_CONNECTSVR, OnConnectsvr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodePlatDoc construction/destruction

CNodePlatDoc::CNodePlatDoc()
{
	// TODO: add one-time construction code here
	m_ReceiveSocket = new CMySocket();
	m_ReceiveSocket->Create(CLIENTPORT);

	//��ʼ
	theApp.m_RecvMsg.stComm.clear();
	theApp.m_RecvMsg.stEsm.clear();
	theApp.m_RecvMsg.stTrace.clear();
}

CNodePlatDoc::~CNodePlatDoc()
{
	m_ReceiveSocket->Close();
	delete m_ReceiveSocket;

	//����
	theApp.m_RecvMsg.stComm.clear();
	theApp.m_RecvMsg.stEsm.clear();
	theApp.m_RecvMsg.stTrace.clear();
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

void CNodePlatDoc::OnConnectsvr() 
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
	
	if (m_ReceiveSocket->Connect(strTmp, SERVERPORT))
	{
		//��ʼ
		theApp.m_RecvMsg.stComm.clear();
		theApp.m_RecvMsg.stEsm.clear();
		theApp.m_RecvMsg.stTrace.clear();

		//��ʼ��¼����
		CMainFrame* pTmp = (CMainFrame*)AfxGetMainWnd();
		pTmp->StartTimer_X();

	} 
	else
	{
		AfxMessageBox(_T("���Ӿ��������ʧ�ܣ���������������"));
	}

	//��ʼ��¼����
	CMainFrame* pTmp = (CMainFrame*)AfxGetMainWnd();
	pTmp->StartTimer_X();
}

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
			
			::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 0, 0);

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

			::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 0, 0);
			
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

			::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);

			break;
		}
	default:
		break;
	}	
}
