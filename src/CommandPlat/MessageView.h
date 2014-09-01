#if !defined(AFX_MESSAGEVIEW_H__AF5269BB_6E8B_44F2_BFCB_9AF86BC7C674__INCLUDED_)
#define AFX_MESSAGEVIEW_H__AF5269BB_6E8B_44F2_BFCB_9AF86BC7C674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageView.h : header file
//

#include "MsgAllSheet.h"

/////////////////////////////////////////////////////////////////////////////
// CMessageView view

class CMessageView : public CView
{
protected:
	CMessageView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMessageView)

// Attributes
private:
	CMsgAllSheet m_MsgSheet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMessageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMessageView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEVIEW_H__AF5269BB_6E8B_44F2_BFCB_9AF86BC7C674__INCLUDED_)
