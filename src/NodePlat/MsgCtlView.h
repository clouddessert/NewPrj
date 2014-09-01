#if !defined(AFX_MSGCTLVIEW_H__EDF02E86_828F_44B3_B016_CD665237D152__INCLUDED_)
#define AFX_MSGCTLVIEW_H__EDF02E86_828F_44B3_B016_CD665237D152__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgCtlView.h : header file
//

#include "AllParamSheet.h"
/////////////////////////////////////////////////////////////////////////////
// CMsgCtlView view

class CMsgCtlView : public CView
{
protected:
	CMsgCtlView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMsgCtlView)

// Attributes
private:
	CAllParamSheet m_ParamSheet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgCtlView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMsgCtlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMsgCtlView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGCTLVIEW_H__EDF02E86_828F_44B3_B016_CD665237D152__INCLUDED_)
