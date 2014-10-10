#if !defined(AFX_MSGFSTPAGE_H__2A00972C_0C57_4001_A2AA_D2943AEB16C3__INCLUDED_)
#define AFX_MSGFSTPAGE_H__2A00972C_0C57_4001_A2AA_D2943AEB16C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgFstPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgFstPage dialog

class CMsgFstPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgFstPage)

// Construction
public:
	CMsgFstPage();
	~CMsgFstPage();

// Dialog Data
	//{{AFX_DATA(CMsgFstPage)
	enum { IDD = IDD_MSG_DLG_FIRST };
	CListCtrl	m_click_esm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgFstPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgFstPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEsmMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRclickListEsm(NMHDR* pNMHDR, LRESULT* pResult);
	
	//afx_msg void OnSendmsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGFSTPAGE_H__2A00972C_0C57_4001_A2AA_D2943AEB16C3__INCLUDED_)
