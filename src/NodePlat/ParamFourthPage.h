#if !defined(AFX_PARAMFOURTHPAGE_H__53A8BAB4_33AF_4A55_9A27_9539E074F833__INCLUDED_)
#define AFX_PARAMFOURTHPAGE_H__53A8BAB4_33AF_4A55_9A27_9539E074F833__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamFourthPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParamFourthPage dialog

class CParamFourthPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CParamFourthPage)

// Construction
public:
	void ExitConnect();
	void OnInitADOConn();
	CParamFourthPage();
	~CParamFourthPage();
	_ConnectionPtr pConn;
	_RecordsetPtr pRst;
// Dialog Data
	//{{AFX_DATA(CParamFourthPage)
	enum { IDD = IDD_PARAM_DLG_FOURTH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParamFourthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParamFourthPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangedDbTree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMFOURTHPAGE_H__53A8BAB4_33AF_4A55_9A27_9539E074F833__INCLUDED_)
