#if !defined(AFX_PARAMSETVIEW_H__85622787_235D_4FA5_9E21_DD487916368D__INCLUDED_)
#define AFX_PARAMSETVIEW_H__85622787_235D_4FA5_9E21_DD487916368D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamSetView.h : header file
//

#include "AllParamSheet.h"

/////////////////////////////////////////////////////////////////////////////
// CParamSetView view

class CParamSetView : public CView
{
protected:
	CParamSetView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CParamSetView)

// Attributes
private:
	CAllParamSheet m_ParamSheet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamSetView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CParamSetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CParamSetView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMSETVIEW_H__85622787_235D_4FA5_9E21_DD487916368D__INCLUDED_)
