#if !defined(AFX_QBFUS_H__B563C665_657A_47A0_90A9_5E3C07530500__INCLUDED_)
#define AFX_QBFUS_H__B563C665_657A_47A0_90A9_5E3C07530500__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QBFus.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CQBFus dialog

class CQBFus : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbfus;
	CQBFus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQBFus)
	enum { IDD = IDD_DIALOG_QBFUS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQBFus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQBFus)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QBFUS_H__B563C665_657A_47A0_90A9_5E3C07530500__INCLUDED_)
