#if !defined(AFX_MSGSIXTHPAGE_H__95871465_91C0_4656_9B17_88F9407FF919__INCLUDED_)
#define AFX_MSGSIXTHPAGE_H__95871465_91C0_4656_9B17_88F9407FF919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSixthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgSixthPage dialog

class CMsgSixthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgSixthPage)

// Construction
public:
	CMsgSixthPage();
	~CMsgSixthPage();

// Dialog Data
	//{{AFX_DATA(CMsgSixthPage)
	enum { IDD = IDD_MSG_DLG_SIXTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgSixthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgSixthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSIXTHPAGE_H__95871465_91C0_4656_9B17_88F9407FF919__INCLUDED_)
