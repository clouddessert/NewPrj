#if !defined(AFX_PARAMFSTPAGE_H__E722DC0E_54E7_49D0_80ED_49D0311703F6__INCLUDED_)
#define AFX_PARAMFSTPAGE_H__E722DC0E_54E7_49D0_80ED_49D0311703F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamFstPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamFstPage dialog

class CParamFstPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParamFstPage)

// Construction
public:
	CParamFstPage();
	~CParamFstPage();

// Dialog Data
	//{{AFX_DATA(CParamFstPage)
	enum { IDD = IDD_PARAM_DLG_FIRST };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParamFstPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParamFstPage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMFSTPAGE_H__E722DC0E_54E7_49D0_80ED_49D0311703F6__INCLUDED_)
