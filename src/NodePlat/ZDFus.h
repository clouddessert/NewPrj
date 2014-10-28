#if !defined(AFX_ZDFUS_H__28332367_E2D6_4728_9B44_69639B581A44__INCLUDED_)
#define AFX_ZDFUS_H__28332367_E2D6_4728_9B44_69639B581A44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZDFus.h : header file
//
#include "afxdb.h"
/////////////////////////////////////////////////////////////////////////////
// CZDFus dialog

class CZDFus : public CDialog
{
// Construction
public:
	int num;
//  	struct UNIFY
// 	{
// 		int h;
//  		int m;
//  		int s;
//  		int ms;
//  	};
//  	UNIFY IntToTime(int t);
	void OpenIdentiDb();
	void ShowData(int number);
	CDatabase m_dbfus;
	CZDFus(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZDFus)
	enum { IDD = IDD_DIALOG_ZDFUS };
	CListCtrl	m_zdFus;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZDFus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZDFus)
	virtual BOOL OnInitDialog();
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDFUS_H__28332367_E2D6_4728_9B44_69639B581A44__INCLUDED_)
