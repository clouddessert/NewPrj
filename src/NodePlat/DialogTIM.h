#if !defined(AFX_DIALOGTIM_H__756692A2_F711_48D4_BDD8_E2A1945A3FED__INCLUDED_)
#define AFX_DIALOGTIM_H__756692A2_F711_48D4_BDD8_E2A1945A3FED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTIM.h : header file
//
#include "ParamFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogTIM dialog

class CDialogTIM : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogTIM(CWnd* pParent = NULL);   // standard constructor
	int ID;
	
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogTIM)
	enum { IDD = IDD_DB_TIM };
	CListCtrl	m_Grid;
	CString	m_id;
	BOOL	m_ale;
	BOOL	m_pat;
	BOOL	m_att;
	BOOL	m_int;
	BOOL	m_bom;
	BOOL	m_pen;
	BOOL	m_fev;
	BOOL	m_war;
	BOOL	m_rec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTIM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogTIM)
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

#endif // !defined(AFX_DIALOGTIM_H__756692A2_F711_48D4_BDD8_E2A1945A3FED__INCLUDED_)
