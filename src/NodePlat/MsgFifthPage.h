#if !defined(AFX_MSGFIFTHPAGE_H__DD640EEF_6E4A_492F_BAB7_3CE550744424__INCLUDED_)
#define AFX_MSGFIFTHPAGE_H__DD640EEF_6E4A_492F_BAB7_3CE550744424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgFifthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgFifthPage dialog

class CMsgFifthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgFifthPage)

// Construction
public:
	CMsgFifthPage();
	~CMsgFifthPage();

// Dialog Data
	//{{AFX_DATA(CMsgFifthPage)
	enum { IDD = IDD_MSG_DLG_FIFTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgFifthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgFifthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGFIFTHPAGE_H__DD640EEF_6E4A_492F_BAB7_3CE550744424__INCLUDED_)
