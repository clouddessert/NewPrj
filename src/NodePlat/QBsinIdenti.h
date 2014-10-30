#if !defined(AFX_QBSINIDENTI_H__7B1DF068_81CB_416D_AC0A_5F0FC8E1BF79__INCLUDED_)
#define AFX_QBSINIDENTI_H__7B1DF068_81CB_416D_AC0A_5F0FC8E1BF79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QBsinIdenti.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CQBsinIdenti dialog

class CQBsinIdenti : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbidenti;
	CQBsinIdenti(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQBsinIdenti)
	enum { IDD = IDD_DIALOG_QBSINSHIBIE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQBsinIdenti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQBsinIdenti)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QBSINIDENTI_H__7B1DF068_81CB_416D_AC0A_5F0FC8E1BF79__INCLUDED_)
