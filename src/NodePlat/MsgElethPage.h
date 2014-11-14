#if !defined(AFX_MSGELETHPAGE_H__838FE57C_695B_4E4B_BCAA_A746E8B8D930__INCLUDED_)
#define AFX_MSGELETHPAGE_H__838FE57C_695B_4E4B_BCAA_A746E8B8D930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgElethPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgElethPage dialog

class CMsgElethPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgElethPage)

// Construction
public:
	CMsgElethPage();
	~CMsgElethPage();

// Dialog Data
	//{{AFX_DATA(CMsgElethPage)
	enum { IDD = IDD_DIALOG_ELEVENTH };
	CListCtrl	m_SpaceList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgElethPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgElethPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGELETHPAGE_H__838FE57C_695B_4E4B_BCAA_A746E8B8D930__INCLUDED_)
