#if !defined(AFX_DIALOGCOM1_H__2B0CA09D_FF32_4B8A_9DF4_8696A4FF3698__INCLUDED_)
#define AFX_DIALOGCOM1_H__2B0CA09D_FF32_4B8A_9DF4_8696A4FF3698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogCOM1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogCOM1 dialog
#include "ParamFourthPage.h"
class CDialogCOM1 : public CDialog
{
// Construction
public:

	void AddToGrid();
	CDialogCOM1(CWnd* pParent = NULL);   // standard constructor
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogCOM1)
	enum { IDD = IDD_DB_COM1 };
	CListCtrl	m_Grid;
	CString	m_style;
	CString	m_data1;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogCOM1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogCOM1)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButmod();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCOM1_H__2B0CA09D_FF32_4B8A_9DF4_8696A4FF3698__INCLUDED_)
