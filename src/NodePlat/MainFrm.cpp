// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "DrawView.h"
#include "MsgCtlView.h"
#include "MsgListView.h"
#include "DrawView.h"
  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////

//////////////////////////////
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator ��ʾ�о�����Ϣ
    ID_SEPARATOR,           //��ʾ�����ĵ���λ��(��γ�ȱ仯)
	ID_SEPARATOR,           //��껬����λ��   
	ID_SEPARATOR,           //��껬����λ�� 
	ID_SEPARATOR,           //��ʾϵͳʱ��  
	ID_SEPARATOR,           // status line indicator ��ʾ�о�����Ϣ
// 	ID_INDICATOR_CAPS,
// 	ID_INDICATOR_NUM,
// 
// 	ID_INDICATOR_SCRL,
/*	IDS_TIME,*/
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bCreate = FALSE;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	SetTimer(1,1000,NULL);		// ��ʾϵͳʱ��
		showParaX=0;
    m_wndStatusBar.SetPaneInfo(0,0,0,200*showParaX);
	//CString strTemp1=" ����ΪA�� ����Ϊ      γ��Ϊ    ";
	//m_wndStatusBar.SetPaneText(1,strTemp1);
	m_wndStatusBar.SetPaneInfo(1,0,0,180);
	m_wndStatusBar.SetPaneInfo(2,0,0,260);
	m_wndStatusBar.SetPaneInfo(3,0,0,290);
	m_wndStatusBar.SetPaneInfo(4,0,0,250);  

	CString strTemp2="     XXX�о���";
	m_wndStatusBar.SetPaneText(5,strTemp2);
	m_wndStatusBar.SetPaneInfo(5,0,0,250);

	double x00=(LEFT_LONGIT + RIGHT_LONGIT)/2;
	double y00=(UP_LATI + DOWN_LATI)/2;
	theApp.m_GpsDisplay.Format("��ͼ���ľ���Ϊ%.4f,����γ��Ϊ%.4f", x00,y00);
	OnShowGps();
	
	theApp.m_GpsZBDisplay.Format("");
	OnShowGps();
    OnSelfShipGps();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	// the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRetVal = TRUE;
	bRetVal = m_HSplitter.CreateStatic(this, 2, 1);
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_HSplitter.CreateView(1, 0, RUNTIME_CLASS(CMsgListView), CSize(0, 0), pContext);
	if (!bRetVal)
		return(FALSE);
	
	bRetVal = m_VSplitter.CreateStatic(&m_HSplitter, 1, 2, WS_CHILD | WS_VISIBLE, m_HSplitter.IdFromRowCol(0, 0));
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_VSplitter.CreateView(0, 0, RUNTIME_CLASS(CMsgCtlView), CSize(300, 0), pContext);
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_VSplitter.CreateView(0, 1, RUNTIME_CLASS(CDrawView), CSize(0, 0), pContext);
	if (!bRetVal)
		return(FALSE);
	
	m_bCreate = TRUE;
	//���ø߶�
	SetFrmLayout();

	return(TRUE);
}

void CMainFrame::SetFrmLayout()
{
	int cymin = 0;
	int cy0 = 0;
	int cy1 = 0;
	int Allcy = 0;

	int minCy0 = 0;
	if (m_bCreate)
	{
		if (m_HSplitter.m_hWnd)
		{
			//m_HSplitter.GetRowInfo(1, cy0, cymin);
			//��õ�ǰ�߶�
			m_HSplitter.GetRowInfo(0, cy0, cymin);
			m_HSplitter.GetRowInfo(1, cy1, cymin);
			Allcy = cy0 + cy1;
			//������Ϊ�ܿ�ܵ�0.80
			minCy0 = (int)(0.80*Allcy);
			if (cy0 != minCy0)
			{
				cy0 = minCy0;
				m_HSplitter.SetRowInfo(0, cy0 , cymin);
				m_HSplitter.SetRowInfo(1, Allcy-cy0 , cymin);
			}
			m_HSplitter.RecalcLayout();
		}
	}		
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetFrmLayout();
}

/////////////////////////////////////////////////////////////////

void CMainFrame::StartTimer_X(void)
{
	SetTimer(8, 800, 0);
}

void CMainFrame::CloseTimer_X(void)
{
	KillTimer(8);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
//	theApp.pOutPt = NULL;
	VCT_ESM_MSG::iterator ite_Esm;
	VCT_COMM_MSG::iterator ite_Comm;
	VCT_TRACE_MSG::iterator ite_Trace;
	if (8 == nIDEvent)
	{
		//�����㷨ģ��
		::EnterCriticalSection(&(theApp.g_cs));
		if (!theApp.m_RecvMsg.stEsm.empty() || !theApp.m_RecvMsg.stComm.empty() || !theApp.m_RecvMsg.stTrace.empty())
		{
			SingleIdentify(theApp.m_RecvMsg, theApp.m_ClusterUniMsg, theApp.m_ClusterNoTraceMsg, theApp.m_IdentifyMsg, theApp.m_SingleTrace, theApp.m_SingleEsm, theApp.m_SingleComm);
			//�����������Ϣ����
			theApp.m_ESM.clear();
			theApp.m_Comm.clear();
			theApp.m_Trace.clear();
			for (ite_Esm = theApp.m_RecvMsg.stEsm.begin(); ite_Esm != theApp.m_RecvMsg.stEsm.end(); ite_Esm++)
			{
				theApp.m_ESM.push_back(*ite_Esm);
			}
			for (ite_Comm = theApp.m_RecvMsg.stComm.begin(); ite_Comm != theApp.m_RecvMsg.stComm.end(); ite_Comm++)
			{
				theApp.m_Comm.push_back(*ite_Comm);
			}
			for (ite_Trace = theApp.m_RecvMsg.stTrace.begin(); ite_Trace != theApp.m_RecvMsg.stTrace.end(); ite_Trace++)
			{
				theApp.m_Trace.push_back(*ite_Trace);
			}
		}
		::LeaveCriticalSection(&(theApp.g_cs));
		
		//��ʾ����
		::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 0, 0);
		::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 0, 0);
		::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);
		::PostMessage(theApp.hSigOut_wnd, WM_SIG_OUT_MSG, 0, 0);
		::PostMessage(theApp.hMulOut_wnd, WM_MUL_OUT_MSG, 0, 0);
        ::PostMessage(theApp.hMulESM_wmd, WM_MULESM_MSG, 0, 0);
		::PostMessage(theApp.hMulCOMM_wnd, WM_MULCOMM_MSG, 0, 0);
		::PostMessage(theApp.hMulTRACE_wnd, WM_MULTRACE_MSG, 0, 0);          
	}
	if (1 == nIDEvent)
	{
		GetSysTime();
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::GetSysTime()
{
	CTime tm;
	int a;                      //����Сʱ
	int b;                      //�������
	int c;                      //������
	CString strW;
	tm=CTime::GetCurrentTime(); //��ȡϵͳ��ǰʱ��
	a=tm.GetHour();             //��ȡʱ
	b=tm.GetMinute();           //��ȡ��
	c=tm.GetSecond();           //��ȡ��
	strW.Format("     ϵͳʱ�䣺%d:%02d:%02d",a,b,c);
	m_wndStatusBar.SetPaneText(4,strW);
}

void CMainFrame::OnShowGps(void)
{
	m_wndStatusBar.SetPaneText(2,theApp.m_GpsDisplay);
	m_wndStatusBar.SetPaneText(3,theApp.m_GpsZBDisplay);
}

void CMainFrame::OnSelfShipGps(void)
{
	if (theApp.m_ThisNumber == 0)
	{
		strcpy(theApp.m_SelfName, _T("A"));
        theApp.m_SelfShipGps.Format("  ����Ϊ%s��", theApp.m_SelfName);
    	m_wndStatusBar.SetPaneText(1,theApp.m_SelfShipGps);
	}
	if (theApp.m_ThisNumber == 1)
	{
		strcpy(theApp.m_SelfName,  _T("B"));
        theApp.m_SelfShipGps.Format("  ����Ϊ%s��", theApp.m_SelfName);
		m_wndStatusBar.SetPaneText(1,theApp.m_SelfShipGps);
	}
	if (theApp.m_ThisNumber == 2)
	{
		strcpy(theApp.m_SelfName,  _T("C"));
        theApp.m_SelfShipGps.Format("  ����Ϊ%s��", theApp.m_SelfName);
		m_wndStatusBar.SetPaneText(1,theApp.m_SelfShipGps);
	}
	if (theApp.m_ThisNumber == 3)
	{
		strcpy(theApp.m_SelfName,  _T("D"));
        theApp.m_SelfShipGps.Format("  ����Ϊ%s��", theApp.m_SelfName);
		m_wndStatusBar.SetPaneText(1,theApp.m_SelfShipGps);
	}
	if (theApp.m_ThisNumber == 4)
	{
		strcpy(theApp.m_SelfName,  _T("E"));
        theApp.m_SelfShipGps.Format("  ����Ϊ%s��", theApp.m_SelfName);
		m_wndStatusBar.SetPaneText(1,theApp.m_SelfShipGps);
	}
}