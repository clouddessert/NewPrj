#if !defined(AFX_DIALOGESM1_H__76F4488E_F615_4F01_B639_FF4697CFE218__INCLUDED_)
#define AFX_DIALOGESM1_H__76F4488E_F615_4F01_B639_FF4697CFE218__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogESM1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogESM1 dialog
#include "ParamFourthPage.h"
class CDialogESM1 : public CDialog
{
// Construction
public:

	void AddToGrid();
	CDialogESM1(CWnd* pParent = NULL);   // standard constructor
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogESM1)
	enum { IDD = IDD_DB_ESM1 };
	CListCtrl	m_Grid;
	CString	m_data1;
	CString	m_style;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogESM1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogESM1)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButmod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGESM1_H__76F4488E_F615_4F01_B639_FF4697CFE218__INCLUDED_)
