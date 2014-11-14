// NodePlatView.cpp : implementation of the CNodePlatView class
//

#include "stdafx.h"
#include "NodePlat.h"

#include "NodePlatDoc.h"
#include "NodePlatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CNodePlatApp theApp;
//////////////////////////////////////////////////////////////////////////
   
CNodePlatDoc* pDoc = NULL;

/////////////////////////////////////////////////////////////////////////////
// CNodePlatView

IMPLEMENT_DYNCREATE(CNodePlatView, CView)

BEGIN_MESSAGE_MAP(CNodePlatView, CView)
	//{{AFX_MSG_MAP(CNodePlatView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNodePlatView construction/destruction

CNodePlatView::CNodePlatView()
{
	// TODO: add construction code here
	pDoc = GetDocument();
}

CNodePlatView::~CNodePlatView()
{

}

BOOL CNodePlatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNodePlatView drawing

void CNodePlatView::OnDraw(CDC* pDC)
{
	CNodePlatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CNodePlatView diagnostics

#ifdef _DEBUG
void CNodePlatView::AssertValid() const
{
	CView::AssertValid();
}

void CNodePlatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNodePlatDoc* CNodePlatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNodePlatDoc)));
	return (CNodePlatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNodePlatView message handlers

// void CNodePlatView::OnTimer(UINT nIDEvent) 
// {
// 	// TODO: Add your message handler code here and/or call default
// 
// 	CView::OnTimer(nIDEvent);
// }


