#if !defined(AFX_MSGTENPAGE_H__63D72279_9D1C_448F_9F37_C88DC5352404__INCLUDED_)
#define AFX_MSGTENPAGE_H__63D72279_9D1C_448F_9F37_C88DC5352404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgTenPage.h : header file
//
extern CNodePlatApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CMsgTenPage dialog

class CMsgTenPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgTenPage)

// Construction
public:
	CMsgTenPage();
	~CMsgTenPage();

// Dialog Data
	//{{AFX_DATA(CMsgTenPage)
	enum { IDD = IDD_DIALOG_TEN };
	CListCtrl	m_PlatList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgTenPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgTenPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGTENPAGE_H__63D72279_9D1C_448F_9F37_C88DC5352404__INCLUDED_)
