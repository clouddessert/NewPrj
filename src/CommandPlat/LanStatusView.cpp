// LanStatusView.cpp : implementation file
//

#include "stdafx.h"
#include "CommandPlat.h"
#include "LanStatusView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////
extern CCommandPlatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLanStatusView

IMPLEMENT_DYNCREATE(CLanStatusView, CView)

CLanStatusView::CLanStatusView()
{
}

CLanStatusView::~CLanStatusView()
{
}


BEGIN_MESSAGE_MAP(CLanStatusView, CView)
	//{{AFX_MSG_MAP(CLanStatusView)
	ON_WM_TIMER()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLanStatusView drawing

void CLanStatusView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLanStatusView diagnostics

#ifdef _DEBUG
void CLanStatusView::AssertValid() const
{
	CView::AssertValid();
}

void CLanStatusView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLanStatusView message handlers

void CLanStatusView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int nLen;
	vector<CString>::iterator pTmp;

	::EnterCriticalSection(&(theApp.g_cs));
	for (pTmp = theApp.m_NewMessage.begin(); pTmp != theApp.m_NewMessage.end(); ++pTmp)
	{
		nLen = m_EditCtrl->GetWindowTextLength ();
		m_EditCtrl->SetFocus ();
		m_EditCtrl->SetSel (nLen, nLen);
		m_EditCtrl->ReplaceSel(*pTmp);	
	}
	theApp.m_NewMessage.clear();
	::LeaveCriticalSection(&(theApp.g_cs));

	CView::OnTimer(nIDEvent);
}

void CLanStatusView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	theApp.pMsgFm = (void*)this;

	m_EditCtrl = new CEdit;
	if (!m_EditCtrl->Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_WANTRETURN, 
		CRect(10, 10, 400, 300), this, IDC_LAN_MSGEDIT))
	{
		TRACE0("Failed to create view for CMyBarLeft\n");
	}
	m_EditCtrl->ModifyStyleEx(0, WS_EX_CLIENTEDGE | ES_AUTOVSCROLL);

	SetTimer(3, 1500, NULL);
}

void CLanStatusView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	this->ShowWindow(SW_MAXIMIZE);
	
	//ÅÐ¶ÏÊÇ·ñ´æÔÚ¶¥²ã´°¿Ú
	CWnd *pchild = this->GetWindow(GW_CHILD);
	if(pchild != NULL)
	{
		CRect rect;
		this->GetWindowRect(&rect);
		ScreenToClient(&rect);
		
		m_EditCtrl->MoveWindow(0, 0, rect.Width(), rect.Height(), TRUE);
	}
}

void CLanStatusView::ClearMessages(void)
{
	m_EditCtrl->SetWindowText(_T(""));
	UpdateData(FALSE);
}
