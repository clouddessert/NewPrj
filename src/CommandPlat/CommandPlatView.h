// CommandPlatView.h : interface of the CCommandPlatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMANDPLATVIEW_H__57AA9C3E_535F_408D_A36D_C86231A3E45A__INCLUDED_)
#define AFX_COMMANDPLATVIEW_H__57AA9C3E_535F_408D_A36D_C86231A3E45A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommandPlatView : public CView
{
protected: // create from serialization only
	CCommandPlatView();
	DECLARE_DYNCREATE(CCommandPlatView)

// Attributes
public:
	CCommandPlatDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandPlatView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCommandPlatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	//位图
	CBitmap TaiwanMap;

	//内存DC
	CDC MemDc;
	//位图大小
	BITMAP bBitMap;
	//客户区域大小
	CRect ClientRect;

	//目标点
	CPoint m_TmpPt;
    

private:
	VCT_ESM_MSG::iterator pESM_Dat;
	VCT_COMM_MSG::iterator pComm_Dat;
	VCT_TRACE_MSG::iterator pTrace_Dat;

//	VCT_IDENTIFY_MSG::iterator pIDENTIFY_Dat;

private:
   void DrawLines(CDC *pDc, BITMAP &Bm, CRect &Rect);

    


// Generated message map functions
protected:
	//{{AFX_MSG(CCommandPlatView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CommandPlatView.cpp
inline CCommandPlatDoc* CCommandPlatView::GetDocument()
   { return (CCommandPlatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDPLATVIEW_H__57AA9C3E_535F_408D_A36D_C86231A3E45A__INCLUDED_)
