// MessageView.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "MessageView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageView

IMPLEMENT_DYNCREATE(CMessageView, CView)

CMessageView::CMessageView() : m_MsgSheet("")
{
}

CMessageView::~CMessageView()
{
}


BEGIN_MESSAGE_MAP(CMessageView, CView)
	//{{AFX_MSG_MAP(CMessageView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageView drawing

void CMessageView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMessageView diagnostics

#ifdef _DEBUG
void CMessageView::AssertValid() const
{
	CView::AssertValid();
}

void CMessageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMessageView message handlers

void CMessageView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_MsgSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	
	if(m_MsgSheet.m_hWnd)
		m_MsgSheet.ShowWindow(SW_MAXIMIZE);//显示选项卡
}

void CMessageView::OnSize(UINT nType, int cx, int cy) 
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
		CWnd *ptab = this->m_MsgSheet.GetTabControl();
		if(ptab != NULL){
			ptab->ScreenToClient(&rect);
			ptab->SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(),
				SWP_NOZORDER | SWP_NOACTIVATE);
			
			//让PropertySheet自动调整page的大小
			this->m_MsgSheet.SetActivePage(this->m_MsgSheet.GetActiveIndex());
		}
	}
}
