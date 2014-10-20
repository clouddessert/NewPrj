#if !defined(AFX_MSGSEVENTHPAGE_H__0AD4EB5A_E2D2_4DD2_A270_9040725D6329__INCLUDED_)
#define AFX_MSGSEVENTHPAGE_H__0AD4EB5A_E2D2_4DD2_A270_9040725D6329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSeventhPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgSeventhPage dialog

class CMsgSeventhPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgSeventhPage)

// Construction
public:
	CMsgSeventhPage();
	~CMsgSeventhPage();

// Dialog Data
	//{{AFX_DATA(CMsgSeventhPage)
	enum { IDD = IDD_MSG_DLG_SEVENTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgSeventhPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgSeventhPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnFusCommMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSEVENTHPAGE_H__0AD4EB5A_E2D2_4DD2_A270_9040725D6329__INCLUDED_)
