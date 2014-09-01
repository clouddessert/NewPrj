// NodePlatView.h : interface of the CNodePlatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODEPLATVIEW_H__C3BBF27E_EAE9_4CED_826F_27C587A63107__INCLUDED_)
#define AFX_NODEPLATVIEW_H__C3BBF27E_EAE9_4CED_826F_27C587A63107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNodePlatView : public CView
{
protected: // create from serialization only
	CNodePlatView();
	DECLARE_DYNCREATE(CNodePlatView)

// Attributes
public:
	CNodePlatDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNodePlatView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNodePlatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:
// Generated message map functions
protected:
	//{{AFX_MSG(CNodePlatView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in NodePlatView.cpp
inline CNodePlatDoc* CNodePlatView::GetDocument()
   { return (CNodePlatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NODEPLATVIEW_H__C3BBF27E_EAE9_4CED_826F_27C587A63107__INCLUDED_)
