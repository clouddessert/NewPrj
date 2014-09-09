#if !defined(AFX_MSGTHREEPAGE_H__7D4511EF_FE59_4268_9893_6E34730B141F__INCLUDED_)
#define AFX_MSGTHREEPAGE_H__7D4511EF_FE59_4268_9893_6E34730B141F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgThreePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgThreePage dialog

class CMsgThreePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgThreePage)

// Construction
public:
	CMsgThreePage();
	~CMsgThreePage();

// Dialog Data
	//{{AFX_DATA(CMsgThreePage)
	enum { IDD = IDD_MSG_DLG_THREE };
	CListCtrl	m_click_trace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgThreePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgThreePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnTraceMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRclickListTrace(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGTHREEPAGE_H__7D4511EF_FE59_4268_9893_6E34730B141F__INCLUDED_)
