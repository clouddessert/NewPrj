// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "MainFrm.h"
#include "DrawView.h"
#include "MsgCtlView.h"
#include "MsgListView.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
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

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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
	//设置高度
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
			//获得当前高度
			m_HSplitter.GetRowInfo(0, cy0, cymin);
			m_HSplitter.GetRowInfo(1, cy1, cymin);
			Allcy = cy0 + cy1;
			//下面框架为总框架的0.80
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
		//调用算法模块
		::EnterCriticalSection(&(theApp.g_cs));
		if (!theApp.m_RecvMsg.stEsm.empty() || !theApp.m_RecvMsg.stComm.empty() || !theApp.m_RecvMsg.stTrace.empty())
		{
			SingleIdentify(theApp.m_RecvMsg, theApp.m_ClusterUniMsg, theApp.m_ClusterNoTraceMsg, theApp.m_IdentifyMsg, theApp.m_SingleTrace, theApp.m_SingleEsm, theApp.m_SingleComm);
			//将编批后的信息存入
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
		
		//显示数据
		::PostMessage(theApp.hESM_wmd, WM_ESM_MSG, 0, 0);
		::PostMessage(theApp.hCOMM_wmd, WM_COMM_MSG, 0, 0);
		::PostMessage(theApp.hTRACE_wmd, WM_TRACE_MSG, 0, 0);
		::PostMessage(theApp.hSigOut_wnd, WM_SIG_OUT_MSG, 0, 0);
		::PostMessage(theApp.hMulOut_wnd, WM_MUL_OUT_MSG, 0, 0);
                ::PostMessage(theApp.hMulESM_wmd, WM_MULESM_MSG, 0, 0);
		::PostMessage(theApp.hMulCOMM_wnd, WM_MULCOMM_MSG, 0, 0);
		::PostMessage(theApp.hMulTRACE_wnd, WM_MULTRACE_MSG, 0, 0);
                
	}

	CFrameWnd::OnTimer(nIDEvent);
}
