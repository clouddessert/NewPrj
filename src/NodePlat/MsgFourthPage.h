#if !defined(AFX_MSGFOURTHPAGE_H__3C3FADA0_592E_467B_9496_254CE67FED63__INCLUDED_)
#define AFX_MSGFOURTHPAGE_H__3C3FADA0_592E_467B_9496_254CE67FED63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgFourthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgFourthPage dialog

class CMsgFourthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgFourthPage)

// Construction
public:
	CMsgFourthPage();
	~CMsgFourthPage();

// Dialog Data
	//{{AFX_DATA(CMsgFourthPage)
	enum { IDD = IDD_MSG_DLG_FOURTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgFourthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgFourthPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGFOURTHPAGE_H__3C3FADA0_592E_467B_9496_254CE67FED63__INCLUDED_)
