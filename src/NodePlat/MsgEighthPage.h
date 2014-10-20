#if !defined(AFX_MSGEIGHTHPAGE_H__D5A73EBE_FAAC_473B_B80C_492D31B1D937__INCLUDED_)
#define AFX_MSGEIGHTHPAGE_H__D5A73EBE_FAAC_473B_B80C_492D31B1D937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgEighthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgEighthPage dialog

class CMsgEighthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMsgEighthPage)

// Construction
public:
	CMsgEighthPage();
	~CMsgEighthPage();

// Dialog Data
	//{{AFX_DATA(CMsgEighthPage)
	enum { IDD = IDD_MSG_DLG_EIGHTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMsgEighthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMsgEighthPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnFusTraceMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGEIGHTHPAGE_H__D5A73EBE_FAAC_473B_B80C_492D31B1D937__INCLUDED_)
