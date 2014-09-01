// MsgListView.cpp : implementation file
//

#include "stdafx.h"
#include "NodePlat.h"
#include "MsgListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
extern CRITICAL_SECTION g_cs;				// �ٽ����ṹ����

/////////////////////////////////////////////////////////////////////////////
// CMsgListView

IMPLEMENT_DYNCREATE(CMsgListView, CView)

CMsgListView::CMsgListView():m_MsgSheet("")
{
	//{{AFX_DATA_INIT(CMsgListView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMsgListView::~CMsgListView()
{
}

BEGIN_MESSAGE_MAP(CMsgListView, CView)
	//{{AFX_MSG_MAP(CMsgListView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgListView diagnostics

#ifdef _DEBUG
void CMsgListView::AssertValid() const
{
	CView::AssertValid();
}

void CMsgListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMsgListView message handlers

void CMsgListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

void CMsgListView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	CWnd *psheet = this->GetWindow(GW_CHILD);//m_messageSheet��resultview��Ψһ�����Ӵ���
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
			
			//��PropertySheet�Զ�����page�Ĵ�С
			this->m_MsgSheet.SetActivePage(this->m_MsgSheet.GetActiveIndex());
		}
	}
}

void CMsgListView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_MsgSheet.Create(this, WS_CHILD | WS_VISIBLE, 0);
	
	if(m_MsgSheet.m_hWnd)
		m_MsgSheet.ShowWindow(SW_MAXIMIZE);//��ʾѡ�
}
