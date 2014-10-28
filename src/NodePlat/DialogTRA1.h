#if !defined(AFX_DIALOGTRA1_H__5F5341D5_4D2E_4462_B57E_E40E30727B7C__INCLUDED_)
#define AFX_DIALOGTRA1_H__5F5341D5_4D2E_4462_B57E_E40E30727B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogTRA1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogTRA1 dialog
#include "ParamFourthPage.h"
class CDialogTRA1 : public CDialog
{
// Construction
public:

	void AddToGrid();
	CDialogTRA1(CWnd* pParent = NULL);   // standard constructor
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogTRA1)
	enum { IDD = IDD_DB_TRA1 };
	CListCtrl	m_Grid;
	CString	m_data1;
	CString	m_id;
	CString	m_style;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogTRA1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogTRA1)
	virtual BOOL OnInitDialog();
	afx_msg void OnButmod();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGTRA1_H__5F5341D5_4D2E_4462_B57E_E40E30727B7C__INCLUDED_)
