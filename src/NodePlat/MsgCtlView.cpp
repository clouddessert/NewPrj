// MsgCtlView.cpp : implementation file
//

#include "stdafx.h"
#include "nodeplat.h"
#include "MsgCtlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgCtlView

IMPLEMENT_DYNCREATE(CMsgCtlView, CView)

CMsgCtlView::CMsgCtlView():m_ParamSheet("")
{
}

CMsgCtlView::~CMsgCtlView()
{
}


BEGIN_MESSAGE_MAP(CMsgCtlView, CView)
	//{{AFX_MSG_MAP(CMsgCtlView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgCtlView drawing

void CMsgCtlView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMsgCtlView diagnostics

#ifdef _DEBUG
void CMsgCtlView::AssertValid() const
{
	CView::AssertValid();
}

void CMsgCtlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMsgCtlView message handlers

void CMsgCtlView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	CWnd *psheet = this->GetWindow(GW_CHILD);//m_messageSheet是resultview的唯一顶层子窗口
	if(psheet != NULL){
		CRect rect;
		this->GetWindowRect(&rect);
		psheet->ScreenToClient(&rect);
		psheet->SetWindowPos(NULL, 0, 0, rect.Width() , rect.Height() ,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
		CWnd *ptab = this->m_ParamSheet.GetTabControl();
		if(ptab != NULL){
			ptab->ScreenToClient(&rect);
			ptab->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
				SWP_NOZORDER | SWP_NOACTIVATE);
			
			//让PropertySheet自动调整page的大小
			this->m_ParamSheet.SetActivePage(this->m_ParamSheet.GetActiveIndex());
		}
	}
}

void CMsgCtlView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_ParamSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	
	if(m_ParamSheet.m_hWnd)
		m_ParamSheet.ShowWindow(SW_MAXIMIZE);//显示选项卡
}
