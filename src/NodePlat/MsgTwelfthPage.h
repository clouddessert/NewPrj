#if !defined(AFX_MSGTWELFTHPAGE_H__D5E7EF41_5B30_47B2_8048_CB32D9FD6F65__INCLUDED_)
#define AFX_MSGTWELFTHPAGE_H__D5E7EF41_5B30_47B2_8048_CB32D9FD6F65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgTwelfthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgTwelfthPage dialog

class CMsgTwelfthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgTwelfthPage)

// Construction
public:
	CMsgTwelfthPage();
	~CMsgTwelfthPage();

// Dialog Data
	//{{AFX_DATA(CMsgTwelfthPage)
	enum { IDD = IDD_DIALOG_TWELFTH };
	CListCtrl	m_FunList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgTwelfthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgTwelfthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGTWELFTHPAGE_H__D5E7EF41_5B30_47B2_8048_CB32D9FD6F65__INCLUDED_)
