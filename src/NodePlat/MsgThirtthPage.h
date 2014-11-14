#if !defined(AFX_MSGTHIRTTHPAGE_H__03497FF1_1DB3_4C85_8823_E13922FCCACA__INCLUDED_)
#define AFX_MSGTHIRTTHPAGE_H__03497FF1_1DB3_4C85_8823_E13922FCCACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgThirtthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgThirtthPage dialog

class CMsgThirtthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgThirtthPage)

// Construction
public:
	CMsgThirtthPage();
	~CMsgThirtthPage();

// Dialog Data
	//{{AFX_DATA(CMsgThirtthPage)
	enum { IDD = IDD_DIALOG_THIRTTH };
	CListCtrl	m_InterList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgThirtthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgThirtthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnSigleOutMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGTHIRTTHPAGE_H__03497FF1_1DB3_4C85_8823_E13922FCCACA__INCLUDED_)
