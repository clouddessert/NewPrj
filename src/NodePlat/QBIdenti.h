#if !defined(AFX_QBIDENTI_H__1D2DA3A1_1337_464D_A421_941A4FCA4D40__INCLUDED_)
#define AFX_QBIDENTI_H__1D2DA3A1_1337_464D_A421_941A4FCA4D40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QBIdenti.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CQBIdenti dialog

class CQBIdenti : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbidenti;
	CQBIdenti(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQBIdenti)
	enum { IDD = IDD_DIALOG_QBSHIBIE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQBIdenti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQBIdenti)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QBIDENTI_H__1D2DA3A1_1337_464D_A421_941A4FCA4D40__INCLUDED_)
