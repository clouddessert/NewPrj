// ParamSetView.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "ParamSetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParamSetView

IMPLEMENT_DYNCREATE(CParamSetView, CView)

CParamSetView::CParamSetView() : m_ParamSheet("")
{
}

CParamSetView::~CParamSetView()
{
}


BEGIN_MESSAGE_MAP(CParamSetView, CView)
	//{{AFX_MSG_MAP(CParamSetView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParamSetView drawing

void CParamSetView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CParamSetView diagnostics

#ifdef _DEBUG
void CParamSetView::AssertValid() const
{
	CView::AssertValid();
}

void CParamSetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CParamSetView message handlers

void CParamSetView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_ParamSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	
	if(m_ParamSheet.m_hWnd)
		m_ParamSheet.ShowWindow(SW_MAXIMIZE);//显示选项卡
}

void CParamSetView::OnSize(UINT nType, int cx, int cy) 
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
