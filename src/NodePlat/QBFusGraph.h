#if !defined(AFX_QBFUSGRAPH_H__F6523786_6F15_425F_8264_65EC086CBD3A__INCLUDED_)
#define AFX_QBFUSGRAPH_H__F6523786_6F15_425F_8264_65EC086CBD3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QBFusGraph.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CQBFusGraph dialog

class CQBFusGraph : public CDialog
{
// Construction
public:
	//void OpenIdentiDb();
	void ShowData();
	CDatabase m_dbfus;
	CQBFusGraph(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQBFusGraph)
	enum { IDD = IDD_DIALOG_QBFUSTU };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQBFusGraph)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQBFusGraph)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QBFUSGRAPH_H__F6523786_6F15_425F_8264_65EC086CBD3A__INCLUDED_)
