#if !defined(AFX_DIALOGSPA_H__CBE9BFB0_36DA_4BE1_B10C_7C53EF450407__INCLUDED_)
#define AFX_DIALOGSPA_H__CBE9BFB0_36DA_4BE1_B10C_7C53EF450407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSPA.h : header file
//
#include "ParamFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogSPA dialog

class CDialogSPA : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogSPA(CWnd* pParent = NULL);   // standard constructor
	int ID;
	
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogSPA)
	enum { IDD = IDD_DB_SPA };
	CComboBox	m_objtype;
	CListCtrl	m_Grid;
	CString	m_id;
	CString	m_distance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSPA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSPA)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButadd();
	afx_msg void OnButmod();
	afx_msg void OnButdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSPA_H__CBE9BFB0_36DA_4BE1_B10C_7C53EF450407__INCLUDED_)
