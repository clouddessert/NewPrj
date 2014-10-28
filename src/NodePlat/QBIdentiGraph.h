#if !defined(AFX_QBIDENTIGRAPH_H__9FF0932C_1C6F_4D16_9F40_DE51DB0675D6__INCLUDED_)
#define AFX_QBIDENTIGRAPH_H__9FF0932C_1C6F_4D16_9F40_DE51DB0675D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QBIdentiGraph.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CQBIdentiGraph dialog

class CQBIdentiGraph : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbidenti;
	CQBIdentiGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQBIdentiGraph)
	enum { IDD = IDD_DIALOG_QBSHIBIETU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQBIdentiGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQBIdentiGraph)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QBIDENTIGRAPH_H__9FF0932C_1C6F_4D16_9F40_DE51DB0675D6__INCLUDED_)
