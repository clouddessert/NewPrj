#if !defined(AFX_LANSTATUSVIEW_H__6EF67E6B_80B8_497B_9CCF_767ECF290920__INCLUDED_)
#define AFX_LANSTATUSVIEW_H__6EF67E6B_80B8_497B_9CCF_767ECF290920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LanStatusView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLanStatusView view

class CLanStatusView : public CView
{
protected:
	CLanStatusView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLanStatusView)

// Attributes
public:
	//Çå¿ÕÐÅÏ¢
	void ClearMessages(void);

// Operations
private:
	CEdit* m_EditCtrl;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLanStatusView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLanStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLanStatusView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANSTATUSVIEW_H__6EF67E6B_80B8_497B_9CCF_767ECF290920__INCLUDED_)
