#if !defined(AFX_DIALOGESM_H__71AE367F_1B13_41AE_AC4C_6E9FF59E0B66__INCLUDED_)
#define AFX_DIALOGESM_H__71AE367F_1B13_41AE_AC4C_6E9FF59E0B66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogESM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogESM dialog
#include "ParamFourthPage.h"
class CDialogESM : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogESM(CWnd* pParent = NULL);   // standard constructor    
	int ID;
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogESM)
	enum { IDD = IDD_DB_ESM };
	CComboBox	m_baseevent;
	CComboBox	m_esmscan;
	CComboBox	m_esmprit;
	CComboBox	m_esmpwz;
	CComboBox	m_esmpaw;
	CComboBox	m_esmpre;
	CListCtrl	m_Grid;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogESM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogESM)
	virtual BOOL OnInitDialog();
	afx_msg void OnButAdd();
	afx_msg void OnButMod();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGESM_H__71AE367F_1B13_41AE_AC4C_6E9FF59E0B66__INCLUDED_)
