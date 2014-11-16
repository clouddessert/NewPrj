#if !defined(AFX_DRAWVIEW_H__0E850945_D55E_4971_A0DB_2CAE997AF1A7__INCLUDED_)
#define AFX_DRAWVIEW_H__0E850945_D55E_4971_A0DB_2CAE997AF1A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawView view

class CDrawView : public CView
{
protected:
	CDrawView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDrawView)

// Attributes
public:
    #define LEFT_LONGIT 115.8 //��߾���
	#define RIGHT_LONGIT 123.5//�ұ߾���
	#define UP_LATI 27.8   //�ϱ�γ��
    #define DOWN_LATI 21.5//�±�γ��

// Operations
private:
	//λͼ
	CBitmap TaiwanMap;
	//�ڴ�DC
	CDC MemDc;
	//λͼ��С
	BITMAP bBitMap;
	//�ͻ������С
	CRect ClientRect;

	//����Ŀ���
	CPoint m_TmpPt;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
private:
	void DrawLines(CDC *pDc, BITMAP &Bm, CRect &Rect);

protected:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWVIEW_H__0E850945_D55E_4971_A0DB_2CAE997AF1A7__INCLUDED_)
