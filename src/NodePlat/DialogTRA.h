#if !defined(AFX_DIALOGTRA_H__FCC99752_E256_498F_8A5D_28A3644160AF__INCLUDED_)
#define AFX_DIALOGTRA_H__FCC99752_E256_498F_8A5D_28A3644160AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTRA.h : header file
//
#include "ParamFourthPage.h"
/////////////////////////////////////////////////////////////////////////////
// CDialogTRA dialog

class CDialogTRA : public CDialog
{
// Construction
public:
	void AddToGrid();
	CDialogTRA(CWnd* pParent = NULL);   // standard constructor
	int ID;

	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogTRA)
	enum { IDD = IDD_DB_TRA };
	CComboBox	m_baseevent;
	CComboBox	m_high;
	CComboBox	m_azimuth;
	CComboBox	m_addspeed;
	CComboBox	m_speed;
	CComboBox	m_rd;
	CListCtrl	m_Grid;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTRA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogTRA)
	virtual BOOL OnInitDialog();
	afx_msg void OnButAdd();
	afx_msg void OnButmod();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButdel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTRA_H__FCC99752_E256_498F_8A5D_28A3644160AF__INCLUDED_)
