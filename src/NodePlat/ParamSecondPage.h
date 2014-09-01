#if !defined(AFX_PARAMSECONDPAGE_H__55929950_61C9_49C6_9003_B8622F123412__INCLUDED_)
#define AFX_PARAMSECONDPAGE_H__55929950_61C9_49C6_9003_B8622F123412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamSecondPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamSecondPage dialog

class CParamSecondPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParamSecondPage)

// Construction
public:
	CParamSecondPage();
	~CParamSecondPage();

// Dialog Data
	//{{AFX_DATA(CParamSecondPage)
	enum { IDD = IDD_PARAM_DLG_SECOND };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParamSecondPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParamSecondPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMSECONDPAGE_H__55929950_61C9_49C6_9003_B8622F123412__INCLUDED_)
