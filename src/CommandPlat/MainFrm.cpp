// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CommandPlat.h"

#include "MainFrm.h"

#include "LanStatusView.h"
#include "MessageView.h"
#include "ParamSetView.h"

#include "CommandPlatDoc.h"
#include "CommandPlatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
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
	bRetVal = m_HSplitter.CreateView(1, 0, RUNTIME_CLASS(CMessageView), CSize(0, 100), pContext);
	if (!bRetVal)
		return(FALSE);
	
	bRetVal = m_VSplitter.CreateStatic(&m_HSplitter, 1, 3, WS_CHILD | WS_VISIBLE, m_HSplitter.IdFromRowCol(0, 0));
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_VSplitter.CreateView(0, 0, RUNTIME_CLASS(CParamSetView), CSize(300, 0), pContext);
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_VSplitter.CreateView(0, 1, RUNTIME_CLASS(CCommandPlatView), CSize(500, 0), pContext);
	if (!bRetVal)
		return(FALSE);
	bRetVal = m_VSplitter.CreateView(0, 2, RUNTIME_CLASS(CLanStatusView), CSize(300, 0), pContext);
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

	int cxmin = 0;
	int cx0 = 0;
	int cx1 = 0;
	int cx2 = 0;
	int Allcx = 0;
	
	int minCy0 = 0;
	int minCx0 = 0;
	int minCx2 = 0;

	if (m_bCreate)
	{
		if (m_HSplitter.m_hWnd)
		{
			//获得当前高度
			m_HSplitter.GetRowInfo(0, cy0, cymin);
			m_HSplitter.GetRowInfo(1, cy1, cymin);
			Allcy = cy0 + cy1;
			//下面框架为总框架的0.75
			minCy0 = (short)(0.75*Allcy);
			if (cy0 != minCy0)
			{
				cy0 = minCy0;
				m_HSplitter.SetRowInfo(0, cy0 , cymin);
				m_HSplitter.SetRowInfo(1, Allcy-cy0 , cymin);
			}
			m_HSplitter.RecalcLayout();
		}
		if (m_VSplitter.m_hWnd)
		{
			m_VSplitter.GetColumnInfo(0, cx0, cxmin);
			m_VSplitter.GetColumnInfo(1, cx1, cxmin);
			m_VSplitter.GetColumnInfo(2, cx2, cxmin);
			Allcx = cx0 + cx1 + cx2;

			minCx0 = (short)(0.25*Allcx);
			minCx2 = (short)(0.2*Allcx);//比例是3、5、2
			if (cx2 != minCx2 || cx0 != minCx0)
			{
				m_VSplitter.SetColumnInfo(0, minCx0 , cxmin);
				m_VSplitter.SetColumnInfo(1, Allcx-minCx0-minCx2 , cxmin);
				m_VSplitter.SetColumnInfo(2, minCx2 , cxmin);
			}
			m_VSplitter.RecalcLayout();
		}
	}		
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetFrmLayout();
}
