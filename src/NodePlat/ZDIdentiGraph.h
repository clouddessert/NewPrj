#if !defined(AFX_ZDIDENTIGRAPH_H__3F5F915C_5BC3_4095_A144_150990A430D5__INCLUDED_)
#define AFX_ZDIDENTIGRAPH_H__3F5F915C_5BC3_4095_A144_150990A430D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDIdentiGraph.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CZDIdentiGraph dialog

class CZDIdentiGraph : public CDialog
{
// Construction
public:
	void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbidenti;
	//	CString real_rty;
	CString real_plattye;
	int num;

	CZDIdentiGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZDIdentiGraph)
	enum { IDD = IDD_DIALOG_ZDSHIBIETU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZDIdentiGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZDIdentiGraph)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDIDENTIGRAPH_H__3F5F915C_5BC3_4095_A144_150990A430D5__INCLUDED_)
