#if !defined(AFX_ZDIDENTI_H__961AB726_5EFD_4687_8BDC_AFB45867BDE2__INCLUDED_)
#define AFX_ZDIDENTI_H__961AB726_5EFD_4687_8BDC_AFB45867BDE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDIdenti.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CZDIdenti dialog

class CZDIdenti : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbidenti;
    //  CString real_rty;
	CString real_plattye;
	int num;

	CZDIdenti(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZDIdenti)
	enum { IDD = IDD_DIALOG_ZDSHIBIE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZDIdenti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZDIdenti)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDIDENTI_H__961AB726_5EFD_4687_8BDC_AFB45867BDE2__INCLUDED_)
