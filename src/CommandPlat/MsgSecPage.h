#if !defined(AFX_MSGSECPAGE_H__A3B15A3B_D93A_4FED_8F27_E6D340F281F8__INCLUDED_)
#define AFX_MSGSECPAGE_H__A3B15A3B_D93A_4FED_8F27_E6D340F281F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgSecPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgSecPage dialog

class CMsgSecPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgSecPage)

// Construction
public:
	CMsgSecPage();
	~CMsgSecPage();

// Dialog Data
	//{{AFX_DATA(CMsgSecPage)
	enum { IDD = IDD_MSG_DLG_SECOND };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgSecPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgSecPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnCommMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGSECPAGE_H__A3B15A3B_D93A_4FED_8F27_E6D340F281F8__INCLUDED_)
