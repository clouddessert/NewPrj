#if !defined(AFX_DIALOGCOM_H__5B14D44A_35D7_429E_A92D_0247587F1189__INCLUDED_)
#define AFX_DIALOGCOM_H__5B14D44A_35D7_429E_A92D_0247587F1189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogCOM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogCOM dialog
#include "ParamFourthPage.h"
class CDialogCOM : public CDialog
{
// Construction
public:
	void AddToGrid();
	int ID;
	CDialogCOM(CWnd* pParent = NULL);   // standard constructor
	int ids;
	CParamFourthPage ado;
// Dialog Data
	//{{AFX_DATA(CDialogCOM)
	enum { IDD = IDD_DB_COM };
	CComboBox	m_baseevent;
	CComboBox	m_hoop;
	CComboBox	m_paw;
	CComboBox	m_pre;
	CListCtrl	m_Grid;
	CString	m_id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogCOM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogCOM)
	virtual BOOL OnInitDialog();
	afx_msg void OnButAdd();
	afx_msg void OnButmod();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButDel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCOM_H__5B14D44A_35D7_429E_A92D_0247587F1189__INCLUDED_)
