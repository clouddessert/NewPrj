#if !defined(AFX_MSGLISTVIEW_H__4EF710EC_1982_4DF0_A19F_FA05E780760B__INCLUDED_)
#define AFX_MSGLISTVIEW_H__4EF710EC_1982_4DF0_A19F_FA05E780760B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgListView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "MsgAllSheet.h"

class CMsgListView : public CView
{
protected:
	CMsgListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMsgListView)

// Form Data
public:
	//{{AFX_DATA(CMsgListView)
	//}}AFX_DATA

// Attributes
private:
	CMsgAllSheet m_MsgSheet;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMsgListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMsgListView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGLISTVIEW_H__4EF710EC_1982_4DF0_A19F_FA05E780760B__INCLUDED_)
