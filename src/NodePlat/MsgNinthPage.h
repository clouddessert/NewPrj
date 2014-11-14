#if !defined(AFX_MSGNINTHPAGE_H__74E1A910_E783_45E4_9B17_B0E36A1E028D__INCLUDED_)
#define AFX_MSGNINTHPAGE_H__74E1A910_E783_45E4_9B17_B0E36A1E028D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgNinthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgNinthPage dialog

class CMsgNinthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgNinthPage)

// Construction
public:
	CMsgNinthPage();
	~CMsgNinthPage();

// Dialog Data
	//{{AFX_DATA(CMsgNinthPage)
	enum { IDD = IDD_MSG_DLG_NINTH };
	CListCtrl	m_EventList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgNinthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgNinthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGNINTHPAGE_H__74E1A910_E783_45E4_9B17_B0E36A1E028D__INCLUDED_)
